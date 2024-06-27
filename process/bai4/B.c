#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	int pid; 	
    int status;
    int fd;
	if( (pid = fork()) > 0) 
	{
		printf("Im B process, my pid is: %d\n", getpid());
        wait(&status);
        fd = open("sample3.txt" , O_RDWR| O_CREAT);
        lseek(fd, 30, 0);
        write(fd , "Im B process" , sizeof("Im B process")); 
        close(fd);
        exit(EXIT_SUCCESS);
	}
	else if( pid == 0) 
	{
        printf("Im B' process, my pid is: %d\n", getpid());
        fd = open("sample1.txt" , O_RDWR| O_CREAT);
        write(fd , "Im B' process" , sizeof("Im B' process")); 
        close(fd);
        exit(EXIT_SUCCESS);
    }
	return 0;
}
