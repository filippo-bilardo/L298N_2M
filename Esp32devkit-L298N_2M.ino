/** 
 * L298N_2M driver motor library test
 * by Filippo Bilardo
 * v1.0 - 02/01/21
 */

#include "L298N_2M.h"

// motor 1 settings
#define IN3 17
#define IN4 16
#define ENB 4// this pin must be PWM enabled pin if Arduino board is used
// motor 2 settings
#define ENA 19 // this pin must be PWM enabled pin if Arduino board is used
#define IN1 5  //18 motore collegato al contrario
#define IN2 18 //5

// fore two motors with debug information
//L298N_2M motors(IN3, IN4, ENB, PWM_CHB, IN1, IN2, ENA, PWM_CHA, true);
L298N_2M motors(IN1, IN2, ENA, PWM_CHA, IN3, IN4, ENB, PWM_CHB, true);

void setup() {
  Serial.begin(115200); 
  
  motors.begin();
  motors.demo();
}

void loop() {
}
