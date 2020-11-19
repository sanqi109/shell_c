#include <stdio.h> 
#include <time.h> 
#include<string.h>
#include<stdlib.h>
#define buf_len 256

int main(int argc, char* argv[]) 
{ 
  
  if(argc==1)
  { 
    time_t t = time(NULL); 
    if(t==-1)
    { 
    	printf("time() function failed\n");
    	return 1;
    }

    struct tm* local = localtime(&t); 
    char local_str[buf_len];
  	if(local==NULL)
  	{
  		printf("localtime() function failed\n");
  		return 1;
  	}
  	
    strftime(local_str, buf_len,"%a %b %d %X %Z %Y",local); 
    printf("%s\n",local_str);
  	
  }

  else if(argc==2 && strcmp(argv[1],"-u")==0)
  {
  	time_t t = time(NULL); 
    if(t==-1)
    {
    	printf("time() function failed\n");
    	return 1;
    }

    struct tm* local = gmtime(&t); 
    char local_str[buf_len];
  	if(local==NULL)
  	{
  		printf("gmtime() function failed\n");
  		return 1;
  	}
  	
    strftime(local_str, buf_len,"%a %b %d %X %Z %Y",local); 
    printf("%s\n",local_str);
  	
  }


  else if(argc==2 && strcmp(argv[1],"-I")==0)
  { 
    time_t t = time(NULL); 
    if(t==-1)
    {
    	printf("time() function failed\n");
    	return 1;
    }

    struct tm* local = localtime(&t); 
    char local_str[buf_len];
  	if(local==NULL)
  	{
  		printf("localtime() function failed\n");
  		return 1;
  	}
  	
    strftime(local_str, buf_len,"%F",local); 
    printf("%s\n",local_str);
  	
  }

  else if(argc==2)
  {
  		printf("%s\n", "date: invalid option");
  }

  else if(argc==3 && ((strcmp(argv[1],"-u")==0 && strcmp(argv[2],"-I")==0) || (strcmp(argv[1],"-I")==0 && strcmp(argv[2],"-u")==0)))
  {
  	
  	time_t t = time(NULL); 
    if(t==-1)
    {
    	printf("time() function failed\n");
    	return 1;
    }

    struct tm* local = gmtime(&t); 
    char local_str[buf_len];
  	if(local==NULL)
  	{
  		printf("gmtime() function failed\n");
  		return 1;
  	}
  	
    strftime(local_str, buf_len,"%F",local); 
    printf("%s\n",local_str);
  	
  }

  else 
  {
  		printf("%s\n", "date: invalid option(s)");
  }


    return 0; 

} 