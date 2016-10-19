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

// Use these variables if you find them useful
// throw them away if not

#define TEMP_BUFFER 8
int temperatures[TEMP_BUFFER] = {
		0,0,0,0,
		0,0,0,0
};

//
// return the Nth valuke in the temperatures array
//
int tm_get_temperature(int n)
{
	return -1;
}

int temp_index=0;

int temp_sum=0;
int temp_old_sum = 0;

int temp_prev_average=0;
int temp_current_average=0;

display_message_t temp_trend = DISP_MSG_SAME;

//
// reset all temperature data (above, including array)
//
void tm_reset_data()
{
	for (int i=0; i<7; i++) {
		temperatures[i] = 0;
	}
}

//
// update calculations
//
void tm_update_average(int temp)
{
	for (int i=0; i<7; i++) {
		temperatures[i] = temperatures[i+1];
	}
	temperatures[7] = temp;
}
//
// return the average
//
int tm_get_average()
{
	return temp_current_average;
}
//
// get the current trend value
//
display_message_t tm_get_trend()
{
	int temp_diff = temp_current_average - temp_prev_average;
	if (temp_diff > 0) {
		return DISP_MSG_UP;
	} else if (temp_diff < 0) {
		return DISP_MSG_DOWN;
	}
	return DISP_MSG_SAME; // default
}
