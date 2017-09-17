/* STM32SerialRtiostream-Rtiostream.c
 *
 * Specifies rtiostream functions to implement serial PIL
 *
 * NOTES: 
 *  - Baud rate is specified in UART_PIL_Configuration();
 *  - rtIOStreamSend & rtIOStreamRecv functions send and receive
 *    8-bit characters.
 *
 * Copyright 2011 The MathWorks, Inc.
 */

// Include header files
#include <stdlib.h>
#include <stdio.h>


#include "STM32SerialRtiostream-Rtiostream.h"
/* STM32SerialRtiostream_Config.h is generated with definitions 
depending on USART selection */
#include "STM32SerialRtiostream_Config.h"

static volatile uint8_t RxCplt = 0;
static volatile uint8_t TxCplt = 0;
		
// Function prototypes
void USARTx_IRQHandler (void);


/* Function: rtIOStreamOpen ================================================= */
/* Configuration of USART for rtIOStream =====================================*/
int rtIOStreamOpen(int argc, void * argv[])
{
    (void)argc;
    (void)argv;
    
	
    return SERVER_STREAM_ID;
}


/* Function: rtIOStreamClose ================================================ */
int rtIOStreamClose(int streamID)
{
    return RTIOSTREAM_NO_ERROR;
}


/* Function: rtIOStreamSend ================================================ */
int rtIOStreamSend(int streamID, const void *src, size_t size, size_t *sizeSent)
{
	(void)streamID; //streamID not used
			
	 TxCplt = 0;
	 
  	HAL_UART_Transmit_IT(PIL_USART_HANDLE, (uint8_t*)src, (uint16_t)size);
	
	//Wait for end of Tx
    while(!TxCplt);
	
    *sizeSent = size;	

    return RTIOSTREAM_NO_ERROR;
}


 /* Function: rtIOStreamRecv ================================================ */
int rtIOStreamRecv(int streamID, void * dst, size_t size, size_t * sizeRecv) 
{
    (void)streamID; //streamID not used
        
    //Rx not complete
	RxCplt = 0;
        
	//start Rx interrupt
	HAL_UART_Receive_IT(PIL_USART_HANDLE, (uint8_t*)dst, (uint16_t)size);	
	
	//Wait for end of Rx
    while(!RxCplt);
	
	*sizeRecv = size;
	
    return RTIOSTREAM_NO_ERROR;
}


/*******************************************************************************
* Function Name  : HAL_UART_RxCpltCallback
* Description    : Rx Transfer completed callbacks. 
* Input          : UART handle
*******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    //Rx complete
	RxCplt = 1;
}

/*******************************************************************************
* Function Name  : HAL_UART_TxCpltCallback
* Description    : Tx Transfer completed callbacks. 
* Input          : UART handle
*******************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    //Tx complete
	TxCplt = 1;
}

