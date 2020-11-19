#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h> // stat头文件
#include <pwd.h>  // ls -l getpwuid
#include <grp.h>  // ls -l getgrgid
#include <time.h> // ls-l locatetime

#define MAXSIZE 1024
#define BLUE "\x1b[94m"    // \x1b 表示ESC
#define GREEN "\x1b[92m"
#define WRITE "\x1b[37m"

void nameFile(struct dirent* name,char* followup)
{
    if(name->d_type == DT_REG)          // regular file
    {
        printf("%s%s%s",BLUE, name->d_name, followup);
    }
    else if(name->d_type == DT_DIR)    // a directory
    {
        printf("%s%s%s",GREEN, name->d_name, followup);
    }
    else                              // unknown file types
    {
        printf("%s%s%s",WRITE, name->d_name, followup);
    }
}
void listFiles(){ // ls
    struct dirent **listr;
    int listn = scandir(".",&listr,0,alphasort);
    if(listn >= 0){
        for(int i=0;i<listn;i++){
            if(listr[i]->d_name[0]=='.'){
                continue;
            }else{
                nameFile(listr[i],"\t"); 
            }
            if((i+1)%4==0){
                printf("\n"); //4个一行
            }
        }
        printf("%s\n",WRITE);
    }else{
        printf("error in ls");
    }
}

void listFilesL(){ // ls -l
    struct dirent **listr;
    struct stat details;
    char timer[14];
    int listn = scandir(".",&listr,0,alphasort);
    if(listn>0){
        printf("total %d objects in this directiry\n",listn-2);
        for(int i=0;i<listn;i++){
            if(listr[i]->d_name[0]=='.'){
                continue;
            }else if(stat(listr[i]->d_name,&details) == 0){ //Get file attributes for FILE and put them in BUF.
             // stat函数执行成功则返回0,失败返回-1
                printf("%1s",(S_ISDIR(details.st_mode))  ? "d" : "-");
                printf("%1s",(details.st_mode & S_IRUSR) ? "r" : "-");
                printf("%1s",(details.st_mode & S_IWUSR) ? "w" : "-");
                printf("%1s",(details.st_mode & S_IXUSR) ? "x" : "-");
                printf("%1s",(details.st_mode & S_IRGRP) ? "r" : "-");
                printf("%1s",(details.st_mode & S_IWGRP) ? "w" : "-");
                printf("%1s",(details.st_mode & S_IXGRP) ? "x" : "-");
                printf("%1s",(details.st_mode & S_IROTH) ? "r" : "-");
                printf("%1s",(details.st_mode & S_IWOTH) ? "w" : "-");
                printf("%1s",(details.st_mode & S_IXOTH) ? "x" : "-");
                // links associated - owner name - group name
                printf("%2ld ",(unsigned long)(details.st_nlink));
                printf("%s ",(getpwuid(details.st_uid))->pw_name);
                printf("%s ",(getgrgid(details.st_gid))->gr_name);
                // file size (bytes) - time modified - name
                printf("%5lld ",(unsigned long long)details.st_size);
                strftime (timer,14,"%h %d %H:%M",localtime(&details.st_mtime));
                printf("%s ",timer);
                nameFile(listr[i],"");
                printf("%s\n",WRITE);
            }
        }
        printf("%s\n",WRITE);
    }else{
        printf("Empty directiry\n");
    }
}
int main(int argc,char *argv[]){
    if(argc == 1){
        listFiles();
    }else if(argc == 2 && (strcmp(argv[1],"-l")==0)){
        listFilesL();
    }
}