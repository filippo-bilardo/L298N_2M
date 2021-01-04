#include "L298N.h"

L298N::L298N(int inaPin, int inbPin, int enPin) {
  this->init(inaPin, inbPin, enPin, 0, true);  
}
L298N::L298N(int inaPin, int inbPin, int enPin, int pwmCh, boolean debug) {
  this->init(inaPin, inbPin, enPin, pwmCh, debug);  
}

void L298N::init(int inaPin, int inbPin, int enPin, int pwmCh, boolean debug) {

  if(this->_debug) debug("FB L298N Motor Library");  
  
  #if defined(ARDUINO_ARCH_ESP32)   
  _pwmCh = pwmCh;
  #endif

  _inaPin = inaPin;
  _inbPin = inbPin;
  _enPin  = enPin;
  _debug = debug; 
}
void L298N::begin() {
  
  if(this->_debug) {debug("ledcSetup(_pwmCh=%d, _pwmFrequency=%d, _pwmResolution=%d)",_pwmCh, _pwmFrequency, _pwmResolution);}
  if(this->_debug) {debug("ledcAttachPin(_enPin=%d, _pwmCh=%d)",_enPin, _pwmCh);}

  #if defined(ARDUINO_ARCH_ESP32)   
  ledcSetup(_pwmCh, this->_pwmFrequency, this->_pwmResolution);
  ledcAttachPin(_enPin, _pwmCh);
  #else
  pinMode(this->_enPin, OUTPUT);
  #endif
  
  pinMode(this->_inaPin, OUTPUT);
  pinMode(this->_inbPin, OUTPUT);
  
  _speed = 0;
  _status = STOP;

  if(this->_debug) {debug("pinMode _enPin=%d, _inaPin=%d, _inbPin=%d ", _enPin, _inaPin, _inbPin);}
}
void L298N::stop() {
  if(this->_debug) {trace("stop()");}
  digitalWrite(_enPin , LOW);
  digitalWrite(_inaPin, LOW);
  digitalWrite(_inbPin, LOW);
  _status = STOP;
}
void L298N::brake() {
  if(this->_debug) {trace("brake()");}
  digitalWrite(_enPin , HIGH);
  digitalWrite(_inaPin, HIGH);
  digitalWrite(_inbPin, HIGH);
  _status = BRAKE;
}
void L298N::forward() {
  if(this->_debug) {trace("forward()");}
  digitalWrite(_enPin, HIGH); 
  digitalWrite(_inaPin, HIGH);
  digitalWrite(_inbPin, LOW);
  _status = FORWARD;
}
void L298N::reverse() {
  if(this->_debug) {trace("reverse()");}
  digitalWrite(_enPin, HIGH); 
  digitalWrite(_inaPin, LOW);
  digitalWrite(_inbPin, HIGH);
  _status = REVERSE;
}

void L298N::setSpeed(int value) {
  //Valori ammessi 0-100
  value = constrain(value, 0, 100);
  //Linearizzazione tra MTR_VMIN e 255 dei movimenti del motore
  //Per valori minori di MTR_VMIN il motore non riesce a muoversi
  value = map(value, 0, 100, MTR_VMIN*2.55, 255);
  _speed = value;

  #if defined(ARDUINO_ARCH_ESP32) 
  //TODO max value 4080 per 255
  uint32_t duty = _pwmDutyTick * value;
  ledcWrite(_pwmCh, duty); // write duty to LEDC
  #else
  analogWrite(_enPin, value);
  #endif 

  if(this->_debug) {trace("setSpeed value=%d, duty=%d, _pwmCh=%d ", value, duty, _pwmCh);}
}
int L298N::getSpeed() {
  return _speed;
}
void L298N::setStatus(int st) {
  switch(st) {
    case 0:
    case 1:
    case 2:
    case STOP: //Free Running Motor Stop
      this->stop();
      break;
    case BRAKE: 
    case 7: //Fast Motor Stop (Brake)
      this->brake();
      break;
    case FORWARD: //Forward
      this->forward();
      break;
    case REVERSE: //Reverse
      this->reverse();
      break;
  }
}
L298N::Status L298N::getStatus() {
  return _status;
}

void L298N::test() {
  //Avanti e indietro
  debug("Speed %d forward. delay(%d)", 100, 1000);
  this->setSpeed(100); this->forward(); delay(1000);
  debug("Speed %d reverse. delay(%d)", 30, 1500);
  this->setSpeed(30); this->reverse(); delay(1500);
  debug("stop. delay(%d)", 300);
  this->stop(); delay(300);

  //Avanti e indietro
  debug("Speed %d forward. delay(%d)", 50, 1500);
  this->setSpeed(50); this->forward(); delay(500);
  debug("Speed %d reverse. delay(%d)", 80, 1000);
  this->setSpeed(80); this->reverse(); delay(1000);
  debug("brake. delay(%d)", 300);
  this->brake(); delay(300);

  //Velocità da 0 a 100
  for(int i=0; i<=100; i++) {
    debug("Speed %d forward. delay(%d)", i, 100);
    this->setSpeed(i);
    this->forward();
    delay(100);
  }
  this->stop(); delay(1000);
}
