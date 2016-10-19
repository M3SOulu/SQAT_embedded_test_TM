/*
 * delay.h
 *
 *  Created on: Oct 3, 2016
 *      Author: timppa
 */

#ifndef DELAY_H_
#define DELAY_H_

void delay(volatile int d);
//
// this causes delay of approx 1s (when clocking is the default)
//
void delay_1s();

#endif /* DELAY_H_ */
