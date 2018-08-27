#ifndef _methods_motors.h
#define _methods_motors.h

//includes
//_________________________________________________________________________________________________________________
#include <SPI.h>
#include <Servo.h>
#include <math.h>


//constants
//_________________________________________________________________________________________________________________



#define PIN_SH_ROT_EN 
#define PIN_SH_ROT_IN1
#define PIN_SH_ROT_IN2	
#define PIN_SH_ROT_ADC

#define PIN_SH_EXT_EN 
#define PIN_SH_EXT_IN1 
#define PIN_SH_EXT_IN2 
#define PIN_SH_EXT_ADC

#define PIN_EL_EXT_EN
#define PIN_EL_EXT_IN1
#define PIN_EL_EXT_IN2
#define PIN_EL_EXT_ADC

#define PIN_WR_ROT_EN
#define PIN_WR_ROT_IN1
#define PIN_WR_ROT_IN2
#define PIN_WR_ROT_ADC

#define PIN_WR_EXT_EN
#define PIN_WR_EXT_IN1
#define PIN_WR_EXT_IN2
#define PIN_WR_EXT_ADC

#define SH_ROT_dir_pos() {digitalWrite(PIN_SH_ROT_IN1,LOW), digitalWrite(PIN_SH_ROT_IN2,HIGH);}
#define SH_ROT_dir_neg() {digitalWrite(PIN_SH_ROT_IN1,HIGH), digitalWrite(PIN_SH_ROT_IN2,LOW);}

#define SH_EXT_dir_pos() {digitalWrite(PIN_SH_EXT_IN1,LOW), digitalWrite(PIN_SH_EXT_IN2,HIGH);}
#define SH_EXT_dir_neg() {digitalWrite(PIN_SH_EXT_IN1,HIGH), digitalWrite(PIN_SH_EXT_IN2,LOW);}

#define EL_EXT_dir_pos() {digitalWrite(PIN_EL_EXT_IN1,LOW), digitalWrite(PIN_EL_EXT_IN2,HIGH);}
#define EL_EXT_dir_neg() {digitalWrite(PIN_EL_EXT_IN1,HIGH), digitalWrite(PIN_EL_EXT_IN2,LOW);}

#define WR_ROT_dir_pos() {digitalWrite(PIN_WR_ROT_IN1,LOW), digitalWrite(PIN_WR_ROT_IN2,HIGH);}
#define WR_ROT_dir_neg() {digitalWrite(PIN_WR_ROT_IN1,HIGH), digitalWrite(PIN_WR_ROT_IN2,LOW);}

#define WR_EXT_dir_pos() {digitalWrite(PIN_WR_EXT_IN1,LOW), digitalWrite(PIN_WR_EXT_IN2,HIGH);}
#define WR_EXT_dir_neg() {digitalWrite(PIN_WR_EXT_IN1,HIGH), digitalWrite(PIN_WR_EXT_IN2,LOW);}



//global variables
//_________________________________________________________________________________________________________________

//Prototype function
//_________________________________________________________________________________________________________________
void motor_setup();
void motor_run(byte PIN, int ControlValue);
void motor_set_dir(byte PIN, int ControlValue);


#endif