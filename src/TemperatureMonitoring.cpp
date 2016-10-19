/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

#include "swm.h"
#include "delay.h"
#include "i2c.h"
#include "display.h"
//
#include "tm.h"

int main(void)
{
#if defined (__USE_LPCOPEN)
    SystemCoreClockUpdate();
#endif

    swm_config_i2c( LPC_SYSCON, LPC_SWM );
    i2c_reset();
	disp_on( DISP_SHOW_NONE );
	disp_reset( DISP_SHOW_NONE );

	tm_reset_data();
	/**
	 * TODO: Oscar to remove this (was in the original)
	 */
	int i;
	for( i=0; i<9; i++){
		tm_handle_sensor();
	}
	display_message_t trend = tm_get_trend();
	//disp_show_message( trend );
	/**
	 * TODO: Oscar to remove until here (was in the original)
	 */

	char disp_msg_data[10]={
			0,0,
			1,0,
			2,0,
			3,0,
			4,0,
	};

	while( 1 ){
		/**
		 * TODO: Oscar to remove this (was in the original)
		 */
		/*tm_handle_sensor();
		trend = tm_get_trend();
		trend
		disp_show_message( trend );*/
		/**
		 * TODO: Oscar to remove until here (was in the original)
		 */

		delay_1s();
		disp_show_message(DISP_MSG_DOWN);
		delay_1s();
		disp_msg_data[9] = 0;
		disp_msg_data[7] = 0;
		i2c_write( 0x70, disp_msg_data,10 );
	}
    return 0 ;
}
