#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024

int main() {
    mqd_t mq;
    char buffer[MAX_SIZE];
    struct mq_attr attr;

    // Initialize the queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    // Open the message queue
    mq = mq_open(QUEUE_NAME, O_WRONLY | O_CREAT, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    // Send messages with different priorities
    strcpy(buffer, "Message with priority 1");
    if (mq_send(mq, buffer, strlen(buffer) + 1, 1) == -1) {
        perror("mq_send");
        exit(1);
    }

    strcpy(buffer, "Message with priority 3");
    if (mq_send(mq, buffer, strlen(buffer) + 1, 3) == -1) {
        perror("mq_send");
        exit(1);
    }

    strcpy(buffer, "Message with priority 2");
    if (mq_send(mq, buffer, strlen(buffer) + 1, 2) == -1) {
        perror("mq_send");
        exit(1);
    }

    strcpy(buffer, "Message with priority 0");
    if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) {
        perror("mq_send");
        exit(1);
    }

    // Close the message queue
    mq_close(mq);
    //mq_unlink(QUEUE_NAME);
    return 0;
}
