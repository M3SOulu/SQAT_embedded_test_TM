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
	char data[10];
	int rc=0;

	data[0] = HT16K33_CMD_OSCILLATOR_OFF;
	data[1]=0;

	rc = i2c_write( addr,data,1 );
	return rc;
}

static char disp_msg_data[10]={
		0,0,
		1,0,
		2,0,
		3,0,
		4,0,
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
	disp_msg_data[1] = value;
	disp_msg_data[3] = value;
	disp_msg_data[5] = value;
	disp_msg_data[7] = value;
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

int msg_index = 0;

char* table;

static char disp_msg_up[4]={0, 0, 28, 115
	/*0x00001C73, 28, 115
	0x001C7300,
	0x1C730000,
	0x7300001C*/
};

static char disp_msg_down[4] = { 0x5E, 0x5C, 0x7E, 0x54
	/*0x5E5C8254, 94, 92, 130, 84
	0x5C82545E,
	0x82545E5C,
	0x545E5C82*/
};

static char disp_msg_same[4] = { 0x6D, 0x77, 0x37, 0x79
	/*0x6D773779, 109, 119, 55, 121
	0x7737796D,
	0x37796D77,
	0x796D7737*/
};

void rotate_message_left()
{
	msg_index++;
	if (msg_index > 3)
		msg_index = 0;
}

//
// display message of:
//   - DISP_MSG_DOWN
//   - DISP_MSG_SAME
//   - DISP_MSG_UP
// if message is same as previous then rotate left
//
display_message_t prev_message = DISP_MSG_FIRST;
int disp_show_message(display_message_t message)
{
	bool invalid = false;

	if (message == prev_message) {
		rotate_message_left();
	} else if (message == DISP_MSG_DOWN) {
		table = disp_msg_down;
		msg_index = 0;
	} else if (message == DISP_MSG_UP) {
		table = disp_msg_up;
		msg_index = 0;
	} else if (message == DISP_MSG_SAME) {
		table = disp_msg_same;
		msg_index = 0;
	} else {
		invalid = true;
	}

	if (!invalid) {
		disp_msg_data[1] = table[msg_index];
		disp_msg_data[3] = table[(msg_index+1) % 4];
		disp_msg_data[7] = table[(msg_index+2) % 4];
		disp_msg_data[9] = table[(msg_index+3) % 4];

		prev_message = message;
	} else {
		disp_reset(0);
	}

	const int addr = HW_I2C_ADDR_HT16K33;
	return i2c_write( addr, disp_msg_data,10 );
}
