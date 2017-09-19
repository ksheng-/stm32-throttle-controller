/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: etc_discovery.c
 *
 * Code generated for Simulink model :etc_discovery.
 *
 * Model version      : 1.51
 * Simulink Coder version    : 8.10 (R2016a) 10-Feb-2016
 * TLC version       : 8.10 (Jan 14 2016)
 * C/C++ source code generated on  : Mon Sep 18 21:12:12 2017
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

/* Block signals and states (auto storage) */
D_Work rtDWork;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function */
void etc_discovery_step(void)
{
    real_T rtb_error;
    real_T rtb_Saturate;
    real_T rtb_FilterCoefficient;

    /* S-Function Block: <Root>/STM32_Config */

    /* S-Function Block: <Root>/ADC_Read */

    /* Read regular ADC1 value */
    for (uint16_t i=0;i<2;i++)
        if (HAL_ADC_PollForConversion(&hadc1, G_ADC1_PollTimeOut) == HAL_OK) {
            ADC1_RegularConvertedValue[i] = (uint16_t)HAL_ADC_GetValue(&hadc1);
        }

    /* Get regular rank1 output value from ADC1 regular value buffer */
    rtDWork.input = (uint16_t)ADC1_RegularConvertedValue[0];
    printf("APPS: %f -- ", rtDWork.input/4096.0);

    /* Re-Start ADC1 conversion */
    HAL_ADC_Start(&hadc1);

    /* S-Function Block: <Root>/ADC_Read1 */

    /* Read regular ADC2 value */
    for (uint16_t i=0;i<2;i++)
        if (HAL_ADC_PollForConversion(&hadc2, G_ADC2_PollTimeOut) == HAL_OK) {
            ADC2_RegularConvertedValue[i] = (uint16_t)HAL_ADC_GetValue(&hadc2);
        }

    /* Get regular rank1 output value from ADC2 regular value buffer */
    rtDWork.TPS = (uint16_t)ADC2_RegularConvertedValue[0];
    printf("TPS: %f -- ", rtDWork.TPS/4096.0);

    /* Re-Start ADC2 conversion */
    HAL_ADC_Start(&hadc2);

    /* Sum: '<Root>/Sum1' */
    rtb_error = rtDWork.input - rtDWork.TPS;

    /* Gain: '<S2>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2>/Filter'
     *  Gain: '<S2>/Derivative Gain'
     *  Sum: '<S2>/SumD'
     */
    rtb_FilterCoefficient = (0.00390218818507904 * rtb_error -
        rtDWork.Filter_DSTATE) * 218.373722092741;

    /* Sum: '<S2>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2>/Integrator'
     *  Gain: '<S2>/Proportional Gain'
     */
    rtb_Saturate = (0.177533835702716 * rtb_error + rtDWork.Integrator_DSTATE) +
        rtb_FilterCoefficient;

    /* Saturate: '<S2>/Saturate' */
    if (rtb_Saturate > 50.0) {
        rtb_Saturate = 50.0;
    } else {
        if (rtb_Saturate < -50.0) {
            rtb_Saturate = -50.0;
        }
    }

    /* End of Saturate: '<S2>/Saturate' */

    /* RelationalOperator: '<S1>/Compare' incorporates:
     *  Constant: '<S1>/Constant'
     */
    rtDWork.Compare = (uint8_T)(rtb_Saturate < 0.0);

    /* S-Function Block: <Root>/GPIO_Write */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, rtDWork.Compare);

    /* Abs: '<Root>/Abs' */
    rtDWork.dutycycle = fabs(rtb_Saturate);
    printf("DUTY: %f \n", rtDWork.dutycycle);

    /* Gain: '<S2>/Integral Gain' */
    rtb_error *= 1.438435490023;

    /* Update for DiscreteIntegrator: '<S2>/Integrator' */
    rtDWork.Integrator_DSTATE += 0.04 * rtb_error;

    /* Update for DiscreteIntegrator: '<S2>/Filter' */
    rtDWork.Filter_DSTATE += 0.04 * rtb_FilterCoefficient;

    /* Update for S-Function (TIMERS_Config): '<Root>/Timers' */
    if (rtDWork.dutycycle < 0) {
        /* Disable output and complementary output */
        (&htim1)->Instance->BDTR |= TIM_BDTR_MOE;//MOE = 1
        (&htim1)->Instance->BDTR &= ~TIM_BDTR_OSSR;//OSSR = 0
        (&htim1)->Instance->CCER &= ~TIM_CCER_CC1E;//CC1E = 0
        (&htim1)->Instance->CCER &= ~TIM_CCER_CC1NE;//CC1NE = 0
        (&htim1)->Instance->CR2 &= ~TIM_CR2_OIS1;//OIS1 = 0
        (&htim1)->Instance->CR2 &= ~TIM_CR2_OIS1N;//OIS1N = 0
    } else {
        // Enable output and complementary output and update dutyCycle
        (&htim1)->Instance->BDTR |= TIM_BDTR_MOE;//MOE = 1
        (&htim1)->Instance->CCER |= TIM_CCER_CC1E;//CC1E = 1
        (&htim1)->Instance->CCER |= TIM_CCER_CC1NE;//CC1NE = 1

        // Channel1 duty cycle is an input port
        __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, (uint32_t)(rtDWork.dutycycle
                              * (&htim1)->Instance->ARR / 100));
    }
}

