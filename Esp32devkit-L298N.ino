/** 
 * ESP32 L298N driver motor class test
 * by Filippo Bilardo - http://fb-projects.blogspot.com/
 * v1.0 - 02/01/2021
 */

#include "L298N.h"

// motor 1 settings
#define IN3 17
#define IN4 16
#define ENB 4// this pin must be PWM enabled pin if Arduino board is used
// motor 2 settings
#define ENA 19 // this pin must be PWM enabled pin if Arduino board is used
#define IN1 5  //18 motore collegato al contrario
#define IN2 18 //5

L298N m1(IN3, IN4, ENB, PWM_CHB, true);
L298N m2(IN1, IN2, ENA, PWM_CHA, true);

void setup() {
  Serial.begin(115200);
  
  m1.begin();
  m2.begin();
  //m1.test();
  //m2.test();
  delay(2000);
}

void loop() {
  
  Serial.println("Avanti dritto a velocità variabile");
  m1.forward(); m2.forward(); 
  m1.setSpeed(100); m2.setSpeed(100); delay(1000);
  for(int i=0; i<=100; i++) {m1.setSpeed(i); m2.setSpeed(i); delay(50);}
  Serial.println("Indietro dritto a velocità variabile");
  m1.reverse(); m2.reverse(); 
  for(int i=0; i<=100; i++) {m1.setSpeed(i); m2.setSpeed(i); delay(50);}
  
  Serial.println("Brake");
  m1.brake(); m2.brake(); delay(1000);

  Serial.println("Curva Dx - 100,70");
  m1.forward(); m2.forward(); 
  m1.setSpeed(100); m2.setSpeed(70); delay(1000);
  Serial.println("Ruota a destra - 100,0");
  m2.brake(); delay(2000);
  
  Serial.println("Brake");
  m1.brake(); m2.brake(); delay(1000);

  Serial.println("Curva Sx - 40,100");
  m1.forward(); m2.forward(); 
  m1.setSpeed(40); m2.setSpeed(100); delay(1000);
  Serial.println("Ruota a sinistra - 0,100");
  m1.brake(); delay(2000);
  
  Serial.println("Brake");
  m1.brake(); m2.brake(); delay(1000);

  Serial.println("Ruota Dx e Sx a velocità variabile");
  m1.forward(); m2.reverse();
  for(int i=0; i<=100; i++) {m1.setSpeed(i); m2.setSpeed(i); delay(100);}
  m1.reverse(); m2.forward();
  for(int i=0; i<=100; i++) {m1.setSpeed(i); m2.setSpeed(i); delay(100);}
  m1.brake(); m2.brake(); delay(1000);
  
  Serial.println("Spirali Dx e Sx");
  m1.forward(); m2.forward(); 
  m1.setSpeed(100); 
  for(int i=0; i<=100; i++) {m2.setSpeed(i); delay(50);}
  m2.setSpeed(100); 
  for(int i=0; i<=100; i++) {m1.setSpeed(i); delay(50);}  

  //Stop 5sec
  m1.brake(); m2.brake(); delay(5000);
}
