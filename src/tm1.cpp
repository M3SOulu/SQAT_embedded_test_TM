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
	return temperatures[n];
}

bool enough_data = false;
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
	for (int i = 0; i < TEMP_BUFFER; i++)
		temperatures[i] = 0;

	enough_data = false;
	temp_index=0;

	temp_sum=0;
	temp_old_sum = 0;

	temp_prev_average=0;
	temp_current_average=0;
}

//
// return the average
//
int tm_get_average()
{
	if (!enough_data) {
		return -1;
	}

	int sum = 0;
	for (int i = 0; i < TEMP_BUFFER; i++)
		sum += temperatures[i];

	return (sum / TEMP_BUFFER);
}

//
// update calculations
//
void tm_update_average(int temp)
{
	if (temp < 0 || temp > 99)
		return;

	if (!enough_data) {
		temp_index++;

		if (temp_index > 8)
			enough_data = true;
	}

	temp_prev_average = tm_get_average();

	for (int i = 1; i < TEMP_BUFFER; i++) {
		temperatures[i-1] = temperatures[i];
	}

	temperatures[TEMP_BUFFER-1] = temp;

	temp_current_average = tm_get_average();
}
//
// get the current trend value
//
display_message_t tm_get_trend()
{
	if (temp_current_average == temp_prev_average)
		return DISP_MSG_SAME;
	else if (temp_current_average < temp_prev_average)
		return DISP_MSG_DOWN;
	else
		return DISP_MSG_UP;
}

