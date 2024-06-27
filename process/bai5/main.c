#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
void func()
{
    printf("Im in func\n");
    wait(NULL);
}
int main()
{
	int pid; 	
    int status;
    int var1 = 1;
	if( (pid = fork()) > 0) 
	{
        signal(SIGCHLD, func);
		printf("Im father process, my pid is: %d and my parrent pid is: %d\n", getpid(), getppid());
        printf("%d\n", ++var1);
        while(1);
	}
	else if( pid == 0) 
	{   
        printf("Im child process, my pid is: %d and my parrent pid is: %d\n", getpid(), getppid());
        printf("%d\n", ++var1);
        while(1);
        exit(EXIT_SUCCESS);
    }
    
	return 0;
}