/*
	Code running on MISC Viking 3 - T1's MR02-Manipulator module.

	descr...


	Authors: Rein Åsmund Torsvik & Jonas Haldorsen, MISC 2018-07-06
*/





//includes
//_________________________________________________________________________________________________________________
#include <SPI.h>
#include <Servo.h>
#include <math.h>
#include <limits.h>
#include "AutoPID\AutoPID.h"
#include "mcp_can.h"



//constants
//_________________________________________________________________________________________________________________
//#define PIN_SERVO		9
//#define PIN_POT			A0



//global variables
//_________________________________________________________________________________________________________________
byte status;				//status byte
byte alive;					//Watchdog (increment by 1/second)



enum operation_mode {		//operation mode
	masterslave,
	absloutekinematics,
	relativekinematics
};

operation_mode mode = operation_mode::masterslave;





//objects
//_________________________________________________________________________________________________________________
Servo servo;



//Setup
//_________________________________________________________________________________________________________________
void setup()
{
	Serial.begin(9600);
	Serial.println("MISC MR02 MANIMPULATOR\n");
	
	//Initialize CAN bus with baud rate 500kbps and clockset 8MHz
	Serial.print("Initializing CAN bus...\t");
	if (CAN_OK != CAN.begin(CAN_500KBPS, MCP_8MHz))
		Serial.println("[FAIL]");
	else
		Serial.println("[SUCCESS]");

	//init pins
	//pinMode(PIN_POT, INPUT);
	//pinMode(PIN_SERVO, OUTPUT);

	//initialize servo
	//Serial.print("Initializing servo...\t");
	//servo.attach(PIN_SERVO);
	//Serial.println("[DONE]");

	//initialize PID
	//myPID.setTimeStep(100);




	Serial.println("Setup finished. Starting MR02.");
}



//Program loop
//_________________________________________________________________________________________________________________
void loop()
{
	switch (mode)
	{
	case operation_mode::masterslave:
	{
		//do shit
	}
	break;
	case operation_mode::absloutekinematics:
	{
		//do something
	}
	break;
	case operation_mode::relativekinematics:
	{
		//do something else
	}
	break;
	default:
		break;
	}
	



	


	//set status bits
	//bitWrite(buf_stat[0], 1, positionReached);
	//bitWrite(buf_stat[0], 2, pastMaxAngle);








	//debug
	if (alive % 2 == 0)
	{
		/*
		Serial.print("r: ");
		Serial.print(radius);
		Serial.print(" a: ");
		Serial.print(analogRead(PIN_POT));
		Serial.print(" pos r: ");
		Serial.print(positionReached);
		Serial.print(" SP: ");
		Serial.print(pid_SP);
		Serial.print(" PV: ");
		Serial.print(pid_PV);
		Serial.print(" CV: ");
		Serial.print(pid_CV);
		Serial.print(" A/M: ");
		Serial.print(pid_man);
		Serial.print(" HB: ");
		Serial.print(alive);
		Serial.println();
		*/
	}



	//runtime variables
	alive = (millis() / 1000) % 256;

}
