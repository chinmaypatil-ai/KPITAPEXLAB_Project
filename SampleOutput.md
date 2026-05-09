````markdown id="dr8v0n"
# Sample Output

## Terminal Output

```text
Vehicle Monitoring System Started...

[LiDAR] Distance Generated : 12.00 m
[RADAR] Speed Generated    : 45.00 km/h
[Camera] Object Detected   : Car

[Fusion] Processing Sensor Data...
[Fusion] Risk Level : 0 (SAFE)

--------------------------------------------------

[LiDAR] Distance Generated : 7.00 m
[RADAR] Speed Generated    : 25.00 km/h
[Camera] Object Detected   : Bike

[Fusion] Processing Sensor Data...
[Fusion] Risk Level : 1 (WARNING)

--------------------------------------------------

[LiDAR] Distance Generated : 3.00 m
[RADAR] Speed Generated    : 60.00 km/h
[Camera] Object Detected   : Pedestrian

[Fusion] Processing Sensor Data...
[Fusion] Risk Level : 2 (HIGH RISK)

--------------------------------------------------

Press CTRL + C to terminate system...
````

---

# Logger File Output

Generated file:

```text
vehicle_log.txt
```

Sample log entries:

```text
Dist: 12.00 Speed: 45.00 Risk: 0
Dist: 7.00 Speed: 25.00 Risk: 1
Dist: 3.00 Speed: 60.00 Risk: 2
Dist: 15.00 Speed: 10.00 Risk: 0
Dist: 5.00 Speed: 40.00 Risk: 2
```

---

# Shutdown Output

When user presses:

```bash
CTRL + C
```

System output:

```text
Shutting down system...
Removing FIFO...
Removing Message Queue...
Removing Shared Memory...
System terminated successfully.
```

---

# Risk Level Meaning

| Risk Level | Meaning   |
| ---------- | --------- |
| 0          | SAFE      |
| 1          | WARNING   |
| 2          | HIGH RISK |

---

```
```
