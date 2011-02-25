#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int fd0, fd1;
    struct stat buf;
    int len = 0;
    int *p0, *p1;

    fd0 = open("hello", O_RDWR);
    fd1 = open("copy", O_RDWR|O_CREAT, 0777);
    if(fd0 < 0 || fd1 < 0)
    {
        perror("open");
        exit(1);
    }
    fstat(fd0, &buf);    
    len = buf.st_size;
    lseek(fd1, len-1, SEEK_SET);
    write(fd1, "1", 1);
    p1 = mmap(NULL, len, PROT_WRITE, MAP_SHARED, fd1, 0);
    if(p1 == MAP_FAILED)
    {
        perror("mamp1");
        exit(1);
    }
    p0 = mmap(NULL, len, PROT_READ, MAP_SHARED, fd0, 0);
    if(p0 == MAP_FAILED)
    {
        perror("mamp0");
        exit(1);
    }
    memcpy(p1, p0, len);
    close(fd0);
    close(fd1);
    munmap(p0, len);
    munmap(p1, len);

    return 0;
}
