# KPITAPEXLAB_Project

# Vehicle Monitoring System using Linux IPC

A multi-process Vehicle Monitoring System developed in C using Linux System Programming concepts such as:

- Process Creation
- POSIX Threads
- FIFO (Named Pipes)
- Message Queues
- Shared Memory
- Signal Handling
- Synchronization using Mutex

This project simulates a real-time vehicle monitoring architecture where multiple sensor modules communicate with a fusion engine and logger process.

---

# Project Overview

Modern autonomous and smart vehicles rely on multiple sensors such as LiDAR, RADAR, and Cameras to monitor surroundings and assess driving risks.

This project simulates such a system on Linux using Inter Process Communication (IPC) and concurrent programming concepts.

The system demonstrates:
- Multi-process execution
- Parallel sensor simulation
- Shared data communication
- Risk analysis using fusion logic
- Graceful system shutdown

---

# Features

- Multi-process architecture using `fork()` and `execl()`
- Real-time sensor simulation
- Sensor fusion mechanism
- Shared memory communication
- Message queue communication
- FIFO-based communication
- POSIX thread implementation
- Signal handling using `SIGINT`
- Continuous vehicle logging system
- Linux system programming concepts

---

# Technologies Used

| Technology | Purpose |
|---|---|
| C Programming | Core implementation |
| Linux System Calls | Process and IPC handling |
| POSIX Threads | Concurrent fusion processing |
| Shared Memory | Fast data sharing |
| Message Queue | Camera object transfer |
| FIFO | RADAR speed transfer |
| Signals | Graceful shutdown |

---

# Project Structure

```text
Vehicle_Project/
│── Makefile
│
├── Src/
│   ├── main.c
│   ├── lidar.c
│   ├── radar.c
│   ├── camera.c
│   ├── fusion.c
│   └── logger.c
│
├── include/
│   └── common.h
│
└── vehicle_log.txt
````

---

# System Architecture

```text
                         +----------------------+
                         |      main.c          |
                         |  Parent Controller   |
                         +----------+-----------+
                                    |
          -------------------------------------------------------
          |               |               |             |        |
          v               v               v             v        v

   +-------------+  +-------------+  +-------------+  +-------------+
   |  LiDAR      |  |   RADAR     |  |   Camera    |  |   Logger    |
   |  Process    |  |   Process   |  |   Process   |  |   Process   |
   +------+------+  +------+------+  +------+------+  +------+------+
          |                |                |                 ^
          |                |                |                 |
          |                |                |                 |
          |             FIFO PIPE      Message Queue          |
          |                |                |                 |
          -----------------+----------------+-----------------
                           |
                           v
                   +---------------+
                   | Fusion Engine |
                   |   fusion.c    |
                   +-------+-------+
                           |
                     Shared Memory
                           |
                           v
                   +---------------+
                   | vehicle_log   |
                   +---------------+
```

---

# Process Design

## 1. main.c

Acts as the parent controller process.

Responsibilities:

* Creates FIFO
* Creates unnamed pipe
* Spawns child processes
* Handles graceful shutdown using signals

Processes created:

* lidar
* radar
* camera
* fusion
* logger

### Important Code

```c
if (fork() == 0) execl("./lidar", "lidar", NULL);
if (fork() == 0) execl("./radar", "radar", NULL);
if (fork() == 0) execl("./camera", "camera", NULL);
if (fork() == 0) execl("./fusion", "fusion", NULL);
if (fork() == 0) execl("./logger", "logger", NULL);
```

---

## 2. lidar.c

Simulates LiDAR sensor data.

Responsibilities:

* Generates random distance values
* Sends data using pipe communication

Example:

```c
float distance = rand() % 20;
```

---

## 3. radar.c

Simulates RADAR sensor.

Responsibilities:

* Generates random speed values
* Sends speed data through FIFO

Example:

```c
float speed = rand() % 100;
```

---

## 4. camera.c

Simulates camera object detection.

Responsibilities:

* Detects object types
* Sends object names using Message Queue

Detected objects:

* Car
* Pedestrian
* Bike

---

## 5. fusion.c

Core processing module.

Responsibilities:

* Reads sensor information
* Calculates risk level
* Updates shared memory
* Uses POSIX thread for concurrent processing

### Risk Logic

```c
if (data.distance < 5 && data.speed > 30)
    data.risk = 2;
else if (data.distance < 10)
    data.risk = 1;
else
    data.risk = 0;
