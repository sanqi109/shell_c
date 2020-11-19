#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define MAJOR(dev)	((dev)>>8)
#define MINOR(dev)	((dev) & 0xff)
#define MKDEV(ma,mi)	((ma)<<8 | (mi))

#define BUFF_SIZE 3000

int ifProcess(char *s)
{
	int i;
	for(i=0;s[i]!='\0';i++)
	{
		if(!isdigit(s[i])) //检查字符串是否只由数字组成
		   return 0;
	}
	return 1;
}

void main(){
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	DIR *proc;
	FILE *fp;
	char path[BUFF_SIZE], comm[BUFF_SIZE], state, temp_string[BUFF_SIZE], c, cmdline[BUFF_SIZE];
	int pid, session, tty_nr, tpgid, temp_int, major, minor, device, sec, min, hour, day, count, width;
	long unsigned int utime, stime, cutime, cstime, temp_luint, time;
	long int nice, num_threads, temp_lint;
	unsigned int temp_uint, VmLck;
	proc = opendir("/proc/");
	/*
	/proc目录中包含许多以数字命名的子目录，这些数字表示系统当前正在运行进程的进程号，
	里面包含对应进程相关的多个信息文件。
	*/
	if(proc == NULL)
	{
		perror("Cannot open /proc directory\n");
		return ;
	}
	struct dirent *process;
	puts("PID\tTTY\tSTAT\tTIME\tCOMMAND");
	errno = 0;
	while((process = readdir(proc)) != NULL && errno == 0) //循环读出/proc/目录下的值并赋给process
	{    
		if(ifProcess(process->d_name)) //进行判断，如果名字是数字就是代表一个进程
		{
			width = w.ws_col - 32;
			VmLck = 0;
			count = 0;
			strcpy(path,"/proc/");
			strcat(path,process->d_name); //拼接字符串，将其赋给path，返回指向path的指针
			strcat(path,"/stat");
			fp = fopen(path,"r");
			if(fp == NULL)
				continue;
			// lu:lang unsigned  ld:输出长整数型
			//fscanf:从输入流(stream)中读入数据，存储到 *argument中，遇到空格和换行时结束                1          S      0        1           1       0      -1      4194560   91043         86          246         49        615     134    85       20       0        1         0               
/*
pid： 进程ID.
comm: task_struct结构体的进程名
state: 进程状态, 此处为S
ppid: 父进程ID （父进程是指通过fork方式，通过clone并非父进程）
pgrp：进程组ID
session：进程会话组ID
tty_nr：当前进程的tty终点设备号
tpgid：控制进程终端的前台进程号
flags：进程标识位，定义在include/linux/sched.h中的PF_*, 此处等于1077952832
minflt： 次要缺页中断的次数，即无需从磁盘加载内存页. 比如COW和匿名页
cminflt：当前进程等待子进程的minflt
majflt：主要缺页中断的次数，需要从磁盘加载内存页. 比如map文件
majflt：当前进程等待子进程的majflt
utime: 该进程处于用户态的时间，单位jiffies，此处等于166114
stime: 该进程处于内核态的时间，单位jiffies，此处等于129684
cutime：当前进程等待子进程的utime
cstime: 当前进程等待子进程的utime
priority: 进程优先级, 此次等于10.
nice: nice值，取值范围[19, -20]，此处等于-10
num_threads: 线程个数, 此处等于221 
*/
			fscanf(fp,"%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %lu %lu %ld %ld %ld",&pid,comm,&state,&temp_int,&temp_int,&session,&tty_nr,&tpgid,&temp_uint,&temp_luint,&temp_luint,&temp_luint,&temp_luint,&utime,&stime,&cutime,&cstime,&temp_lint,&nice,&num_threads);
			fclose(fp);

			strcpy(path,"/proc/");
			strcat(path,process->d_name);
			strcat(path,"/status");
			fp = fopen(path,"r");
			if(fp == NULL)
				continue;
				
			do
				fscanf(fp,"%s ",temp_string);
			while(strcmp(temp_string,"VmLck:")!=0 && !feof(fp));
			fscanf(fp," %u",&VmLck);
			fclose(fp);
			major = MAJOR(tty_nr);
			minor = MINOR(tty_nr);
			device = MKDEV(major,minor);
			if(device != tty_nr)
			{
				printf("tty error\n");
				return ;
			}
			strcpy(path,"/proc/");
			strcat(path,process->d_name);
			strcat(path,"/cmdline");
			fopen(path,"r");
			if(fp == NULL)
				continue;
			printf("%d",pid);
			if(major == 0)
				printf("\t?");
			else if(major == 4)
				printf("\ttty%d",minor);
			else if(major == 136)
				printf("\tpts/%d",minor);
			else
			{
				puts("other major value");
				return ;
			}
			printf("\t%c",state);
			if(nice < 0)
				printf("<");
			else if(nice > 0)
				printf("N");
			if(VmLck > 0)
				printf("L");
			if(session == pid)
				printf("s");
			if(num_threads > 1)
				printf("l");
			if(tpgid > 0)
				printf("+");
			time = utime + stime;
			time/=(unsigned long int)sysconf(_SC_CLK_TCK);
			min = time/60;
			sec = time % 60;
			hour = min/60;
			min = min % 60;
			day = hour / 24;
			hour = hour % 24;
			if(day > 0)
				printf("\t[%.2d-]%.2d:%.2d:%.2d",day,hour,min,sec);
			else if(hour > 0)
				printf("\t%.2d:%.2d:%.2d",hour,min,sec);
			else
				printf("\t%.2d:%.2d",min,sec);
			printf("\t");
			while((c = fgetc(fp)) != EOF && width)
			{
				count++;
				printf("%c",c);
				width--;
			}
			if(count == 0)
				printf("[%s\b]",comm+1);
			fclose(fp);
			puts("");
		}
		errno = 0;
	}
	if(closedir(proc)==-1)
		puts("/proc directory closing error");
}