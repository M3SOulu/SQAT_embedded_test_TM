/*
 * display.h
 *
 *  Created on: Jun 6, 2016
 *      Author: timppa
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define DISP_ERR_OVERFLOW  -1
#define DISP_ERR_UNDERFLOW -2
#define DISP_ERR_ILLEGAL   -3

#define DISP_SHOW_ALL   1
#define DISP_SHOW_NONE  0

#define SEGMENT_NONE 0
#define SEGMENT_ALL  0xFF

#define SEGMENT_0    0b11111100
#define SEGMENT_1    0b01100000
#define SEGMENT_u    0b00111000
#define SEGMENT_P    0b11001110
#define SEGMENT_A    0b11101110
#define SEGMENT_E    0b10011110
#define SEGMENT_d    0b01111010
#define SEGMENT_n    0b00101010
#define SEGMENT_m    0b11101100
#define SEGMENT_o    0b00111010
#define SEGMENT_P    0b11001110
#define SEGMENT_s    0b10110110
#define SEGMENT_w    0b01111110

int disp_off();
int disp_on(int alloff);
void disp_reset(int alloff);

typedef enum display_message_e {
	DISP_MSG_FIRST=-2,
	DISP_MSG_DOWN = -1,
	DISP_MSG_SAME = 0,
	DISP_MSG_UP   = 1,
	DISP_MSG_LAST
} display_message_t;

int disp_show_message( display_message_t message );

#endif /* DISPLAY_H_ */
