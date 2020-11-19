#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

extern int alphasort();

int file_select(const struct dirent* entry)                   // -a -r . ..    .代表当前文件夹   ..代表上层文件夹
{
	if((strcmp(entry->d_name,".")==0)|| (strcmp(entry->d_name,"..")==0))
		return 0;
	else 
		return 1;
}


int main(int argc, char** argv)
{
	struct dirent** filelist;
	int count;

	if(argc<1)
	{
		return 0;
	}

	else if(argc==1)
	{
		count=scandir(".",&filelist,file_select,alphasort);         // 

		if(count<0)
		{
			printf("No files in the directory");
			//perror("scandir");
		}

		else
		{
			for(int i=0; i<count; i++)
			{
				printf("%s\n", filelist[i]->d_name);
			}
		}

	}

	else if(argc==2 && strcmp(argv[1],"-a")==0)
	{
		count=scandir(".",&filelist,NULL,alphasort);    //NULL代表全部都要
		if(count<0)
		{
			printf("No files in the directory");
			//perror("scandir");
			
		}

		else
		{
			for(int i=0; i<count; i++)
			{
				printf("%s\n", filelist[i]->d_name);
			}
		}
	}

	else if(argc==2 && strcmp(argv[1],"-r")==0)						//相反次序
	{

		count=scandir(".",&filelist,file_select,alphasort);

		if(count<0)
		{
			printf("No files in the directory");
			//perror("scandir");
			
		}

		else
		{
			
			for(int i=count-1; i>=0; i--)
			{
				printf(" %s\n", filelist[i]->d_name);
			}

		}

	}


	else if(argc==2)
	{
		printf("%s:\n",argv[1]);
		count=scandir(argv[1],&filelist,file_select,alphasort);

		if(count<0)
		{
			printf("No files in the directory");
			//perror("scandir");
			
		}

		else
		{
			for(int i=0; i<count; i++)
			{
				printf("%s\n", filelist[i]->d_name);
			}
		}

	}


	else if(argc==3 && ((strcmp(argv[1],"-r")==0 && strcmp(argv[2],"-a")==0) || (strcmp(argv[1],"-a")==0 && strcmp(argv[2],"-r")==0)))
	{

		count=scandir(".",&filelist,NULL,alphasort);

		if(count<0)
		{
			printf("No files in the directory");
			//perror("scandir");
			
		}

		else
		{
			
			for(int i=count-1; i>=0; i--)
			{
				printf(" %s\n", filelist[i]->d_name);
			}

		}

	}

	/*else if(argc==3 && ((strcmp(argv[1],"-r")!=0 || strcmp(argv[1],"-a")!=0) && (strcmp(argv[2],"-a")!=0 || strcmp(argv[2],"-r")!=0)))
	{
		printf("ls: invalid option(s)\n");
	}*/
	//else if()

	else if(argc>=3 && strcmp(argv[1],"-r")==0 && strcmp(argv[2],"-a")!=0)
	{
		for(int i=2; i<argc; i++)
		{
			printf("%s:\n",argv[i]);
			count=scandir(argv[i],&filelist,file_select,alphasort);

			if(count<0)
			{
				printf("No files in the directory");
				//perror("scandir");
			
			}

			else
			{
				for(int j=count-1; j>=0; j--)
				{
					printf("%s\n", filelist[j]->d_name);
				}
			}
		}

	}

	else if(argc>=3 && strcmp(argv[1],"-a")==0 && strcmp(argv[2],"-r")!=0)
	{
		for(int i=2; i<argc; i++)
		{
			printf("%s:\n",argv[i]);
			count=scandir(argv[i],&filelist,NULL,alphasort);

			if(count<0)
			{
				printf("No files in the directory");
			
			}

			else
			{
				for(int j=0; j<count; j++)
				{
					printf("%s\n", filelist[j]->d_name);
				}
			}

		}

	}

	


	else if(argc>=4 && ((strcmp(argv[1],"-r")==0 && strcmp(argv[2],"-a")==0) || (strcmp(argv[1],"-a")==0 && strcmp(argv[2],"-r")==0)))
	{
		for(int i=3; i<argc; i++)
		{
			printf("%s:\n",argv[i]);
			count=scandir(argv[i],&filelist,NULL,alphasort);

			if(count<0)
			{
				//printf("No files in the directory");
				perror("scandir");
				
			}

			else
			{
			
				for(int j=count-1; j>=0; j--)
				{
					printf(" %s\n", filelist[j]->d_name);
				}

			}
		}

	}

	else if(argc>=3)
	{
		for(int i=1; i<argc; i++)
		{
			printf("%s:\n",argv[i]);
			count=scandir(argv[i],&filelist,file_select,alphasort);

			if(count<0)
			{
				//printf("No files in the directory");
				perror("scandir");
				
			}

			else
			{
			
				for(int j=0; j<count; j++)
				{
					printf("%s\n", filelist[j]->d_name);
				}

			}
		}
	}

	else
	{
		printf("%s\n", "ls: invalid option(s)");
	}




}
