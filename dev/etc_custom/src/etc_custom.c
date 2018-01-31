/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: etc_custom.c
 *
 * Code generated for Simulink model :etc_custom.
 *
 * Model version      : 1.51
 * Simulink Coder version    : 8.10 (R2016a) 10-Feb-2016
 * TLC version       : 8.10 (Jan 14 2016)
 * C/C++ source code generated on  : Thu Jan 18 16:22:03 2018
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

#include "etc_custom.h"

/* Block signals and states (auto storage) */
D_Work rtDWork;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function */
void etc_custom_step(void)
{
    real_T rtb_error;
    real_T rtb_Saturate;
    real_T rtb_TSamp;

    /* S-Function Block: <Root>/STM32_Config */

    /* S-Function Block: <Root>/ADC_Read */

    /* Read regular ADC1 value */
    for (uint16_t i=0;i<2;i++)
        if (HAL_ADC_PollForConversion(&hadc1, G_ADC1_PollTimeOut) == HAL_OK) {
            ADC1_RegularConvertedValue[i] = (uint16_t)HAL_ADC_GetValue(&hadc1);
        }

    /* Get regular rank1 output value from ADC1 regular value buffer */
    rtDWork.apps0 = (uint16_t)ADC1_RegularConvertedValue[0];

    /* Get regular rank2 output value from ADC1 regular value buffer */
    rtDWork.apps1 = (uint16_t)ADC1_RegularConvertedValue[1];

    /* Re-Start ADC1 conversion */
    HAL_ADC_Start(&hadc1);

    /* S-Function Block: <Root>/ADC_Read3 */

    /* Read regular ADC2 value */
    for (uint16_t i=0;i<2;i++)
        if (HAL_ADC_PollForConversion(&hadc2, G_ADC2_PollTimeOut) == HAL_OK) {
            ADC2_RegularConvertedValue[i] = (uint16_t)HAL_ADC_GetValue(&hadc2);
        }

    /* Get regular rank1 output value from ADC2 regular value buffer */
    rtDWork.tps0 = (uint16_t)ADC2_RegularConvertedValue[0];

    /* Get regular rank2 output value from ADC2 regular value buffer */
    rtDWork.tps1 = (uint16_t)ADC2_RegularConvertedValue[1];

    /* Re-Start ADC2 conversion */
    HAL_ADC_Start(&hadc2);

    /* Sum: '<Root>/Sum1' incorporates:
     *  Gain: '<Root>/Gain'
     *  Gain: '<Root>/Gain1'
     *  Sum: '<Root>/Add'
     *  Sum: '<Root>/Add1'
     */
    rtb_error = (rtDWork.apps0 + rtDWork.apps1) * 0.5 - (rtDWork.tps0 +
        rtDWork.tps1) * 0.5;

    /* SampleTimeMath: '<S4>/TSamp' incorporates:
     *  Gain: '<S1>/Derivative Gain'
     *
     * About '<S4>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     */
    rtb_TSamp = 0.002 * rtb_error * 5.0;

    /* Sum: '<S1>/Sum' incorporates:
     *  Delay: '<S4>/UD'
     *  DiscreteIntegrator: '<S1>/Integrator'
     *  Gain: '<S1>/Proportional Gain'
     *  Sum: '<S4>/Diff'
     */
    rtb_Saturate = (0.98 * rtb_error + rtDWork.Integrator_DSTATE) + (rtb_TSamp -
        rtDWork.UD_DSTATE);

    /* Saturate: '<S1>/Saturate' */
    if (rtb_Saturate > 75.0) {
        rtb_Saturate = 75.0;
    } else {
        if (rtb_Saturate < -75.0) {
            rtb_Saturate = -75.0;
        }
    }

    /* End of Saturate: '<S1>/Saturate' */

    /* Abs: '<Root>/Abs' */
    rtDWork.duty = fabs(rtb_Saturate);

    /* If: '<Root>/If' incorporates:
     *  Constant: '<S2>/Constant'
     *  Constant: '<S3>/Constant'
     */
    if (rtb_Saturate > 0.0) {
        /* Outputs for IfAction SubSystem: '<Root>/forward' incorporates:
         *  ActionPort: '<S2>/Action Port'
         */

        /* Update for S-Function (TIMERS_Config): '<S2>/Timers' */
        if (rtDWork.duty < 0) {
            /* Disable output and complementary output */
            (&htim1)->Instance->BDTR |= TIM_BDTR_MOE;//MOE = 1
            (&htim1)->Instance->BDTR &= ~TIM_BDTR_OSSR;//OSSR = 0
            (&htim1)->Instance->CCER &= ~TIM_CCER_CC3E;//CC3E = 0
            (&htim1)->Instance->CCER &= ~TIM_CCER_CC3NE;//CC3NE = 0
            (&htim1)->Instance->CR2 &= ~TIM_CR2_OIS3;//OIS3 = 0
            (&htim1)->Instance->CR2 &= ~TIM_CR2_OIS3N;//OIS3N = 0
        } else {
            /* Enable output and complementary output and update dutyCycle*/
            (&htim1)->Instance->BDTR |= TIM_BDTR_MOE;//MOE = 1
            (&htim1)->Instance->CCER |= TIM_CCER_CC3E;//CC3E = 1
            (&htim1)->Instance->CCER |= TIM_CCER_CC3NE;//CC3NE = 1

            /* Channel3 duty cycle is an input port */
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, (uint32_t)(rtDWork.duty *
                                  (&htim1)->Instance->ARR / 100));
        }

        if (0.0 < 0) {
            /* Disable output and complementary output */
            (&htim1)->Instance->BDTR |= TIM_BDTR_MOE;//MOE = 1
            (&htim1)->Instance->BDTR &= ~TIM_BDTR_OSSR;//OSSR = 0
            (&htim1)->Instance->CCER &= ~TIM_CCER_CC4E;//CC4E = 0
            (&htim1)->Instance->CR2 &= ~TIM_CR2_OIS4;//OIS4 = 0
        } else {
            /* Enable output and complementary output and update dutyCycle*/
            (&htim1)->Instance->BDTR |= TIM_BDTR_MOE;//MOE = 1
            (&htim1)->Instance->CCER |= TIM_CCER_CC4E;//CC4E = 1

            /* Channel4 duty cycle is an input port */
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, (uint32_t)(0.0 * (&htim1)
                                  ->Instance->ARR / 100));
        }

        /* End of Outputs for SubSystem: '<Root>/forward' */
    } else {
        /* Outputs for IfAction SubSystem: '<Root>/reverse' incorporates:
         *  ActionPort: '<S3>/Action Port'
         */

        /* Update for S-Function (TIMERS_Config): '<S3>/Timers' */
        if (0.0 < 0) {
            /* Disable output and complementary output */
            (&htim1)->Instance->BDTR |= TIM_BDTR_MOE;//MOE = 1
            (&htim1)->Instance->BDTR &= ~TIM_BDTR_OSSR;//OSSR = 0
            (&htim1)->Instance->CCER &= ~TIM_CCER_CC3E;//CC3E = 0
            (&htim1)->Instance->CCER &= ~TIM_CCER_CC3NE;//CC3NE = 0
            (&htim1)->Instance->CR2 &= ~TIM_CR2_OIS3;//OIS3 = 0
            (&htim1)->Instance->CR2 &= ~TIM_CR2_OIS3N;//OIS3N = 0
        } else {
            /* Enable output and complementary output and update dutyCycle*/
            (&htim1)->Instance->BDTR |= TIM_BDTR_MOE;//MOE = 1
            (&htim1)->Instance->CCER |= TIM_CCER_CC3E;//CC3E = 1
            (&htim1)->Instance->CCER |= TIM_CCER_CC3NE;//CC3NE = 1

            /* Channel3 duty cycle is an input port */
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, (uint32_t)(0.0 * (&htim1)
                                  ->Instance->ARR / 100));
        }

        if (rtDWork.duty < 0) {
            /* Disable output and complementary output */
            (&htim1)->Instance->BDTR |= TIM_BDTR_MOE;//MOE = 1
            (&htim1)->Instance->BDTR &= ~TIM_BDTR_OSSR;//OSSR = 0
            (&htim1)->Instance->CCER &= ~TIM_CCER_CC4E;//CC4E = 0
            (&htim1)->Instance->CR2 &= ~TIM_CR2_OIS4;//OIS4 = 0
        } else {
            /* Enable output and complementary output and update dutyCycle*/
            (&htim1)->Instance->BDTR |= TIM_BDTR_MOE;//MOE = 1
            (&htim1)->Instance->CCER |= TIM_CCER_CC4E;//CC4E = 1

            /* Channel4 duty cycle is an input port */
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, (uint32_t)(rtDWork.duty *
                                  (&htim1)->Instance->ARR / 100));
        }

        /* End of Outputs for SubSystem: '<Root>/reverse' */
    }

    /* End of If: '<Root>/If' */

    /* Update for DiscreteIntegrator: '<S1>/Integrator' incorporates:
     *  Gain: '<S1>/Integral Gain'
     */
    rtDWork.Integrator_DSTATE += 0.0 * rtb_error * 0.2;

    /* Update for Delay: '<S4>/UD' */
    rtDWork.UD_DSTATE = rtb_TSamp;
}

