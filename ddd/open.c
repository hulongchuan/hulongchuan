#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int fd;
    ssize_t len;
    char *buf = "hello";
 
    fd = open("akaedu.c", O_RDWR|O_CREAT, 0777);
    if(fd < 0)
    {
        printf("open failed\n"); 
        return 1;
    }
    len = write(fd, buf, strlen(buf));
    close(fd);

    return 0;
}
