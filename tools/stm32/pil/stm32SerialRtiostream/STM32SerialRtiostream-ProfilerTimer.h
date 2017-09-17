/* STM32SerialRtiostream-ProfilerTimer.h
 *
 * Specifies function prototypes for profile timer access functions
 *
 * Copyright 2011 The MathWorks, Inc.
*/

#ifndef _PROFILERTIMER_H
#define _PROFILERTIMER_H

void profileTimerInit(void);       
unsigned int profileTimerRead(unsigned int initTimer);
void SysTick_Handler(void);
#endif
        
 