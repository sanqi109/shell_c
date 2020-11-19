#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#define SIZE 1000001
#define NLINE '\n'
int main(int argc, char *argv[])
{
    char buf[SIZE];
    char *p1, *p2, *p3, *p4;
    struct stat *fp;
    int fd;
    fp = (struct stat *)malloc(sizeof(struct stat));
    if (argc != 2)
    {
        printf("input error \n");
        return 1;
    }
    if ((fd = open(argv[1], O_RDONLY)) == -1)
    {
        printf("open error  \n");
        return 1;
    }
    if (fstat(fd, fp) == -1)
    {
        printf("fstat error\n");
        return 1;
    }
    if (fp->st_size > (SIZE - 1))
    {
        printf( "buffer size is not big enough \n");
        return 1;
    }
    if (read(fd, buf, fp->st_size) == -1)
    {
        printf( "read error.\n");
        return 1;
    }

    p1 = strchr(buf, NLINE);
    p2 = strrchr(buf, NLINE);
    *p2 = '\0';
    do
    {
        p2 = strrchr(buf, NLINE);
        p4 = p2;
        p3 = p2 + sizeof(char);
        printf("%s\n", p3);
        *p4 = '\0';
    } while (p2 != p1);

    if (p2 == p1)
    {
        *p2 = '\0';
        printf("%s\n", buf);
    }
    return 0;
}