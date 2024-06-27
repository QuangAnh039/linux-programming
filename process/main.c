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
    int var1 = 1;
    printf("hello\n");
	if( (pid = fork()) > 0) 
	{
		printf("Im father process, my pid is: %d and my parrent pid is: %d\n", getpid(), getppid());
        printf("%d\n", ++var1);
	}
	else if( pid == 0) 
	{
        printf("Im child process, my pid is: %d and my parrent pid is: %d\n", getpid(), getppid());
        printf("%d\n", ++var1);
        exit(EXIT_SUCCESS);
    }
	return 0;
}