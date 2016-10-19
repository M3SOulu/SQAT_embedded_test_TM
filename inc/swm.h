/*
 * swm.h
 *
 *  Created on: Oct 3, 2016
 *      Author: timppa
 */

#ifndef SWM_H_
#define SWM_H_

#define SWM_RC_OK           0
#define SWM_RC_PARAM_ERROR -1

//
// creates SWM configuration for LEDs, RESET and debug
//
void swm_config_LED();
int swm_config_i2c(LPC_SYSCTL_T* pLPC_SYSCON,LPC_SWM_T* pLPC_SWM);

#endif /* SWM_H_ */
