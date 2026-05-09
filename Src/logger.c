#include "../include/common.h"

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    FusionData *ptr = mmap(0, sizeof(FusionData),
                           PROT_READ, MAP_SHARED, shm_fd, 0);

    int fd = open("vehicle_log.txt", O_CREAT | O_WRONLY, 0666);

    while (1) {
        char buffer[100];
        sprintf(buffer, "Dist: %.2f Speed: %.2f Risk: %d\n",
                ptr->distance, ptr->speed, ptr->risk);

        write(fd, buffer, strlen(buffer));

        lseek(fd, 0, SEEK_END);
        sleep(1);
    }
}