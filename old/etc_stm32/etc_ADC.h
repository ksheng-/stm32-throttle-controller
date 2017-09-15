/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: etc_ADC.h
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

#ifndef RTW_HEADER_etc_ADC_h_
#define RTW_HEADER_etc_ADC_h_

//RP MODIF #include "etc_STM32.h"
#include "STM32_Config.h"

/**
 * @brief  ADC data information
 */
typedef struct {
  uint16_t* RegularValueBuffer;        /*!< Regular buffer for converted value*/
  uint16_t* InjectedValueBuffer;       /*!< Injected buffer for converted value*/
  uint32_t RegularCurrentRank;         /*!< Regular current rank*/
  uint32_t InjectedCurrentRank;        /*!< Injected current rank*/
  uint32_t nbRegChannel;               /*!< Number of regular channel*/
  uint32_t nbInjChannel;               /*!< Number of injected channel*/
  uint8_t useDMA;                      /*!< DMA aquisition mode */
  uint8_t IntEndOfAllConv;             /*!< EOS/JEOS Int at end of all conversions */
  void (* ItEOCFcn)(void);
  void (* ItJEOCFcn)(void);
  void (* ItAWDFcn)(void);
  void (* ItOVRFcn)(void);
} ADC_DataLinkTypeDef;

extern uint16_t G_NbAdcConf;           /* Number of ADC configured */

/* Array of ADC data information */
extern ADC_DataLinkTypeDef* G_ADC_Data[2];
extern ADC_HandleTypeDef* G_ADC_Handler[2];

/* ADC1 handler */
extern ADC_HandleTypeDef hadc1;

/* ADC1 Regular channel Converted value buffer */
extern uint16_t ADC1_RegularConvertedValue[1];

/* ADC1 data information*/
extern ADC_DataLinkTypeDef ADC1_DataLink;

/* ADC2 handler */
extern ADC_HandleTypeDef hadc2;

/* ADC2 Regular channel Converted value buffer */
extern uint16_t ADC2_RegularConvertedValue[1];

/* ADC2 data information*/
extern ADC_DataLinkTypeDef ADC2_DataLink;

#endif                                 /* RTW_HEADER_etc_ADC_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] etc_ADC.h
 */
