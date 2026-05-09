#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

#define FIFO_NAME "/tmp/radar_fifo"
#define MQ_NAME "/camera_mq"
#define SHM_NAME "/fusion_shm"

typedef struct {
    float distance;
    float speed;
    char object[20];
    int risk;
} FusionData;

#endif