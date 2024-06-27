#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct stat sb;
    if(argc != 2)
    {
        printf("invalid syntax!\n");
        return -1;
    }
    if (stat(argv[1], &sb) == -1) 
    {
        perror("stat");
        return 1;
    }
    printf("File type:                \n");
    switch (sb.st_mode & S_IFMT)
    {
        case S_IFBLK:
            printf("block device\n");
            break;
        case S_IFCHR:
            printf("character device\n");
            break;
        case S_IFDIR:
            printf("directory\n");
            break;
        case S_IFIFO:
            printf("FIFO/pipe\n");              
            break;
        case S_IFREG:
            printf("regular file\n");                 
            break;
        case S_IFSOCK:
            printf("socket\n");                  
            break;
        default: 
            printf("unknown?\n");                
            break;
    }
    printf("File size: %lld bytes\n", (long long)sb.st_size);
    printf("Last file modification:   %s\n", ctime(&sb.st_mtime));
    return 0;
}