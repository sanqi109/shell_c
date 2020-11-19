#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>  // mkdir和rmdir的头文件

void removeDirectiry(char *args[]){ // rmdir

    int state = rmdir(args[1]); // name
    if(state == -1){
        printf("failed to remove directiry.\n");
    }
}