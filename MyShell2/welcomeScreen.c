#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void welcomeScreen(){
        /*
        int i=0;
        char a[12] = {0};
        char *lab = "-\\|/";
        while(i<=10){
                printf("[%-21s][%d%%][%c]\r",a,i*10,lab[i%4]);
                sleep(1);
                fflush(stdout);
                a[i++] = '#';
                a[i] = '\0';
        }
        printf("\n");
        */
        const char* blank = "\e[1;1H\e[2J";
        printf("%s\n",blank);
        printf("\n\t============================================\n");
        printf("\t               Simple C Shell\n");
        printf("\t--------------------------------------------\n");
        printf("\t      Author: 刘晨 王禧龙 黄正彬\n");
        printf("\t============================================\n");
        printf("\n\n");
}