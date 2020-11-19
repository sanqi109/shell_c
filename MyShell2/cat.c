#include<stdio.h>
#include<unistd.h> /*for STDOUT_FILENO*/
#include<stdlib.h> 
#include<string.h>

 
int  main (int argc,char *argv[])
{  
 
    if(argc==1)
    {
        printf("%s\n", "cat: missing operands");
    }

    else if(argc==2 && (strcmp(argv[1],"-n")==0 || strcmp(argv[1],"-E")==0))   //strcmp string compare  str1==str2 return 0 < return 负数， > return 正数
    {
        printf("%s\n", "cat: missing operands");
    }

    else if(argc==2)
    {
        FILE* fptr= fopen(argv[1],"r");										//fgets用法 从FILE定义的文件中取数据，三个参数，*str 字符数组指针，
																			//存储要读取的字符。 n 最大字符个数  stream FILE定义的文件读取。

        if(fptr==NULL)
        {
            printf("cat: unable to open the file %s\n",argv[1]);			
            
        }

        else
        {
            char line[255];
            while(fgets(line,sizeof(line),fptr))						//			while (true)
            {
                printf("%s",line);
                
            }

        }

    }

    else if(argc==3 && ((strcmp(argv[1],"-n")==0 && strcmp(argv[2],"-E")==0) || (strcmp(argv[1],"-E")==0 && strcmp(argv[2],"-n")==0)))
    {
        printf("%s\n", "cat: missing operands");
    }


    else if(argc>=3 && strcmp(argv[1],"-n")==0 && strcmp(argv[2],"-E")!=0)
    {
        for(int i=2; i<argc; i++)
        {
            int count=1;
            FILE* fptr= fopen(argv[i],"r");							//-n代表行数。第一列显示行数。

            if(fptr==NULL)
            {
                printf("cat: unable to open the file %s\n",argv[i]);
            
            }

            else
            {
                char line[255];
                while(fgets(line,sizeof(line),fptr))
                {
                    printf(" %d ",count );
                    printf("%s",line);
                    count++;
                }

            }
        }

    }

    else if(argc>=3 && strcmp(argv[1],"-E")==0 && strcmp(argv[2],"-n")!=0) 
    {
        for(int a=2; a<argc; a++)
        {
            int line_count=0;
            FILE* fptr= fopen(argv[a],"r");
            FILE* temp= fopen(argv[a],"r");

            if(fptr==NULL)
            {
                printf("cat: unable to open the file %s\n",argv[a]);
            
            }

            else
            {   
                char line[255];
                while(fgets(line,sizeof(line),temp))
                {
                    line_count++;
                }

                for(int i=0; i<line_count-1; i++)
                {
                    fgets(line,sizeof(line),fptr);

                    printf("$");
                    int j=1;
                    while(line[j]!='\0')
                    {
                        printf("%c", line[j]);
                        j++;
                    }

                }

                fgets(line,sizeof(line),fptr);
                if(strcmp(line,"\r\n")==0 || strcmp(line,"\n")==0)
                {
                    printf("$");
                    int j=1;
                    while(line[j]!='\0')
                    {
                        printf("%c", line[j]);
                        j++;
                    }
                }

                else
                    printf("%s",line);


            }
        }

    }

    else if(argc>=4 && ((strcmp(argv[1],"-n")==0 && strcmp(argv[2],"-E")==0) || (strcmp(argv[1],"-E")==0 && strcmp(argv[2],"-n")==0)))
    {
        for(int j=3; j<argc; j++)
        {
            int line_count=0;
            int count=1;
            FILE* fptr= fopen(argv[3],"r");
            FILE* temp= fopen(argv[3],"r");

            if(fptr==NULL)
            {
                printf("cat: unable to open the file %s\n",argv[2]);
            
            }

            else
            {   
                char line[255];
                while(fgets(line,sizeof(line),temp))
                {
                    line_count++;
                }

                for(int i=0; i<line_count-1; i++)
                {
                    fgets(line,sizeof(line),fptr);

                    printf("$   %d ",count);
                    printf("%s", line);
                    count++;

                }

                fgets(line,sizeof(line),fptr);
                if(strcmp(line,"\r\n")==0 || strcmp(line,"\n")==0)
                {
                    printf("$   %d",count);
                    printf("%s", line);
                }

                else
                    printf("    %d %s",count,line);


            }
        }

    }

    else if(argc>=3)
    {
        for(int i=1; i<argc; i++)
        {
            FILE* fptr= fopen(argv[i],"r");

            if(fptr==NULL)
            {
                printf("cat: unable to open the file %s\n",argv[i]);
            
            }

            else
            {
                char line[255];
                while(fgets(line,sizeof(line),fptr))
                {
                    printf("%s",line);
                
                }

            }
        }
    }

    else
    {
        printf("%s\n", "cat: invalid option(s)");
    }


    return 0;

}