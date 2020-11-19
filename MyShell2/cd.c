#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *args[]){  // cd
    if(args[1] == NULL){  //args[0]用来保存cd
        chdir(getenv("HOME"));  //如果不输入路径 会默认进入home对应目录
        return 1;
    }else{
        int flag  = chdir(args[1]);
        if(flag == -1){
            printf("%s:","No such directiry!\n");
            return -1;
        }
    }
    return 0;
}