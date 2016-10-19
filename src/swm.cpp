/*
 * swm.c
 *
 *  Created on: Oct 3, 2016
 *      Author: timppa
 */

//#include <LPC8xx.h>
#include "chip.h"
#include "swm.h"

// For SWM configuration reading/writing the clocking of SWM
// must be enabled. After the read/write the clocking can be
// disabled, saves power...
//

int swm_config_i2c(LPC_SYSCTL_T* pLPC_SYSCON,LPC_SWM_T* pLPC_SWM)
{
	if ( 0==pLPC_SYSCON || 0==pLPC_SWM ){
		return SWM_RC_PARAM_ERROR;
	}
	// enable system clock for SWM block: toggle bit 7 to one
	pLPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
//	LPC_SWM_T* pLPC_SWM = (LPC_SWM_T*)LPC_SWM;
	// setup SWM for GPIO, I2C (pins 10,11) and debugging stuff (SWCLK, SWDIO, RESET)
	pLPC_SWM->PINASSIGN[0] = 0xffff0004UL;
	pLPC_SWM->PINASSIGN[7] = 0x0affffffUL;
	pLPC_SWM->PINASSIGN[8] = 0xffffff0bUL;
	pLPC_SWM->PINENABLE0 = 0xffffffb3UL;
	// deactivate the clock of SWM (not needed any more)
	pLPC_SYSCON->SYSAHBCLKCTRL &= (~(1<<7));
	return SWM_RC_OK;
}
