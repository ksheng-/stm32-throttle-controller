/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: etc_ADC.c
 *
 * Code generated for Simulink model :etc.
 *
 * Model version      : 1.33
 * Simulink Coder version    : 8.11 (R2016b) 25-Aug-2016
 * TLC version       : 8.11 (Jul 22 2016)
 * C/C++ source code generated on  : Sat Apr 01 17:58:38 2017
 *
 * Target selection: stm32.tlc
 * Embedded hardware selection: STMicroelectronics->STM32 32-bit Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 *
 *
 *
 * ******************************************************************************
 * * attention
 * *
 * * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * *
 * ******************************************************************************
 */

#include "etc.h"
#include "etc_ADC.h"

uint16_t G_NbAdcConf = 0;              /* Number of ADC configured */

/* Array of ADC data information */
ADC_DataLinkTypeDef* G_ADC_Data[2];
ADC_HandleTypeDef* G_ADC_Handler[2];

/* ADC1 Regular channel Converted value buffer */
uint16_t ADC1_RegularConvertedValue[1];

/* ADC1 data information*/
ADC_DataLinkTypeDef ADC1_DataLink;

/* ADC2 Regular channel Converted value buffer */
uint16_t ADC2_RegularConvertedValue[1];

/* ADC2 data information*/
ADC_DataLinkTypeDef ADC2_DataLink;

/*******************************************************************************
 * Function Name  : HAL_ADC_ConvCpltCallback
 * Description    : Regular interrupt conversion complete callback
 * Input          : ADC_HandleTypeDef*
 *******************************************************************************/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
  uint16_t L_AdcHandleIdx = 0;         /* Index to retreive ADC data information */
  ADC_DataLinkTypeDef* pL_ADC_Data = G_ADC_Data[0];/* Pt to the list of ADC data information */
  ADC_HandleTypeDef* pL_ADC_Handler = G_ADC_Handler[0];/* Pt to the list of ADC handler */
  for (L_AdcHandleIdx = 0;L_AdcHandleIdx < 2;L_AdcHandleIdx++) {
    pL_ADC_Handler = G_ADC_Handler[L_AdcHandleIdx];
    if (pL_ADC_Handler == AdcHandle) {
      pL_ADC_Data = G_ADC_Data[L_AdcHandleIdx];
      break;
    }
  }

  if (pL_ADC_Handler == AdcHandle) {
    if (pL_ADC_Data->useDMA == false) {
      /* Process It for current received channel */
      /* Store converted value of current regular channel */
      pL_ADC_Data->RegularValueBuffer[pL_ADC_Data->RegularCurrentRank] =
        HAL_ADC_GetValue(AdcHandle);

      /*Increment rank for next conversion*/
      pL_ADC_Data->RegularCurrentRank++;

      /* Test for max conversion channel number */
      if (pL_ADC_Data->RegularCurrentRank >= pL_ADC_Data->nbRegChannel) {
        pL_ADC_Data->RegularCurrentRank = 0;
      }
    }

    if (pL_ADC_Data->ItEOCFcn != NULL) {
      /* Call End Of Conversion function */
      pL_ADC_Data->ItEOCFcn();
    }
  }
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] etc_ADC.c
 */
