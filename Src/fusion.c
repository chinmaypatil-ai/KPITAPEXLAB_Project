#include "../include/common.h"

FusionData data;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *fusion_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        if (data.distance < 5 && data.speed > 30)
            data.risk = 2;
        else if (data.distance < 10)
            data.risk = 1;
        else
            data.risk = 0;

        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

int main() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(FusionData));
    FusionData *ptr = mmap(0, sizeof(FusionData),
                           PROT_WRITE, MAP_SHARED, shm_fd, 0);

    pthread_t tid;
    pthread_create(&tid, NULL, fusion_thread, NULL);

    srand(time(NULL));

    while (1) {
        pthread_mutex_lock(&mutex);

        data.distance = rand() % 20;
        data.speed = rand() % 100;
        strcpy(data.object, "Car");

        *ptr = data;

        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}