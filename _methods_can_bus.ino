/*
	Methods for reading and writing can bus messages
*/

//includes
//_________________________________________________________________________________________________________________
#include <SPI.h>
#include "mcp_can.h"



//defines
//_________________________________________________________________________________________________________________
#define PIN_CAN_CS		10	//MCP2515 chip select pin

#define FRAMETYPE		0	//frame type of CAN bus. 0=stadard, 1=extended 

#define MANIP_STAT		0x310



//timer variables
//_________________________________________________________________________________________________________________
int t_cantransmit_interval = 1000;
unsigned long t_cantransmit_prev;



//objects
//_________________________________________________________________________________________________________________
MCP_CAN CAN(PIN_CAN_CS);



//Read incoming can messages
//_____________________________________________________________________________________________________________
void can_read()
{
	if (CAN_MSGAVAIL == CAN.checkReceive())
	{
		//Read data
		unsigned long ID;
		byte rxlen = 0;
		byte rxbuf[8];
		CAN.readMsgBufID(&ID, &rxlen, rxbuf);

		//handle data
		switch (ID)
		{
		case GLOB_DRIVE:
			radius = rxbuf[2] << 24 | rxbuf[3] << 16 | rxbuf[4] << 8 | rxbuf[5];
			break;
		case STEER_XX_PID:
			pid_man = rxbuf[0] & 0x01;
			pid_p = (rxbuf[1] << 8 | rxbuf[2]) / 100.0;
			pid_i = (rxbuf[3] << 8 | rxbuf[4]) / 100.0;
			pid_d = (rxbuf[5] << 8 | rxbuf[6]) / 100.0;
			pid_CV_man = rxbuf[7];

			myPID.setGains(pid_p, pid_i, pid_d);
			break;
		case STEED_XX_CAL:
			potMinus90deg = (rxbuf[0] << 8 | rxbuf[1]);
			potMinus90deg = (rxbuf[2] << 8 | rxbuf[3]);
			break;
		default:
			break;
		}


	}
}


//write can messages
//_____________________________________________________________________________________________________________
void can_read()
{
	if (millis() - t_cantransmit_prev > t_cantransmit_interval)
	{
		//Construct message buffers
		byte canbuf_stat[2] = { status, alive };

		//Send
		CAN.sendMsgBuf(MANIP_STAT, FRAMETYPE, 2, canbuf_stat);
		

		t_cantransmit_prev = millis();
	}
}