/* Model initialize function */
void etc_custom_initialize(void)
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
    G_TIM_Data[G_NbTimConf] = &TIM1_DataLink;
    G_TIM_Handler[G_NbTimConf] = &htim1;
    G_NbTimConf++;                     /*Inc number of configured TIM */

    /*Store TIM information */
    TIM1_DataLink.TIM_Prescaler = 0;
    TIM1_DataLink.TIM_APBClock = 84000000;
    TIM1_DataLink.TIM_ARR = 4200 - 1;
    TIM1_DataLink.TIM_Clock = 8.4E+7;
    TIM1_DataLink.CH1_type = OUTPUT_PWM;
    TIM1_DataLink.CH2_type = OUTPUT_PWM;
    TIM1_DataLink.CH3_type = OUTPUT_PWM;
    TIM1_DataLink.CH4_type = OUTPUT_PWM;

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
    __HAL_TIM_SetAutoreload(&htim1, 4200 - 1);

    /*Set CH3 Pulse value*/
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, (uint32_t)(3));

    /*Set CH4 Pulse value*/
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, (uint32_t)(3));

    /* Wait for htim1 State READY */
    while ((&htim1)->State == HAL_TIM_STATE_BUSY) {
    }

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

    /* Enable the complementary PWM output 3 */
    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);

    /* Wait for htim1 State READY */
    while ((&htim1)->State == HAL_TIM_STATE_BUSY) {
    }

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

    /* Start for S-Function (ADC_Read): '<Root>/ADC_Read' */
    ;
    ;

    /* Start for S-Function (ADC_Read): '<Root>/ADC_Read3' */
    ;
    ;

    /* Start for IfAction SubSystem: '<Root>/forward' */

    /* Start for S-Function (TIMERS_Config): '<S2>/Timers' */
    ;
    ;

    /* End of Start for SubSystem: '<Root>/forward' */

    /* Start for IfAction SubSystem: '<Root>/reverse' */

    /* Start for S-Function (TIMERS_Config): '<S3>/Timers' */
    ;

    /* End of Start for SubSystem: '<Root>/reverse' */
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] etc_custom.c
 */
