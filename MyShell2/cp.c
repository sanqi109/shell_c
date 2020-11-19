#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char *args[]){
    int file1,file2;
    char *buff[128];
    file1=open(args[1],O_RDONLY);
    if(file1 == -1){
        printf("copy file failed 1\n");
        return 1;
    }
    file2=open(args[2],O_RDWR|O_CREAT,0777);
    if(file2 == -1){
        printf("copy file failed 2\n");
        close(file1);
        return 2;
    }
    //该函数的返回值为-1时，表示读取数据失败；返回值>0时，表示读出的字节数；
    //返回值等于0时，表示已经读完了，因此没有数据可读了
    int fd1 = read(file1,buff,128);
    if(fd1==-1){
        printf("copy file failed 3\n");
        return 3;
    }
    while(fd1>0){
        int ret = write(file2,buff,fd1);
        if(ret==-1){
            printf("copy file failed 4\n");
            return 4;
        }
        fd1 = read(file1,buff,128);
        if(fd1==-1){
            printf("copy file failed 5\n");
            return 5;
        }
    }
    close(file2);
    close(file1);
    return 0;
}