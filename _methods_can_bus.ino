/*
	Methods for reading and writing can bus messages
*/

//includes
//_________________________________________________________________________________________________________________
#include "_methods_can_bus.h"


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
		case MANIP_CMD:
			
		case MANIP_MODE:			// Sets/changes the operation mode 
			switch (rxbuf[0]) {
			case 0x01:
				mode = operation_mode::masterslave;
				break;
			case 0x02:
				mode = operation_mode::relativekinematics;
				break;
			case 0x04:
				mode = operation_mode::absloutekinematics;
				break;
			}
			
			
		case MANIP_EF_POS_SP:
			EF_POS_SP[0] = (rxbuf[0] << 8) + rxbuf[1];
			EF_POS_SP[1] = (rxbuf[2] << 8) + rxbuf[3];
			EF_POS_SP[2] = (rxbuf[4] << 8) + rxbuf[5];
		
		case MANIP_EF_ROT_SP:
			EF_ROT_SP[0] = (rxbuf[0] << 8) + rxbuf[1];
			EF_ROT_SP[1] = (rxbuf[2] << 8) + rxbuf[3];
			EF_ROT_SP[2] = (rxbuf[4] << 8) + rxbuf[5];
			
		case MANIP_SH_SP:
			SH_ROT_SP = (rxbuf[0] << 8) + rxbuf[1];
			SH_EXT_SP = (rxbuf[2] << 8) + rxbuf[3];

		case MANIP_EL_SP:
			EL_EXT_SP = (rxbuf[0] << 8) + rxbuf[1];

		case MANIP_WR_SP:
			WR_ROT_SP = (rxbuf[0] << 8) + rxbuf[1];
			WR_EXT_SP = (rxbuf[2] << 8) + rxbuf[3];

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
