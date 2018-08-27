#ifndef _methods_can_bus.h
#define _methods_can_bus.h

// the #include statment and code go here...



/* HEADER FILE
	Methods for reading and writing can bus messages
*/



//includes
//_________________________________________________________________________________________________________________
#include <SPI.h>
#include "mcp_can.h"
#include "MISC_MR02_Manipulator.ino"



//defines
//_________________________________________________________________________________________________________________
#define PIN_CAN_CS		10	//MCP2515 chip select pin

#define FRAMETYPE		0	//frame type of CAN bus. 0=stadard, 1=extended 

#define MANIP_STAT		0x600
#define MANIP_CMD		0x601
#define MANIP_MODE		0x602
#define MANIP_EF_POS_PV	0x610
#define MANIP_EF_POS_SP 0x611
#define MANIP_EF_ROT_PV 0x612
#define MANIP_EF_ROT_SP 0x613
#define MANIP_SH_PV		0x621
#define MANIP_SH_SP		0x622
#define MANIP_EL_PV		0x631
#define MANIP_EL_SP		0x632
#define MANIP_WR_PV		0x641
#define MANIP_WR_SP		0x642



//timer variables
//_________________________________________________________________________________________________________________
int t_cantransmit_interval = 1000;
unsigned long t_cantransmit_prev;


#endif