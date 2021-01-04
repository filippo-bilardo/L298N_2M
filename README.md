L298N-lib
=========

An Arduino and ESP32 boards library for using the L298N motor driver.

Visit my blogs for other projects (http://fb-labs.blogspot.com/, http://fb-projects.blogspot.com/)

Methods
=======

Constructor
-----------
Creates an object representing one motor output on the L298N motor controller, which is controlled using three pins
for Arduino boards and for pins for ESP32 boards.

Here an axample of utilization:
```c
// motor 1 settings
#define ENA 19 // this pin must be PWM enabled pin if Arduino board is used
#define IN1 5  //18 motore collegato al contrario
#define IN2 18 //5
// motor 2 settings
#define IN3 17
#define IN4 16
#define ENB 4// this pin must be PWM enabled pin if Arduino board is used

L298N motor1(IN1, IN2, ENA, PWM_CHA);
L298N motor2(IN3, IN4, ENB, PWM_CHB);
```
You can now use these functions on this object:

`void setStatus(direction)`
------------------------------
This will set the status of the motor attached to the driver. Please note that for the motor to run, you must also set the speed.

Also note that the directions are completely arbitrary, because it depends on which way you have connected the motor and which way round you have connected the Input 1 and Input 2.

```c
motor.setStatus(STOP);  //Free Running Motor
```
```c
motor.setStatus(BRAKE); //Fast Motor Stop
motor.setStatus(FORWARD);
motor.setStatus(REVERSE);
```

`void setSpeed(int percentage)`
-------------------------------
This will set the speed of the motor attached to the driver. Please note that for the motor to run, you must also set the direction.

If the value is out of bounds, it uses the closest value. For example `setSpeed(150)` would set the speed to be 100%
```c
motor.setSpeed(50); //Set speed to 50%
```

```c
motor.setSpeed(100); //FULL SPEED AHEAD!
```

`void forward()`
-------------
This will move the motor forward.
```c
motor.forward();
```

`void reverse()`
-------------
This will move the motor reverse.
```c
motor.forward();
```

`void stop()`
-------------
This will stop the motor, letting it spin down to rest
```c
motor.stop();
```
This function will not save direction data.

`void brake()`
--------------
This will put the motor into the break state, stopping it (if moving) and making it harder to turn (in theory...)
```c
motor.brake();
```
This function will not save direction data.

`void test()`
--------------
This function causes the motor to perform some movements.
```c
motor.test();
```

`int getSpeed()`
----------------
Returns the current motor speed as a percentage
```c
int speed = motor.getSpeed(); //Get motor speed and save it into the speed variable
motor.stop(); //Stop the motor
delay(1000); //Wait 1 second
motor.setSpeed(speed); //Set the speed back to the previous speed
motor.setStatus(FORWARD): //Set status to FORWARD because stop() overwrites it
```

`direction getDirection()`
--------------------------
Returns the current motor direction.
```c
status st = motor.getStatus(); //Get motor status and save it into the st variable
motor.stop(); //Stop the motor
delay(1000); //Wait 1 second
motor.setStatus(st); //Set the status back to the previous status
motor.setSpeed(100); //Set the speed to 100% because stop() overwrites it
```

License
=======

  this is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

