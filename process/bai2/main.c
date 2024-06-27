#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
	int pid; 	
    int fd;
    char buf1[13] = "hello world";
    char buf2[13] = "hello worll";
    int numb_read, numb_write;
    int status;

	if( (pid = fork()) > 0) 
	{
		printf("Im father process, my pid is: %d\n", getpid());
        fd = open("hello.txt", O_RDWR | O_CREAT , 0666);   
        if (-1 == fd) 
        { 
	        printf("open() hello.txt failed\n");
        }
        numb_write = pwrite(fd, buf1, strlen(&buf1[0]), 0);  
        close(fd);
        printf("Write %d bytes to hello.txt\n", numb_write);
        wait(&status);
	}
	else if( pid == 0) 
	{   
        printf("Im child process, my pid is: %d\n", getpid());
        fd = open("hello.txt", O_RDWR | O_CREAT , 0666);   
        if (-1 == fd) 
        { 
	        printf("open() hello.txt failed\n");
        }

        numb_write = pwrite(fd, buf2, strlen(&buf1[0]), 13);  
        close(fd);
        printf("Write %d bytes to hello.txt\n", numb_write);
    }
	return 0;
}