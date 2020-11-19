#include<stdio.h>
#include<string.h>
#include<getopt.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
#include<utmp.h>
#include<string.h>
/**mywho函数是调用系统数据文件的核心程序；
***它首先调用系统数据文件的接口函数，然后逐条将其数据保存下来；
***根据选项的标记为，然后输出不同的信息
***关闭系统数据文件
***/
void opt_q(){
    struct utmp *um;
    int users = 0;      //当命令选型为 -q, 用来保存用户数量
    /** 
     * 函数说明：getutent()用来从utmp 文件(/var/run/utmp)中读取一项登录数据, 
     * 该数据以utmp 结构返回. 第一次调用时会取得第一位用户数据, 之后每调用一次就会返回下一项数据, 
     * 直到已无任何数据时返回NULL。
    */
        while ((um == getutent()))
        {
            if (um->ut_type != USER_PROCESS) /*  利用 utmp 结构的ut_type域，过滤出普通进程   Normal process.  */
            {
                continue;
            }
            printf("%-2s  ", um->ut_user);
            users += 1;
        }

        printf("\n# users = %d\n", users);
        endutent();
}
    //打印各栏标题头部
void opt_H()
    {
        struct utmp *um;
        char timebuf[24];
        printf("%-12s%-12s%-20.20s    %s\n","NAME", "LINE", "TIME", "COMMENT");
  //此处处理的是 utmp 文件的内容
    while ((um = getutent()))
    {
        // 利用 utmp 结构的ut_type域，过滤出普通进程  
        if (um->ut_type != USER_PROCESS)
        {
            continue;
        }

        time_t tm;
        tm = (time_t)(um->ut_tv.tv_sec);
        strftime(timebuf, 24, "%F %R", localtime(&tm));
        printf("%-12s%-12s%-20.20s (%s)\n", um->ut_user, um->ut_line, timebuf, um->ut_host);
    }

    endutent();
 }
void opt_No()
    {
        struct utmp *um;
        char timebuf[24];
  //此处处理的是 utmp 文件的内容
    while ((um = getutent()))
    {
        // 利用 utmp 结构的ut_type域，过滤出普通进程  
        if (um->ut_type != USER_PROCESS)
        {
            continue;
        }

        time_t tm;
        tm = (time_t)(um->ut_tv.tv_sec);
        strftime(timebuf, 24, "%F %R", localtime(&tm));
        printf("%-12s%-12s%-20.20s (%s)\n", um->ut_user, um->ut_line, timebuf, um->ut_host);
    }

    endutent();
 }
 int main(int argc,char *argv[]){
     if(argc == 1){
         opt_No();
     }else if(argc == 2 && (strcmp(argv[1],"-q")==0) ){
         opt_q();
     }else if(argc == 2 && (strcmp(argv[1],"-H")==0)){
         opt_H();
     }else{
         printf("参数输入错误！\n");
     }
 }
