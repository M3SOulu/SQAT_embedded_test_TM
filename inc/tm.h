/*
 * tm.h
 *
 *  Created on: Oct 11, 2016
 *      Author: timppa
 */

#ifndef TM_H_
#define TM_H_

#include "display.h"

int tm_get_temperature(int index);
void tm_reset_data();
void tm_update_average(int temp);
int tm_handle_sensor();
display_message_t tm_get_trend();

#endif /* TM_H_ */
