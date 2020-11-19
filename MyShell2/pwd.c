#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
     char currentDirectory[1024]="";
     printf("%s\n",getcwd(currentDirectory,1024));
     return 0;
}