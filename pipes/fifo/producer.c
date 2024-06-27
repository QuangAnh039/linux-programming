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

    mkfifo("./myfifo", 0666);
    while(1)
    {
        printf("Message to comsumer : "); 
        fflush(stdin);
        fgets(buff, 100, stdin);   
        //   
        fd = open("./myfifo", O_WRONLY);
        write(fd, buff, strlen(buff) +1);
        close(fd);
        //
    }
    return 0;
}