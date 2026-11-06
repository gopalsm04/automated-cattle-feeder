# Automated Cattle Feeder

An Arduino-based prototype that follows a line, stops when it detects an animal or feeding point ahead, and releases feed using a servo-controlled mechanism, reducing manual feeding effort.

**Department of Electrical and Electronics Engineering, Shridevi Institute of Engineering and Technology, Tumakuru (VTU)**

## Overview
The robot follows a track using two IR sensors. An ultrasonic sensor watches for obstacles ahead. When something is detected within 20 cm, the robot stops and a servo-controlled mechanism opens to dispense feed. The servo opens wider at each stop, so each feeding point receives a different amount of feed. After the fourth stop, the system resets and rests before starting again.

## Features
- Line following using two IR sensors
- Obstacle detection within 20 cm using an ultrasonic sensor
- Servo-controlled feed release with a different opening angle at each stop
- Automatic cycle reset after four stops

## Components
| Component | Purpose |
|---|---|
| Arduino board [fill in: Uno / Nano] | Main controller |
| IR sensors (2) | Detect the track (line following) |
| Ultrasonic sensor (HC-SR04) | Detect obstacles within 20 cm |
| Servo motor | Opens and closes the feed-dispensing mechanism |
| DC motors with motor driver [fill in: e.g. L298N] | Move the robot |
| Chassis, wheels and battery [fill in] | Mechanical base and power |

## How it works
1. Both IR sensors read the track. Both LOW moves forward, left HIGH turns right, right HIGH turns left, and both HIGH stops.
2. The ultrasonic sensor measures the distance ahead on every loop.
3. If an obstacle is detected within 20 cm, the robot stops and counts the stop.
4. The servo turns to a set angle and the robot waits to release feed:
   - Stop 1: servo at 30°, wait 15 seconds
   - Stop 2: servo at 60°, wait 15 seconds
   - Stop 3: servo at 90°, wait 15 seconds
   - Stop 4: servo returns to 0°, wait 45 seconds, then the count resets
5. The robot then continues following the line.

## Tools and technologies
- Arduino IDE, Embedded C/C++
- IR sensor and ultrasonic sensor interfacing
- Servo motor and DC motor control

## Team
- Gopal S M
- Umesh
- Ajit

## Repository contents
- `code/` Arduino source code
- `images/` photos of the prototype
- `demo/` demo video (if available)

## Future improvements
- Add an RTC module for time-based feeding schedules
- Use PWM motor speed control for smoother movement
- Replace blocking delays with non-blocking timers
- Add a feed-level sensor and an alert system
