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

#define SEGMENT_NONE 0x00
#define SEGMENT_ALL  0xFF

#define SEGMENT_U    0x1C
#define SEGMENT_P    0x73
#define SEGMENT_A    0x77
#define SEGMENT_E    0x79
#define SEGMENT_D    0x5E
#define SEGMENT_N    0x54
#define SEGMENT_M    0x37
#define SEGMENT_O    0x5C
#define SEGMENT_P    0x73
#define SEGMENT_S    0x6D
#define SEGMENT_W    0x7E

#define SEGMENT_0    0x3F
#define SEGMENT_1    0X06

int disp_off();
int disp_on(int alloff);
void disp_reset(int alloff);

typedef enum display_message_e {
	DISP_MSG_FIRST=-2,
	DISP_MSG_DOWN = -1,
	DISP_MSG_SAME = 0,
	DISP_MSG_UP   = 1,
	DISP_MSG_LAST = 2
} display_message_t;

int disp_show_message( display_message_t message );

#endif /* DISPLAY_H_ */
