#include <stdio.h>
#include <stdlib.h>

#include "shellPrompt.c"
#include "welcomeScreen.c"
#include "commandHandler.c"
#include "t.h"

int main(){
    char *lines;
    char *command[MAXSIZE];
    int commandnum;
    welcomeScreen();
    //shellPrompt();
    while(1){
        shellPrompt();
        lines = readline("\n >>");
        add_history(lines);
        //fgets(lines,MAXSIZE,stdin);
        if((command[0] = strtok(lines," \t\n")) == NULL)//如果输入的是空命令，则不执行下面语句继续
            continue;
        commandnum = 1;
        while((command[commandnum] = strtok(NULL," \t\n")) != NULL)
            commandnum++;
        commandHandler(commandnum,command);
    }
    free(lines);
    exit(1);
}