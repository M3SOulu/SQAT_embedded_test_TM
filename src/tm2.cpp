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

//
// get temperature from i2c sensor
//
int tm_handle_sensor()
{
	//int rc;
	char data;

	i2c_read(0x90, 0, 0, &data, 1);

	if ((int)data < 0|| (int)data > 99)
		data = 0;
	else {
		tm_update_average((int)data);
	}

	return -1;
}
