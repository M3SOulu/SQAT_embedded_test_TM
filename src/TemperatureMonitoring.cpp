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

	int temperature;

	int i;
	for( i=0; i<9; i++){
		temperature = tm_handle_sensor();
		tm_update_average(temperature);
		delay_1s();
	}
	display_message_t trend = tm_get_trend();
	disp_show_message( trend );

	while( 1 ){

		tm_handle_sensor();
		tm_update_average(temperature);
		trend = tm_get_trend();
		disp_show_message( trend );
		delay_1s();

	}
    return 0 ;
}
