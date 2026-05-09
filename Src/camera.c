#include "../include/common.h"

int main() {
    struct mq_attr attr = {0, 10, 50, 0};
    mqd_t mq = mq_open(MQ_NAME, O_CREAT | O_WRONLY, 0666, &attr);

    char *objects[] = {"Car", "Pedestrian", "Bike"};
    srand(time(NULL));

    while (1) {
        char *obj = objects[rand() % 3];
        mq_send(mq, obj, strlen(obj) + 1, 0);
        sleep(1);
    }
}