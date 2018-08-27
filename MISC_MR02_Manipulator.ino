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
#include "_methods_can_bus.h"
#include "_methods_motors.h"



//constants
//_________________________________________________________________________________________________________________
#define SH_ROT_home
#define SH_EXT_home
#define EL_EXT_home
#define WR_EXT_home
#define WR_EXT_home

#define PID_INIT_KP
#define PID_INIT_KI
#define PID_INIT_KD
#define MAX_SPEED


//global variables
//_________________________________________________________________________________________________________________
byte status;				//status byte
byte alive;					//Watchdog (increment by 1/second)
byte aliveold;

int EF_POS_SP[3]; // x(0) y(1) z(2)		desired		End effector relative position 
int EF_POS_PV[3]; //					actual
int EF_ROT_SP[3];
int EF_ROT_PV[3];

// desired joint positions
int SH_ROT_SP;	// Shoulder rotation
int SH_EXT_SP;	// Shoulder extention
int EL_EXT_SP;	// Elbow extention
int WR_ROT_SP;	// Wrist rotation
int WR_EXT_SP;	// Wrist extention

// actual joint positions
int SH_ROT_PV;
int SH_EXT_PV;
int EL_EXT_PV;
int WR_ROT_PV;
int WR_EXT_PV;

int SH_ROT_CV;
int SH_EXT_CV;
int EL_EXT_CV;
int WR_ROT_CV;
int WR_EXT_CV;

int t_mainloop_us = 5000;
unsigned long t_mainloop_us_prev;



enum operation_mode {		//operation mode
	masterslave,
	absloutekinematics,
	relativekinematics
};

operation_mode mode = operation_mode::masterslave;


//objects
//_________________________________________________________________________________________________________________
MCP_CAN CAN(PIN_CAN_CS);
AutoPID SHROT_PID(&SH_ROT_PV, &SH_ROT_SP, &SH_ROT_CV, MAX_SPEED, MAX_SPEED, PID_INIT_KP, PID_INIT_KI, PID_INIT_KD);
AutoPID SHEXT_PID(&SH_EXT_PV, &SH_EXT_SP, &SH_EXT_CV, MAX_SPEED, MAX_SPEED, PID_INIT_KP, PID_INIT_KI, PID_INIT_KD);
AutoPID ELEXT_PID(&EL_EXT_PV, &EL_EXT_SP, &EL_EXT_CV, MAX_SPEED, MAX_SPEED, PID_INIT_KP, PID_INIT_KI, PID_INIT_KD);
AutoPID WRROT_PID(&WR_ROT_PV, &WR_ROT_SP, &WR_ROT_CV, MAX_SPEED, MAX_SPEED, PID_INIT_KP, PID_INIT_KI, PID_INIT_KD);
AutoPID WREXT_PID(&WR_EXT_PV, &WR_EXT_SP, &WR_EXT_CV, MAX_SPEED, MAX_SPEED, PID_INIT_KP, PID_INIT_KI, PID_INIT_KD);


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
	motor_setup();

	//initialize PID
	SHROT_PID.setTimeStep(100);
	SHEXT_PID.setTimeStep(100);
	ELEXT_PID.setTimeStep(100);
	WRROT_PID.setTimeStep(100);
	WREXT_PID.setTimeStep(100);




	Serial.println("Setup finished. Starting MR02.");
}



//Program loop
//_________________________________________________________________________________________________________________
void loop()
{	

	if (micros() - t_mainloop_us_prev > t_mainloop_us) {  // 400HZ loop

		SH_ROT_PV = analogRead(PIN_SH_ROT_ADC);
		SH_EXT_PV = analogRead(PIN_SH_EXT_ADC);
		EL_EXT_PV = analogRead(PIN_EL_EXT_ADC);
		WR_ROT_PV = analogRead(PIN_WR_ROT_ADC);
		WR_EXT_PV = analogRead(PIN_WR_EXT_ADC);

		switch (mode)
		{
		case operation_mode::masterslave:
		{	
			SHROT_PID.run();
			SHEXT_PID.run();
			ELEXT_PID.run();
			WRROT_PID.run();
			WREXT_PID.run();

			motor_run(PIN_SH_ROT_EN, SH_ROT_CV);
			motor_run(PIN_SH_EXT_EN, SH_EXT_CV);
			motor_run(PIN_EL_EXT_EN, EL_EXT_CV);
			motor_run(PIN_WR_ROT_EN, WR_ROT_CV);
			motor_run(PIN_WR_EXT_EN, WR_EXT_CV);


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

	if (millis() - t_cantransmit_prev > t_cantransmit_interval)
	{	
		alive += 1;
		alive = alive % 256;
		byte canbuf_stat[2] = { status, alive };

		CAN.sendMsgBuf(MANIP_STAT, FRAMETYPE, 2, canbuf_stat);

		byte canbuf_SH_PV[4] = { SH_ROT_PV >> 8, SH_ROT_PV, SH_EXT_PV >> 8, SH_EXT_PV };
		CAN.sendMsgBuf(MANIP_SH_PV, FRAMETYPE, 4, canbuf_SH_PV);

		byte canbuf_EL_PV[2] = { EL_EXT_PV >> 8, EL_EXT_PV };
		CAN.sendMsgBuf(MANIP_EL_PV, FRAMETYPE, 2, canbuf_EL_PV);

		byte canbuf_WR_PV[4] = { WR_ROT_PV >> 8, WR_ROT_PV, WR_EXT_PV >> 8, WR_EXT_PV };
		CAN.sendMsgBuf(MANIP_WR_PV, FRAMETYPE, 4, canbuf_WR_PV);
	

		t_cantransmit_prev = millis();
	}


}