/* Model initialize function */
void etc_discovery_initialize(void)
{
    /* user code (Start function Body) */

    /* ADC1 initialization */
    /*Store ADC1 data information and its handler */
    G_ADC_Data[G_NbAdcConf] = &ADC1_DataLink;
    G_ADC_Handler[G_NbAdcConf] = &hadc1;
    G_NbAdcConf++;                     /*Inc number of configured ADC */
    ADC1_DataLink.RegularValueBuffer = ADC1_RegularConvertedValue;
    ADC1_DataLink.RegularCurrentRank = 0;
    ADC1_DataLink.nbRegChannel = 2;
    ADC1_DataLink.InjectedValueBuffer = NULL;
    ADC1_DataLink.InjectedCurrentRank = ADC_INJECTED_RANK_1;
    ADC1_DataLink.nbInjChannel = 0;

    /* Interrupt vector initialization */
    ADC1_DataLink.ItEOCFcn = NULL;
    ADC1_DataLink.ItJEOCFcn = NULL;
    ADC1_DataLink.ItAWDFcn = NULL;
    ADC1_DataLink.ItOVRFcn = NULL;

    /* Force data alignment to Right */
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;

    /* DMA not used */
    ADC1_DataLink.useDMA = false;

    /* EOC/JEOC at end of single channel conversion */
    ADC1_DataLink.IntEndOfAllConv = false;

    /* Start ADC1 conversion */
    HAL_ADC_Start(&hadc1);

    /* ADC2 initialization */
    /*Store ADC2 data information and its handler */
    G_ADC_Data[G_NbAdcConf] = &ADC2_DataLink;
    G_ADC_Handler[G_NbAdcConf] = &hadc2;
    G_NbAdcConf++;                     /*Inc number of configured ADC */
    ADC2_DataLink.RegularValueBuffer = ADC2_RegularConvertedValue;
    ADC2_DataLink.RegularCurrentRank = 0;
    ADC2_DataLink.nbRegChannel = 2;
    ADC2_DataLink.InjectedValueBuffer = NULL;
    ADC2_DataLink.InjectedCurrentRank = ADC_INJECTED_RANK_1;
    ADC2_DataLink.nbInjChannel = 0;

    /* Interrupt vector initialization */
    ADC2_DataLink.ItEOCFcn = NULL;
    ADC2_DataLink.ItJEOCFcn = NULL;
    ADC2_DataLink.ItAWDFcn = NULL;
    ADC2_DataLink.ItOVRFcn = NULL;

    /* Force data alignment to Right */
    hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;

    /* DMA not used */
    ADC2_DataLink.useDMA = false;

    /* EOC/JEOC at end of single channel conversion */
    ADC2_DataLink.IntEndOfAllConv = false;

    /* Start ADC2 conversion */
    HAL_ADC_Start(&hadc2);

    /*Store TIM1 data information and its handler */
    G_TIM_Data = &TIM1_DataLink;
    G_TIM_Handler = &htim1;

    /*Store TIM information */
    TIM1_DataLink.TIM_Prescaler = 0;
    TIM1_DataLink.TIM_APBClock = 32000000;
    TIM1_DataLink.TIM_ARR = 640000 - 1;
    TIM1_DataLink.TIM_Clock = 3.2E+7;
    TIM1_DataLink.CH1_type = OUTPUT_PWM;
    TIM1_DataLink.CH2_type = UNKNOWN;
    TIM1_DataLink.CH3_type = UNKNOWN;
    TIM1_DataLink.CH4_type = UNKNOWN;

    /* Interrupt vector initialization */
    TIM1_DataLink.ItUpFcn = NULL;
    TIM1_DataLink.ItTrgFcn = NULL;
    TIM1_DataLink.ItComFcn = NULL;
    TIM1_DataLink.ItBrkFcn = NULL;
    TIM1_DataLink.ItCcFcn = NULL;

    /*Update register value with blocset value*/
    /*Prescaler*/
    (&htim1)->Instance->PSC |= 0;

    /*Autoreload: ARR */
    __HAL_TIM_SetAutoreload(&htim1, 640000 - 1);

    /*Set CH1 Pulse value*/
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, (uint32_t)(3));

    /* Wait for htim1 State READY */
    while ((&htim1)->State == HAL_TIM_STATE_BUSY) {
    }

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

    /* Start for S-Function (ADC_Read): '<Root>/ADC_Read' */
    ;
    ;

    /* Start for S-Function (ADC_Read): '<Root>/ADC_Read1' */
    ;
    ;

    /* Start for S-Function (TIMERS_Config): '<Root>/Timers' */
    ;
    ;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] etc_discovery.c
 */
