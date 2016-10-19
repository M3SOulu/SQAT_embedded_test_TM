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

void rotate_message_left()
{
	char tmp_disp_msg_data_1 = disp_msg_data[1];
	disp_msg_data[1] = disp_msg_data[3];
	disp_msg_data[3] = disp_msg_data[7];
	disp_msg_data[7] = disp_msg_data[9];
	disp_msg_data[9] = tmp_disp_msg_data_1;
}

//
// display message of:
//   - DISP_MSG_DOWN
//   - DISP_MSG_SAME
//   - DISP_MSG_UP
// if message is same as previous then rotate left
//
int disp_show_message(display_message_t message)
{
	const int addr = HW_I2C_ADDR_HT16K33;

	switch (message) {
	case DISP_MSG_UP:
		disp_msg_data[1] = SEGMENTS_NONE;
		disp_msg_data[3] = SEGMENTS_NONE;
		disp_msg_data[5] = SEGMENTS_NONE;
		disp_msg_data[7] = SEGMENT_U;
		disp_msg_data[9] = SEGMENT_P;
		break;
	case DISP_MSG_DOWN:
		disp_msg_data[1] = SEGMENT_D;
		disp_msg_data[3] = SEGMENT_O;
		disp_msg_data[5] = SEGMENTS_NONE;
		disp_msg_data[7] = SEGMENT_W;
		disp_msg_data[9] = SEGMENT_N;
		break;
	 case DISP_MSG_SAME:
		disp_msg_data[1] = SEGMENT_S;
		disp_msg_data[3] = SEGMENT_A;
		disp_msg_data[5] = SEGMENTS_NONE;
		disp_msg_data[7] = SEGMENT_M;
		disp_msg_data[9] = SEGMENT_E;
		break;

	}

	return i2c_write( addr, disp_msg_data,10 );
}
