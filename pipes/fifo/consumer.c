#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char buff[100];
    int num_read = 0;
    fd = open("./myfifo", O_RDONLY);

    while(1)
    {
        num_read = read(fd, buff, 100);
        if(num_read != 0)
        {
            printf("%s", buff);
        }
    }
    close(fd);
    return 0;
}