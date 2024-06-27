#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024

int main() {
    mqd_t mq;
    char buffer[MAX_SIZE];
    ssize_t bytes_read;
    unsigned int prio = 2;
    struct mq_attr attr;

    // Open the message queue
    mq = mq_open(QUEUE_NAME, O_RDONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    // Get the attributes of the message queue
    if (mq_getattr(mq, &attr) == -1) {
        perror("mq_getattr");
        mq_close(mq);
        exit(1);
    }

    printf("Message Queue Attributes:\n");
    printf("mq_flags: %ld\n", attr.mq_flags);
    printf("mq_maxmsg: %ld\n", attr.mq_maxmsg);
    printf("mq_msgsize: %ld\n", attr.mq_msgsize);
    printf("mq_curmsgs: %ld\n", attr.mq_curmsgs);

    printf("Receiving messages...\n");
    bytes_read = mq_receive(mq, buffer, MAX_SIZE, &prio);
    if (bytes_read >= 0)
    {
        buffer[bytes_read] = '\0';
        printf("Received (priority %u): %s\n", prio, buffer);
    } 
    else 
    {
        perror("mq_receive");
        exit(1);
    }
    
    // Close the message queue
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}
