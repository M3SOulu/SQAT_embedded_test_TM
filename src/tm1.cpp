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
int tm_get_temperature(int position){

		int lengthArray = sizeof(temperatures) / sizeof(temperatures[0]);

		if (position >= lengthArray){
			return -1;
		}

		else if (position < 0){
			return -1;
		}

		else{
		int returnValue = temperatures[position];

		return returnValue;
		}
	}

int temp_index=0;

int temp_sum=0;
int temp_old_sum = 0;

int temp_prev_average=1;
int temp_current_average=2;

//display_message_t temp_trend = DISP_MSG_SAME;

//
// reset all temperature data (above, including array)
//
void tm_reset_data()
{
}

//
// update calculations
//
void tm_update_average(int temp)
{
}
//
// return the average
//
int tm_get_average()
{
	/*int averageTemp = 0;
	int i = 0;
	for (i = 0; i < temperature.length; i++){
		averageTemp = averageTemp += temperature[i];
	}

	return averageTemp; */
	return -1;
}
//
// get the current trend value
//
display_message_t tm_get_trend()
{
	int temp_prev_average=1;
	int temp_current_average=2;

	if (temp_prev_average < temp_current_average){
		return DISP_MSG_UP;
	}
	else if (temp_prev_average > temp_current_average){
		return DISP_MSG_DOWN;
	}

	else {
	return DISP_MSG_SAME; // default
	}
}
