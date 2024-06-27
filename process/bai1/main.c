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
    char buf1[13] = "hello world\n";
    char buf2[13];
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
        numb_write = write(fd, buf1, strlen(&buf1[0]));  
        close(fd);
        printf("Write %d bytes to hello.txt\n", numb_write);
        wait(&status);
	}
	else if( pid == 0) 
	{   
        sleep(2);
        printf("Im child process, my pid is: %d\n", getpid());
        fd = open("hello.txt", O_RDWR | O_CREAT , 0666);   
        read(fd, buf2, 12);
        printf("%s\n", buf2);
        close(fd);
    }
	return 0;
}