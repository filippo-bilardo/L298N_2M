#include "Arduino.h"
#include "L298N_2M.h"

L298N_2M::L298N_2M(int in1Pin, int in2Pin, int enAPin, int pwmChA, 
                   int in3Pin, int in4Pin, int enBPin, int pwmChB, 
                   boolean debug) : _motor1(in1Pin, in2Pin, enAPin, pwmChA, debug),
                                    _motor2(in3Pin, in4Pin, enBPin, pwmChB, debug)
{
  _debug=debug;  
  if(this->_debug) debug("FB L298N_2M Motor Library");  
}
void L298N_2M::begin() {
  _motor1.begin();
  _motor2.begin();
}

void L298N_2M::stop(int motor) {
  
  if(motor==3) {
    _motor1.stop();
    _motor2.stop();
  } else if(motor==2) {
    _motor2.stop();
  } else {
    _motor1.stop();
  }
} //stop()
void L298N_2M::brake(int motor) {
  
  if(motor==3) {
    _motor1.brake();
    _motor2.brake();
  } else if(motor==2) {
    _motor2.brake();
  } else {
    _motor1.brake();
  }
} //brake()
void L298N_2M::run(int motor, int speed) {

  if(this->_debug) {trace("run(motor=%d, speed=%d)", motor, speed);}

  // limits range between -100 and 100
  speed = constrain(speed, -100, 100); 

  L298N::Status dir;
  if(speed<0) {dir=L298N::REVERSE; speed*=-1;} else {dir=L298N::FORWARD;}
  if(this->_debug) {trace("run(dir=%d, speed=%d)", dir, speed);}

  if(motor==1) {
    _motor1.setStatus(dir);
    _motor1.setSpeed(speed);
  } else if(motor==2) {
    _motor2.setStatus(dir);
    _motor2.setSpeed(speed);
  } else if(motor==3) {
    _motor1.setStatus(dir);
    _motor1.setSpeed(speed);
    _motor2.setStatus(dir);
    _motor2.setSpeed(speed);
  }
}
void L298N_2M::run(int motor, int speed, int value, int unit) {
  run(motor, speed);
  //TODO: if(value==1) -> unit is ms
  delay(unit);
  brake(motor); 
}
void L298N_2M::steer(int turnRatio, int speed) {
  
  //TODO: Algoritmo da migliorare
  if(this->_debug) {trace("steer(turnRatio=%d, speed=%d)", turnRatio, speed);}
  
  // limits range between -100 and 100
  turnRatio = constrain(turnRatio, -100, 100); 
  speed = constrain(speed, -100, 100); 
  int speedLeft,speedRight;
  
  if(turnRatio<0) { //turnRatio <0 -> turn to left
    speedLeft=100+turnRatio;
    speedLeft=map(speedLeft, 0, 100, 0, speed);
    speedRight=turnRatio*-1;
    speedLeft=map(speedRight, 0, 100, 0, speed);
  } else {  //turnRatio >0 -> turn to right
    speedLeft=turnRatio;
    speedLeft=map(speedLeft, 0, 100, 0, speed);
    speedRight=100-turnRatio;
    speedLeft=map(speedRight, 0, 100, 0, speed);  
  }
  
  run(1, speedLeft);
  run(2, speedRight);
}
void L298N_2M::steer(int turnRatio, int speed, int value, int unit) {
  steer(turnRatio, speed);
  //TODO: if(value==1) -> unit is ms
  delay(unit);
  brake(3); 
}
void L298N_2M::tank(int speedLeft, int speedRight) {

  if(this->_debug) {trace("tank(speedLeft=%d, speedRight=%d)", speedLeft, speedRight);}

  // limits range between -100 and 100
  speedLeft = constrain(speedLeft, -100, 100); 
  speedRight = constrain(speedRight, -100, 100); 

  run(1, speedLeft);
  run(2, speedRight);
}
void L298N_2M::tank(int speedLeft, int speedRight, int value, int unit) {
  tank(speedLeft, speedRight);
  //TODO: if(value==1) -> unit is ms
  delay(unit);
  brake(3); 
}
  
void L298N_2M::test(int nrtest) {

  switch(nrtest) 
  {
    case '1': {
      this->run(3,80,1,2400);
      this->run(3,-70,1,2800);
      this->run(3,100,1,2000);
      this->run(3,-90,1,2200);
      this->run(3,100); delay(2000); this->stop(3); delay(500);
      this->run(3,100); delay(2000); this->brake(3); delay(500);
      break;}
    case '2': {
      //Avanti e indietro a velocità variabile
      if(this->_debug) debug("**** Test Avanti e indietro a velocità variabile ****");
      for(int i=50; i<=100; i++) {this->run(3,i,1,200);}
      for(int i=50; i<=100; i++) {this->run(3,-i,1,200);}
      this->stop(3); delay(500);
      //otto
      if(this->_debug) debug("**** Test2 otto ****");
      //Cerchi
      if(this->_debug) debug("**** Test2 cerchi ****");
      this->brake(3); delay(500);
      break;}
    case '3': {
      if(this->_debug) debug("**** Test Avanti e indietro a velocità variabile ****");
      this->run(3,100,1,500);
      for(int i=100; i>=0; i--) {this->run(3,i,1,50);}
      for(int i=0; i<=100; i++) {this->run(3,-i,1,50);}
      this->run(3,-100,1,500);
      this->brake(3); delay(2000);

      if(this->_debug) debug("**** Test tank dritto ****");
      this->tank(100,100,1,500);
      for(int i=-100; i<=100; i++) {this->tank(i,i,1,50);}
      this->tank(-100,-100,1,500);
      this->brake(3); delay(2000);
      
      if(this->_debug) debug("**** Test tank rotazione ****");
      this->tank(-100,100,1,500);
      for(int i=-100; i<=100; i++) {this->tank(i,-i,1,50);}
      this->tank(100,-100,1,500);
      this->brake(3); delay(2000);
      break;}
    case '4': {
      if(this->_debug) debug("**** Test steer ****");
      this->steer(-100,100,1,1000);
      for(int i=-100; i<=100; i++) {this->steer(i,100,1,100);}
      this->steer(100,-100,1,1000);
      this->brake(3); delay(2000);
      break;} 
  }
}
void L298N_2M::demo() {
  delay(1000);
  this->test('3');
}
