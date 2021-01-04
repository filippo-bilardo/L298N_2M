/** ****************************************************************************************
 * @file L298N.h
 * @brief Library for operating with a L298N motor driver work with ESP32 boards
 * @author Filippo Bilardo (http://fb-labs.blogspot.com/, http://fb-projects.blogspot.com/)
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
 * 02.01.21   1.0.0    Versione iniziale. Ispirazione grazie al codice 
 *                     Robojax_L298N_DC_motor.h, Written by Ahmad Shamshiri (Robojax.com)
 *                     RX14, June 7, 2014 - https://github.com/RX14/L298N-lib
 *                     https://github.com/AndreaLombardo/L298N
 * </pre>
 */
#ifndef L298N_H
#define L298N_H

#include "Arduino.h"

#define debug(fmt, ...) Serial.printf("%s: " fmt "\r\n", __func__, ##__VA_ARGS__)
#define trace(fmt, ...) Serial.printf("%s: " fmt "\r\n", __func__, ##__VA_ARGS__)

#define PWM_CHA   0     //Canale PWM 0 ESP32
#define PWM_CHB   1     //Canale PWM 1 ESP32
#define PWM_RES   12    //Resolution bits
#define PWM_FREQ  5000  //Freq
#define MTR_VMIN  65    //Valore % minimo per mettere in movimento i motori


class L298N
{
  public:

    typedef enum {STOP=3, BRAKE, FORWARD, REVERSE} Status;
    
    L298N(int enPin, int inaPin, int inbPin);
    L298N(int enPin, int inaPin, int inbPin, int pwmCh, boolean debug);

    void begin();
    void stop();
    void brake();
    void forward();
    void reverse();

    void setSpeed(int percentage);
    int  getSpeed();
    void   setStatus(int st);
    L298N::Status getStatus();

    void test();

  private:

    void init(int inaPin, int inbPin, int enPin, int pwmCh, boolean debug);
    
    int _enPin, _inaPin, _inbPin; //Configured pins
    int _pwmCh;
    int _pwmResolution = PWM_RES;
    int _pwmFrequency = PWM_FREQ;
    uint32_t _pwmDutyTick = pow(2, _pwmResolution)/255;
    int _speed;     //Stored speed
    L298N::Status _status; //Stored status
    boolean _debug;
};

#endif
