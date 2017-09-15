/* STM32SerialRtiostream-ProfilerTimer.c
 *
 * Specifies profile timer access functions
 *
 * Copyright 2011 The MathWorks, Inc.
 */

#include "STM32SerialRtiostream-ProfilerTimer.h"
#include "STM32SerialRtiostream_Config.h"


//#include "STM32.h"
unsigned int* reloadVal = (unsigned int*)0xE000E014;
unsigned int* currentVal = (unsigned int*)0xE000E018;
static unsigned char L_init;

void profileTimerInit( void )
{
	//SysTick called every time currentVal 1 to 0. Then reloaded with reload val.
    *reloadVal = 0x00FFFFFF;
}


unsigned int profileTimerRead( unsigned int initTimer )
{
	unsigned int timerVal = 0x00FFFFFF;;
	if(initTimer == 0) {
	/*When initTimer is null, it is xilProfilingSectionStart */
		*currentVal = 0x00FFFFFF;
		L_init = 1;
	} else {
	/*When initTimer is NOT null, it is xilProfilingSectionEnd if init has been done L_init == 1 */	
		if(	L_init == 1) {
			timerVal = *currentVal;
			L_init = 0;
		} else {
			L_init = 1;
			*currentVal = 0x00FFFFFF;
		}
	}
    return(timerVal);
}

/****************************************************
                     SysTick_Handler callback function
		This handler is called every tick 
*****************************************************/
void HAL_SYSTICK_Callback(void)
{
}