```

Risk Levels:

| Risk Value | Meaning   |
| ---------- | --------- |
| 0          | Safe      |
| 1          | Warning   |
| 2          | High Risk |

---

## 6. logger.c

Responsible for logging system data.

Responsibilities:

* Reads data from shared memory
* Writes vehicle data to log file

Log File:

```text
vehicle_log.txt
```

Sample log:

```text
Dist: 5.00 Speed: 40.00 Risk: 2
```

---

# Thread Design

The fusion module uses POSIX threads.

## Fusion Thread

```c
pthread_create(&tid, NULL, fusion_thread, NULL);
```

Purpose:

* Continuously analyze sensor data
* Compute risk level
* Enable concurrent execution

Synchronization:

```c
pthread_mutex_lock(&mutex);
pthread_mutex_unlock(&mutex);
```

---

# IPC Mechanisms Used

## 1. FIFO (Named Pipe)

Used in:

* RADAR → Fusion

Resource:

```c
#define FIFO_NAME "/tmp/radar_fifo"
```

Purpose:

* Transfer speed data

Advantages:

* Simple communication
* Suitable for continuous stream data

---

## 2. Message Queue

Used in:

* Camera → Fusion

Resource:

```c
#define MQ_NAME "/camera_mq"
```

Purpose:

* Send object detection messages

Advantages:

* Structured communication
* Asynchronous messaging

---

## 3. Shared Memory

Used in:

* Fusion ↔ Logger

Resource:

```c
#define SHM_NAME "/fusion_shm"
```

Purpose:

* Fast shared data access

Advantages:

* High-speed communication
* Efficient for real-time systems

---

## 4. Pipe

Used in:

* LiDAR internal communication

Purpose:

* Transfer distance values

Advantages:

* Lightweight IPC
* Fast local communication

---

# Shared Data Structure

```c
typedef struct {
    float distance;
    float speed;
    char object[20];
    int risk;
} FusionData;
```

| Field    | Description            |
| -------- | ---------------------- |
| distance | Distance from object   |
| speed    | Speed of nearby object |
| object   | Object detected        |
| risk     | Collision risk         |

---

# Signal Handling

The system handles graceful shutdown using `SIGINT`.

## Signal Handler

```c
void handler(int sig) {
    printf("Shutting down system...\n");

    unlink(FIFO_NAME);
    mq_unlink(MQ_NAME);
    shm_unlink(SHM_NAME);

    exit(0);
}
```

Triggered using:

```bash
CTRL + C
```

Purpose:

* Remove IPC resources
* Prevent memory leakage
* Cleanly terminate all processes

---

# Data Flow Diagram (DFD)

```text
+-----------+       +-----------+
|  LiDAR    |-----> |           |
+-----------+       |           |
                    |           |
+-----------+       |  Fusion   |-------> Shared Memory -------> Logger
|  RADAR    |-----> |  Engine   |
+-----------+       |           |
                    |           |
+-----------+       |           |
|  Camera   |-----> |           |
+-----------+       +-----------+
```

---

# Build Instructions

## Compile Project

```bash
make
```

---

# Run Instructions

## Execute Project

```bash
./main
```

---

# Clean Build Files

```bash
make clean
```

---

# Sample Output

```text
Dist: 4.00 Speed: 45.00 Risk: 2
Dist: 8.00 Speed: 20.00 Risk: 1
Dist: 15.00 Speed: 10.00 Risk: 0
```

---

# Working Flow

## Step 1

LiDAR generates distance data.

## Step 2

RADAR generates speed data.

## Step 3

Camera detects object type.

## Step 4

Fusion engine combines sensor data.

## Step 5

Risk level is calculated.

## Step 6

Logger stores fused data into log file.

---

# Future Enhancements

* Real sensor integration
* GUI dashboard
* Socket programming support
* CAN Bus communication
* AI-based collision prediction
* Multi-threaded logging
* Database integration
* Real-time visualization

---

# Learning Outcomes

This project demonstrates:

* Linux IPC mechanisms
* Multi-process programming
* POSIX threads
* Shared memory management
* Signal handling
* Concurrent programming
* Real-time system simulation

---

# Conclusion

The Vehicle Monitoring System is a practical implementation of Linux System Programming concepts applied to an embedded automotive scenario.

The project successfully demonstrates:

* Sensor simulation
* Concurrent processing
* IPC communication
* Shared resource management
* Real-time monitoring architecture

This project serves as an excellent mini-project for:

* Embedded Systems
* Linux Programming
* System Programming
* Automotive Software Fundamentals

---

# References

* Linux Man Pages
* POSIX IPC Documentation
* Linux System Programming Concepts
* Operating System IPC Mechanisms

---

```
```
