#include "../include/common.h"

int main() {
    int fd[2];
    pipe(fd);

    srand(time(NULL));

    while (1) {
        float distance = rand() % 20;
        write(fd[1], &distance, sizeof(distance));
        sleep(1);
    }
}