#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MES_TRY "try again\n"

int main(int argc, const char *argv[])
{
    int fd, n;
    char buf[10];
    
    fd = open("/dev/tty", O_RDONLY|O_NONBLOCK);
    if(fd < 0)
    {
        perror("open /dev/tty");
        exit(1);
    }
    lp:
    n = read(fd, buf, 10);
    if(n < 0)
    {
        if(errno == EAGAIN)
        {
            sleep(1);
            write(STDOUT_FILENO, MES_TRY, strlen(MES_TRY));
            goto lp;
        }
        printf("%d\n", n);
        perror("read /dev/tty");
        exit(1);
    }
    write(STDOUT_FILENO, buf, n);
    close(fd);

    return 0;
}
