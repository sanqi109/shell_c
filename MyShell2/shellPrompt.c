#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include "t.h"
 void shellPrompt(){
    //格式是："<user>@<host> <cwd> >"
    char hostname[1024] = "";
    char currentDirectory[1024]="";
    //gethostname这个函数，调用后，会将主机名保存在name里面。而len是name的大小。
    gethostname(hostname,sizeof(hostname));
    printf("%s@%s:%s$ ",getenv("LOGNAME"),hostname,getcwd(currentDirectory,1024));
    //shell = strcat(strcat(strcat(shell,getenv("LOGNAME")),hostname),getcwd(currentDirectory,1024));
    
}