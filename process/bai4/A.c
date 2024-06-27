#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() 
{
    pid_t pid1, pid2;
    int status;

    // Tạo tiến trình con đầu tiên
    pid1 = fork();

    if (pid1 < 0) 
    {
        // Lỗi khi tạo tiến trình
        perror("Fork failed");
        exit(1);
    } 
    else if (pid1 == 0) 
    {
        // Đây là tiến trình con đầu tiên
        printf("This is the B process. PID = %d\n", getpid());
        execl("./B", "./B", NULL);
        // Tiến trình con kết thúc với mã trả về 0
        //exit(0);
    } 
    else 
    {
        // Đây là tiến trình cha hoặc tiến trình con đầu tiên (nếu tiếp tục chạy từ cha)
        // Tạo tiến trình con thứ hai
        pid2 = fork();

        if (pid2 < 0) 
        {
            // Lỗi khi tạo tiến trình
            perror("Fork failed");
            exit(1);
        } else if (pid2 == 0) 
        {
            // Đây là tiến trình con thứ hai
            printf("This is the C process. PID =  %d\n", getpid());
            execl("./C", "./C", NULL);
            // Tiến trình con kết thúc với mã trả về 0
            //exit(0);
        } else 
        {
            // Đây là tiến trình cha
            // Chờ cả hai tiến trình con kết thúc
            waitpid(pid1, &status, 0);
            if (WIFEXITED(status)) 
            {
                printf("B process exited with status = %d\n", WEXITSTATUS(status));
            }

            waitpid(pid2, &status, 0);
            if (WIFEXITED(status)) 
            {
                printf("C process exited with status = %d\n", WEXITSTATUS(status));
            }

            printf("This is the A process. PID = %d\n", getpid());
        }
    }

    return 0;
}