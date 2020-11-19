#ifndef __T_H__
#define __T_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAXSIZE 1024

char * shell;

int inFlag = 0;
int outFlag = 0;
int append = 0;

void welcomeScreen();
void shellPrompt();
int commandHandler(int argc,char *args[]);

#endif // !__T_H__
