#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

char *msg1 = "hello, world #1";

int main()
{
    pid_t child_pid;
    int fds[2];
    int byte_read = 0;
    char in_buff[100];

    if (pipe(fds) < 0) 
    {
        printf("pipe() unsuccessfully\n");
        exit(1);
    }

    child_pid = fork();
    if(child_pid == 0)
    {
        printf("Im child process! my pid is: %d\n", getpid());
        while(1)
        {
            byte_read = read(fds[0], in_buff, 100);
            if(byte_read == -1)
            {
                printf("Read failed!\n");
                exit(1);
            }
            else if(byte_read == 0)
            {
                printf("empty pipe!\n");
                break;
            }
            else 
            {
                printf("Message: %s\n", in_buff);
            }
        }
    }
    else
    {
        printf("Im parents process! my pid is: %d\n", getpid());
        // if (close(fds[0]) == -1)
        // {
        //     printf("close(fds[0]) failed\n");
        // } // read end is unused
                
        write(fds[1], msg1, 100);
        write(fds[1], msg1, 100);
        write(fds[1], msg1, 100);

        if (close(fds[1]) == -1)
        {
            printf("close(fds[0]) failed\n");
        } // reader will see end-of-pipe
        while(1);
    }
    
}