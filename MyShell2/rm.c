#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include<unistd.h>

int main(int argc, char * argv[]){

    if(argc ==1)
    {
        printf("%s\n", "rm: missing operands");
    }

    
    else if(argc==2 && (strcmp(argv[1],"-v")==0 || strcmp(argv[1],"-i")==0))
    {
        printf("%s\n", "rm: missing operands");
    }

    else if(argc==2)
    {
        int check;
        check=remove(argv[1]);

        if(check!=0)
        {   
            printf("rm: cannot remove file");
        }

    }

    else if(argc==3 && ((strcmp(argv[1],"-v")==0 && strcmp(argv[2],"-i")==0) || (strcmp(argv[1],"-i")==0 && strcmp(argv[2],"-v")==0)))
    {
        printf("%s\n", "rm: missing operands");
    }


    else if(argc>=3 && strcmp(argv[1],"-v")==0 && strcmp(argv[2],"-i")!=0)
    {
        for(int i=2; i<argc; i++)
        {
            int check;
            check=remove(argv[i]);

            if(check==0)
            {
                printf("rm: successfully removed file '%s'\n",argv[i]);
            }
            else
            {
           
                printf("rm: cannot remove file");
            }
        }

    }


    else if(argc>=3 && strcmp(argv[1],"-i")==0 && strcmp(argv[2],"-v")!=0)
    {
        char accept;
        printf("rm: remove all files? (Y/N)\n");
        scanf("%c",&accept);

        if(accept=='y' || accept=='Y')
        {
            for(int i=2; i<argc; i++)
            {
            
                int check;
                check=remove(argv[i]);

                if(check!=0)
                {
           
                    printf("rm: cannot remove file");
                }
            }
        }

    }

    else if(argc>=4 && ((strcmp(argv[1],"-v")==0 && strcmp(argv[2],"-i")==0) || (strcmp(argv[1],"-i")==0 && strcmp(argv[2],"-v")==0)))
    {
        char accept;
        printf("rm: remove all files? (Y/N)\n");
        scanf("%c",&accept);

        if(accept=='Y' || accept=='y')
        {
            for(int i=3; i<argc; i++)
            {
                int check;
                check=remove(argv[i]);

                if(check==0)
                {
                    printf("rm: successfully removed file '%s'\n",argv[i]);
                }

                else
                {
            
                    printf("rm: cannot remove file");
                }

            }
        }

    }

    else if(argc>=3)
    {
        for(int i=1; i<argc; i++)
        {
            int check;
            check=remove(argv[i]);

            if(check!=0)
            {   
                printf("rm: cannot remove file");
            }
        }

    }

    else
    {
        printf("rm: invalid option(s)\n");
    }


    return 0;
}