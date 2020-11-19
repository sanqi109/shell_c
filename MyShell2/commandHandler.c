#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "t.h"

char * finalfilepath;
int parse_redirect(int argc,char *args[]){
    outFlag = 0;
    inFlag = 0;
    append = 0;
    for(int i=0;i<argc;i++){
        if(strcmp(args[i],">") == 0){
            outFlag = i+1;
            return outFlag;
        }else if(strcmp(args[i],">>") == 0){
            append = i+1;
            return append;
        }else if(strcmp(args[i],"<") == 0){
            inFlag = i+1;
            return inFlag;
        }
    }
    return 0;
}

void execute_redirect(int argc,char *args[]){
    pid_t pid = fork();
    if(pid<0){
        printf("fork failed\n");
    }else if(pid == 0){
        if(parse_redirect(argc,args)){
            char * argv[1024] ;
            for(int i=0;i<parse_redirect(argc,args)-1;i++){
                argv[i] = args[i];
            }
            char *filename = args[parse_redirect(argc,args)];
            if(outFlag > 0){
                freopen(filename,"w",stdout);
                execvp(argv[0],argv);
                fclose(stdout);
                exit(0);
            }else if(append > 0){
                freopen(filename,"a",stdout);
                execvp(argv[0],argv);
                fclose(stdout);
                exit(0);
            }else if(inFlag > 0){
                argv[parse_redirect(argc,args)-1] = args[parse_redirect(argc,args)];
                freopen(filename,"r",stdin);
                execvp(argv[0],argv);
                fclose(stdin);
                exit(0);
            }
        }else{
             execvp(args[0],args);
             exit(0); 
        }
    }else{
        wait(NULL);
        return;
    }
    
}

int commandHandler(int argc,char *args[]){
    int flag = 1;
    //strcmp(str1,str2)，若str1=str2，则返回零；若str1<str2，则返回负数；若str1>str2，则返回正数。
    if(strcmp(args[0],"exit") == 0){
        exit(0);
    }else if(strcmp(args[0],"cd") == 0){
        //chdir(args[1]);flag = 0;
        if(args[1] == NULL){  //args[0]用来保存cd
        chdir(getenv("HOME"));  //如果不输入路径 会默认进入home对应目录
    }else{
        if(chdir(args[1]) == -1){
            printf("%s:","No such directiry!\n");
        }
    }
        flag = 0;
    }else if(strcmp(args[0],"pwd") == 0){ // 1
        args[0] = "/home/lc/桌面/c++操作系统程序/MyShell2/pwd";
    }else if(strcmp(args[0],"date") == 0){ //1
        args[0] = "/home/lc/桌面/c++操作系统程序/MyShell2/date";
    }else if(strcmp(args[0],"ps") == 0){       //1
        args[0] = "/home/lc/桌面/c++操作系统程序/MyShell2/ps";
    }else if(strcmp(args[0],"cat") == 0){    // 
        args[0] = "/home/lc/桌面/c++操作系统程序/MyShell2/cat";
    }else if(strcmp(args[0],"clear") == 0){    //1
        args[0] = "/home/lc/桌面/c++操作系统程序/MyShell2/clear";
    }else if(strcmp(args[0],"cp") == 0){    //1
        args[0] = "/home/lc/桌面/c++操作系统程序/MyShell2/cp";
    }else if(strcmp(args[0],"mkdir") == 0){    //1
        args[0] = "/home/lc/桌面/c++操作系统程序/MyShell2/mkdir";
    }else if(strcmp(args[0],"ping") == 0){    
        args[0] = "/home/lc/桌面/c++操作系统程序/MyShell2/ping";
    }else if(strcmp(args[0],"rm") == 0){    //1
        args[0] = "/home/lc/桌面/c++操作系统程序/MyShell2/rm";
    }else if(strcmp(args[0],"ls") == 0 && ((args[1]==NULL) || (strcmp(args[1],"-l") == 0))){
        args[0] = "/home/lc/桌面/c++操作系统程序/MyShell2/ls";
    }else if(strcmp(args[0],"ls") == 0 ){
        args[0] = "/home/lc/桌面/c++操作系统程序/MyShell2/ls2";
    }else if(strcmp(args[0],"who") == 0 ){
        args[0] = "/home/lc/桌面/c++操作系统程序/MyShell2/who";
    }else if(strcmp(args[0],"tac") == 0 ){
        args[0] = "/home/lc/桌面/c++操作系统程序/MyShell2/tac";
    }else{
        printf("%s不是可用的命令\n",args[0]);
    }

    if(flag){
        execute_redirect(argc,args);
    }

    return 1;
}