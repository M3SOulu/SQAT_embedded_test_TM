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
int temperatures[TEMP_BUFFER] = { 0, 0, 0, 0, 0, 0, 0, 0 };

//
// return the Nth valuke in the temperatures array
//
int tm_get_temperature(int n) {
	return temperatures[n];
}

int temp_index = 0;

int temp_sum = 0;
int temp_old_sum = 0;

int temp_prev_average = 0;
int temp_current_average = 0;

display_message_t temp_trend = DISP_MSG_SAME;

//
// reset all temperature data (above, including array)
//
void tm_reset_data() {
	temp_index = 0;
	temperatures[0] = 0;
	temperatures[1] = 0;
	temperatures[2] = 0;
	temperatures[3] = 0;
	temperatures[4] = 0;
	temperatures[5] = 0;
	temperatures[6] = 0;
	temperatures[7] = 0;
}

//
// return the average
//
int tm_get_average() {
	temp_prev_average = temp_current_average;

	temp_current_average = 0;

	temp_current_average = (temperatures[0] + temperatures[1] + temperatures[2]
			+ temperatures[3] + temperatures[4] + temperatures[5]
			+ temperatures[6] + temperatures[7]) / 8;
	return temp_current_average;
}

void remove_first_temp() {
	int i = 0;
	for (i = 0; i < 7; i++) {
		temperatures[i] = temperatures[i + 1];
	}
	temperatures[i] = 0;
}
//
// update calculations
//
void tm_update_average(int temp) {

	if (temp_index == 8) {
		remove_first_temp();
		temp_index--;
	}
	temperatures[temp_index] = temp;
	temp_index++;
	tm_get_average();
}

//
// get the current trend value
//
display_message_t tm_get_trend() {
	if(temp_current_average < temp_prev_average)
		return DISP_MSG_DOWN;
	else if (temp_current_average > temp_prev_average)
		return DISP_MSG_UP;
	return DISP_MSG_SAME; // default
}
