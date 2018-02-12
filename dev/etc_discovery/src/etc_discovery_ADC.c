/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: etc_discovery_ADC.c
 *
 * Code generated for Simulink model :etc_discovery.
 *
 * Model version      : 1.80
 * Simulink Coder version    : 8.12 (R2017a) 16-Feb-2017
 * TLC version       : 8.12 (Feb 10 2017)
 * C/C++ source code generated on  : Sun Feb 11 20:02:21 2018
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

#include "etc_discovery.h"
#include "etc_discovery_ADC.h"

uint16_t G_NbAdcConf = 0;              /* Number of ADC configured */

/* Array of ADC data information */
ADC_DataLinkTypeDef* G_ADC_Data[2];
ADC_HandleTypeDef* G_ADC_Handler[2];

/* ADC1 Regular channel Converted value buffer */
uint16_t ADC1_RegularConvertedValue[2];

/* ADC1 data information*/
ADC_DataLinkTypeDef ADC1_DataLink;

/* ADC1 polling timeout value. Number of Solver loop. (can be changed)*/
uint32_t G_ADC1_PollTimeOut = 10;

/* ADC2 Regular channel Converted value buffer */
uint16_t ADC2_RegularConvertedValue[2];

/* ADC2 data information*/
ADC_DataLinkTypeDef ADC2_DataLink;

/* ADC2 polling timeout value. Number of Solver loop. (can be changed)*/
uint32_t G_ADC2_PollTimeOut = 10;

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] etc_discovery_ADC.c
 */
