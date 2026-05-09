CC=gcc
CFLAGS=-Wall -lpthread -lrt

all:
	$(CC) src/lidar.c -o lidar $(CFLAGS)
	$(CC) src/radar.c -o radar $(CFLAGS)
	$(CC) src/camera.c -o camera $(CFLAGS)
	$(CC) src/fusion.c -o fusion $(CFLAGS)
	$(CC) src/logger.c -o logger $(CFLAGS)
	$(CC) src/main.c -o main $(CFLAGS)

run:
	./main

clean:
	rm -f lidar radar camera fusion logger main vehicle_log.txt