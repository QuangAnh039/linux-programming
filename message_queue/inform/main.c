#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define QUEUE_NAME  "/test_queue"

int main() {
    mqd_t mq;
    struct mq_attr attr;

    // Open the message queue
    mq = mq_open(QUEUE_NAME, O_RDONLY | O_CREAT, 0644, NULL);
    if (mq == (mqd_t)-1) 
    {
        perror("mq_open");
        exit(1);
    }

    // Get the attributes of the message queue
    if (mq_getattr(mq, &attr) == -1) 
    {
        perror("mq_getattr");
        mq_close(mq);
        exit(1);
    }

    // Print the attributes
    printf("Message Queue Attributes:\n");
    printf("mq_flags: %ld\n", attr.mq_flags);
    printf("mq_maxmsg: %ld\n", attr.mq_maxmsg);
    printf("mq_msgsize: %ld\n", attr.mq_msgsize);
    printf("mq_curmsgs: %ld\n", attr.mq_curmsgs);

    // Close the message queue
    mq_close(mq);

    return 0;
}
