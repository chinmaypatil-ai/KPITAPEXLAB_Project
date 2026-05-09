#include "../include/common.h"

int main() {
    int fd = open(FIFO_NAME, O_WRONLY);
    srand(time(NULL));

    while (1) {
        float speed = rand() % 100;
        write(fd, &speed, sizeof(speed));
        sleep(1);
    }
}