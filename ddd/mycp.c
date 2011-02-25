#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int fd;
    int n = 0;
    int fd1;
    ssize_t len;
    char  a[100];
    struct stat buf1;
    
    fd = open("akaedu.c", O_RDWR|O_CREAT, 0777);
    fd1 = open("mycp", O_RDWR|O_CREAT, 0777);
    if(fd < 0 || fd1 < 0)
    {
        printf("open failed\n"); 
        return 1;
    }

    n = fstat(fd, &buf1);
    len = read(fd, a, buf1.st_size);
    if(len < 0)
    {
        printf("read error!\n");
        return(1);
    }

    len = write(fd1, a, len);
    if(len < 0)
    {
        printf("write error!\n");
        return(1);
    }

    close(fd);
    close(fd1);

    return 0;
}
