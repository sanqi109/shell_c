#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){ // clear
    const char* blank = "\e[1;1H\e[2J";
    write(STDOUT_FILENO,blank,12); // STDOUT_FILENO：向屏幕输出,第三个参数是一次写入的字节数
    return 0;
}