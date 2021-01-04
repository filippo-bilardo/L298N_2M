/** ****************************************************************************************
 * @file L298N_2M.h
 * @brief L298N Library for controlling two motor. Work with ESP32 boards
 * @author Filippo Bilardo
 * 
 * TODO: Migliorare il logging, Funzione Steer
 *
 *  this is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *    
 * \par History:
 * <pre>
 * Date       Version  Descr
 * 22.05.20   1.0.0    Versione iniziale - Da RobotOfficial_v4.0.0 e DidaBot_v0.1
 * 02.01.21   1.0.1    Aggiunto il supporto per le schede ESP32. Grazie al codice 
 *                     Robojax_L298N_DC_motor.h, Written by Ahmad Shamshiri (Robojax.com)
 *                     RX14, June 7, 2014 - https://github.com/RX14/L298N-lib
 *                     https://github.com/AndreaLombardo/L298N
 *                     https://makecode.mindstorms.com/reference/motors
 * </pre>
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
#include "L298N.h"

class L298N_2M
{
public:

  /**
   * @brief constructor for dual motor
   * @param pins connected to the L298N driver
   * @param pwmChA, pwmChB: esp32 pwm channel
   * @param debug: debug enable
   */
  L298N_2M(int in1Pin,int in2Pin,int enAPin, int pwmChA, int in3Pin, int in4Pin,int enBPin, int pwmChB, boolean debug);   
  
  /**
   * Initializes the L298D motor driver
   */
  void begin();
  void stop(int motor);
  /**
   * @brief stop motor quickly with L298N
   */
  void brake(int motor);
  /**
   * @brief Set the rotation speed of the motor as a percentage of maximum speed.
   * @param motor: 1=motor1, 2=motor2, 3=all
   * @param speed: a number that is the percentage of full speed. A negative 
   * value runs the motor in the reverse direction. range -100 to 100
   * @param value: the number of movement units to rotate for. A value of 0 means 
   * run the motor continuously.
   * @param unit: the movement unit of rotation. This can be milliseconds, seconds, 
   * degrees, or rotations. If the number for value is 0, this parameter isn’t used.
   *
   * @version 1.0 - 2/1/21 - from https://makecode.mindstorms.com/reference/motors/motor/run
   */
  void run(int motor, int speed);
  void run(int motor, int speed, int value, int unit);
  /**
   * @brief Steer the robot in one direction using a turn ratio between two motors.
   *  
   * A robot driving with two motors can steer itself by changing the speed of 
   * one motor compared to the speed of the other. To make a slow turn to the left, you might 
   * make the right motor run slightly faster than the left one. To make a fast, or sharp, 
   * turn to the right, the left motor could run at least twice as fast as the right one.
   * The robot steers by using a percentage value of follow for one of the motors. 
   * This means that the motor in the turn direction will rotate slower than the other. 
   * It is the follower motor and the other motor is the drive motor. The drive motor 
   * runs at a percentage of full speed set in speed. The follower motor runs at a 
   * percentage of speed of the drive motor. So, it runs at a percentage of a percentage 
   * of full speed.
   * To make the turn happen you give a turn ratio which is a percentage value of steer 
   * to the left or right. If you want to steer to the left at 30% of the of the drive motor 
   * speed, use the value of -30 for turnRatio. Left turns use negative values and right 
   * turns use positive values. A really sharp turn to the right might use a turn ratio 
   * value of 80.
   * 
   * @param turnRatio: a number that is the percentage of speed of the drive motor. 
   * The follower motor runs at this speed. A negative number steers to the left 
   * and a positive number steers to the right. This is a number between -100 and 100.
   * @param speed: a number that is the percentage of full speed. A negative 
   * value runs the motor in the reverse direction. range -100 to 100
   * @param value: the number of movement units to rotate for. A value of 0 means 
   * run the motor continuously.
   * @param unit: the movement unit of rotation. This can be milliseconds, seconds, 
   * degrees, or rotations. If the number for value is 0, this parameter isn’t used.
   *
   * @version 1.0 - 2/1/21 - from https://makecode.mindstorms.com/reference/motors/synced/steer
   */
  void steer(int turnRatio, int speed);
  void steer(int turnRatio, int speed, int value, int unit);
  /**
   * @brief Rotate two motors in synchronization.
   * 
   * Tanking the robot will drive two motors in synchronization. This means that 
   * both motors will start at the same time. Also, each motor uses the same amount 
   * of rotation when running at the same speed. You can use different speed values 
   * for each motor to perform turns or spins.
   * 
   * @param speedLeft: a number that is the percentage of full speed for the motor 
   *   attached to the left of the robot. A negative value runs the motor in the 
   *   reverse direction.
   * @param speedRight: same as speedLeft
   * @param value: the number of movement units to rotate for. A value of 0 means 
   * run the motor continuously.
   * @param unit: the movement unit of rotation. This can be milliseconds, seconds, 
   * degrees, or rotations. If the number for value is 0, this parameter isn’t used.
   *
   * @version 1.0 - 2/1/21 - from https://makecode.mindstorms.com/reference/motors/synced/tank
   */
  void tank(int speedLeft, int speedRight);
  void tank(int speedLeft, int speedRight, int value, int unit);
  
  /**
   * motor test
   */
  void test(int nrtest);
  /**
   * runs series of motor control demonstration
   */
  void demo();
  
private:

  void init(int in1Pin, int in2Pin, int enAPin, int pwmChA, int in3Pin, int in4Pin, int enBPin, int pwmChB, boolean debug);

  boolean _debug;
   L298N _motor1;
   L298N _motor2;
};
#endif
