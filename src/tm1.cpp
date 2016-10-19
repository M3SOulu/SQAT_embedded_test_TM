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

int valid_temperature_count = 0;

display_message_t temp_trend = DISP_MSG_SAME;

//
// reset all temperature data (above, including array)
//
void tm_reset_data()
{
	temp_index=0;

	temp_sum=0;
	temp_old_sum = 0;

	temp_prev_average=0;
	temp_current_average=0;

	valid_temperature_count = 0;

	for (int i = 0; i < TEMP_BUFFER; i++) {
		temperatures[i] = -1;
	}
}

//
// update calculations
//
void tm_update_average(int temp)
{
	temp_old_sum = temp_sum;

	if (temp_index == TEMP_BUFFER) {
		temp_index = 0;
		temp_sum -= temperatures[temp_index];
	}

	temperatures[temp_index++] = temp;

	temp_sum += temp;

	if (valid_temperature_count < TEMP_BUFFER)
		++valid_temperature_count;

	temp_prev_average = temp_current_average;
	temp_current_average = temp_sum / valid_temperature_count;
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
	return DISP_MSG_SAME; // default
}
