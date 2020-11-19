#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
#include <libgen.h>
  
void mkdir_recursive(char *path)
{
    char *subpath, *fullpath;

    fullpath = strdup(path);
    subpath = dirname(fullpath);
    if (strlen(subpath) > 1)
        mkdir_recursive(subpath);
    mkdir(path,0777);
      
}

int main(int argc, char** argv) 
{ 
    if(argc==1) 
    {
        printf("mkdir: missing operands\n");
    }


    else if(argc==2 && (strcmp(argv[1],"-v")==0 || strcmp(argv[1],"-p")==0))
    {
        printf("%s\n", "mkdir: missing operands");
    }

    else if(argc==2) //else if 2
    {
        
        int check; 
  
        check = mkdir(argv[1],0777); 
        //printf("else if 2..\n");
        // check if directory is created or not 
        if (check!=0) 
        { 
            printf("mkdir failed"); 
        } 
  
    }

    else if(argc==3 && ((strcmp(argv[1],"-v")==0 && strcmp(argv[2],"-p")==0) || (strcmp(argv[1],"-p")==0 && strcmp(argv[2],"-v")==0)))
    {
        printf("%s\n", "mkdir: missing operands");
    }

    else if(argc>=3 && strcmp(argv[1],"-v")==0 && strcmp(argv[2],"-p")!=0) //else if 3
    {
        for(int i=2; i<argc; i++)
        {
            int check; 
  
            check = mkdir(argv[i],0777); 
            // printf("else if -v..\n");
            // check if directory is created or not 
            if (!check) 
            {    
                printf("mkdir: created directory %s\n",argv[i]);
            }    

            else
            {
                printf("mkdir failed"); 
              
            }
        }

    }

    else if(argc>=3 && strcmp(argv[1],"-p")==0 && strcmp(argv[2],"-v")!=0) //else if 4
    {
        for(int i=2; i<argc; i++)
        {
        
            char* finalpath;
            char cwd[1024]; 

            if (getcwd(cwd, sizeof(cwd)) == NULL)
            {
                printf("mkdir failed"); 

                continue;
            }   
    
            finalpath= strcat(cwd,"/");
            finalpath= strcat(finalpath,argv[i]);

            mkdir_recursive(finalpath);
            
            
        }

    }



    else if(argc>=4 && ((strcmp(argv[1],"-v")==0 && strcmp(argv[2],"-p")==0) || (strcmp(argv[1],"-p")==0 && strcmp(argv[2],"-v")==0))) //else if 7
    {
        for(int i=3; i<argc; i++)
        
        {
            char* finalpath;
            char cwd[1024]; 

            if (getcwd(cwd, sizeof(cwd)) == NULL)
            {
                printf("mkdir failed"); 
                
                continue;
            }   
    
            finalpath= strcat(cwd,"/");
            finalpath= strcat(finalpath,argv[i]);

            mkdir_recursive(finalpath);
            printf("%s\n", finalpath);

        }

    }

    else if(argc>=3)
    {
        for(int i=1; i<argc;i++)
        {
            int check; 
            check = mkdir(argv[i],0777); 
         
            if(check!=0)
            {
                 printf("mkdir failed"); 

               
            }
        }

    }

    else //else if 8
    {

        printf("%s\n", "mkdir: invalid option(s)");
    }



} 