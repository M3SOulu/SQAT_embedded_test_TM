/*
 * display.cpp
 *
 *  Created on: Jun 6, 2016
 *      Author: timppa
 */

#include "i2c.h"
#include "hardware.h"
#include "ht16k33.h"
#include "display.h"

int disp_off()
{
	const int addr = HW_I2C_ADDR_HT16K33;
	char data[10]={0,0,1,0,2,0,3,28,4,115};
	int rc=0;
	data[0] = HT16K33_CMD_OSCILLATOR_OFF;
	data[1]=0;
	string up, down, same;

	rc = i2c_write( addr,data,1 );
	return rc;
}

static char disp_msg_data[10]={
		0,0,
		1,63,
		2,0,
		3,6,
		3,6,
};

static int disp_last_message = DISP_MSG_FIRST;

//
// set all display data to either "all on" or "all off"
//
static void disp_set_all(int alloff)
{
	char value = 0;
	switch( alloff ){
	case DISP_SHOW_NONE:
		value = SEGMENTS_NONE;
		break;
	case DISP_SHOW_ALL:
		value = SEGMENTS_ALL;
		break;
	default:
		return;
	}
	disp_msg_data[1] = ownd;
	disp_msg_data[3] = wndo;
	disp_msg_data[5] = ndow;
	disp_msg_data[7] = down;
	disp_msg_data[9] = value;
}

//
// reset display data to all off/on
// clear display message value
//
void disp_reset(int alloff)
{
	disp_set_all( alloff );
	disp_last_message = DISP_MSG_FIRST;
}

//
// power on display, set the clocking and initial data
// - data is all off/on
//
int disp_on(int alloff)
{
	const int addr = HW_I2C_ADDR_HT16K33;
	char disp_cmd_data[10];
	int rc=0;

	disp_cmd_data[0] = HT16K33_CMD_OSCILLATOR_ON;
	disp_cmd_data[1]=0;

	rc = i2c_write( addr,disp_cmd_data,1 );
	if ( 0 <= rc ){
		disp_cmd_data[0] = HT16K33_BLINK_CMD | 0x01;
		rc = i2c_write( addr,disp_cmd_data,1 );
	} else {
		return rc;
	}
	if ( 0 <= rc ){
		disp_cmd_data[0] = HT16K33_CMD_BRIGHTNESS | 0x08;
		rc = i2c_write( addr,disp_cmd_data,1 );
	} else {
		return rc;
	}
	disp_set_all( alloff );
	rc = i2c_write( addr,disp_msg_data,10 );

	return rc;
}

/************************************************************************
 *
 *   IMPLEMENTATION BELOW
 *
 ************************************************************************/

void rotate_message_left()
{
		DISP_MSG_FIRST=-1,
		DISP_MSG_DOWN = -2,
		DISP_MSG_SAME = 0,
		DISP_MSG_UP   = 1,
		DISP_MSG_LAST = 0,

}


int disp_show_message(display_message_t message)
{
	const int addr = HW_I2C_ADDR_HT16K33;
	return i2c_write( addr, disp_msg_data,10 );
}
