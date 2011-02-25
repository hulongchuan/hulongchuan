#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
    int fd;
    off_t currpos;
    
    fd = open("txt.c", O_RDWR | O_CREAT, 0777);
    if(fd < 0)
    {
        printf("open error\n");
        return 1;
    }
    currpos = lseek(fd, 100, SEEK_CUR);
    write(fd, "1", 1);
    close(fd);
    return 0;
}
