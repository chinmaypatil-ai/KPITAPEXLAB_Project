#include "../include/common.h"

void handler(int sig) {
    printf("Shutting down system...\n");
    unlink(FIFO_NAME);
    mq_unlink(MQ_NAME);
    shm_unlink(SHM_NAME);
    exit(0);
}

int main() {
    signal(SIGINT, handler);

    mkfifo(FIFO_NAME, 0666);

    int pipefd[2];
    pipe(pipefd);

    if (fork() == 0) execl("./lidar", "lidar", NULL);
    if (fork() == 0) execl("./radar", "radar", NULL);
    if (fork() == 0) execl("./camera", "camera", NULL);
    if (fork() == 0) execl("./fusion", "fusion", NULL);
    if (fork() == 0) execl("./logger", "logger", NULL);

    while (wait(NULL) > 0);

    return 0;
}