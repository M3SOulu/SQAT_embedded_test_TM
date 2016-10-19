/*
 * tm.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: timppa
 */

#include "hardware.h"
#include "i2c.h"
#include "display.h"
#include "delay.h"

#include "tm.h"

static char disp_msg_data[10] = { 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, };
//
// get temperature from i2c sensor
//
int tm_handle_sensor()
{
	int rc;
	char data;
	return i2c_read(0x90, 0, 0, disp_msg_data, 1);
}
