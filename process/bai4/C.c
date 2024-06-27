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
		printf("Im C process, my pid is: %d\n", getpid());
        
        wait(&status);
        fd = open("sample4.txt" , O_RDWR| O_CREAT);
        lseek(fd, 45, 0);
        write(fd , "Im C process" , sizeof("Im C process")); 
        close(fd);
        exit(EXIT_SUCCESS);
	}
	else if( pid == 0) 
	{
        printf("Im C' process, my pid is: %d\n", getpid());
        fd = open("sample2.txt" , O_RDWR| O_CREAT);
        lseek(fd, 15, 0);
        write(fd , "Im C' process" , sizeof("Im C' process")); 
        close(fd);
        exit(EXIT_SUCCESS);
    }
	return 0;
}