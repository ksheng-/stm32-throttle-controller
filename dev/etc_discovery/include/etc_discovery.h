/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: etc_discovery.h
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

#ifndef RTW_HEADER_etc_discovery_h_
#define RTW_HEADER_etc_discovery_h_
#include <math.h>
#include "STM32_Config.h"
#include "etc_discovery_ADC.h"
#include "etc_discovery_TIM.h"
#ifndef etc_discovery_COMMON_INCLUDES_
# define etc_discovery_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* etc_discovery_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#define etc_discovery_M                (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
    real_T apps0;                      /* '<Root>/ADC_Read' */
    real_T apps1;                      /* '<Root>/ADC_Read' */
    real_T tps0;                       /* '<Root>/ADC_Read2' */
    real_T tps1;                       /* '<Root>/ADC_Read2' */
    real_T dutycycle;                  /* '<Root>/Abs' */
    real_T Integrator_DSTATE;          /* '<S2>/Integrator' */
    real_T UD_DSTATE;                  /* '<S3>/UD' */
    uint8_T Compare;                   /* '<S1>/Compare' */
} D_Work;

/* Real-time Model Data Structure */
struct tag_RTM {
    const char_T *errorStatus;
};

/* Block signals and states (auto storage) */
extern D_Work rtDWork;

/* Model entry point functions */
extern void etc_discovery_initialize(void);
extern void etc_discovery_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/DTDup' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'etc_discovery'
 * '<S1>'   : 'etc_discovery/Compare To Zero'
 * '<S2>'   : 'etc_discovery/Controller'
 * '<S3>'   : 'etc_discovery/Controller/Differentiator'
 */
#endif                                 /* RTW_HEADER_etc_discovery_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] etc_discovery.h
 */
