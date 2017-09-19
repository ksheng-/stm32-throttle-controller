/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: etc_discovery_TIM.c
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
#include "etc_discovery_TIM.h"

TIM_DataLinkTypeDef* G_TIM_Data;       /* Pointer to TIMER data information*/
TIM_HandleTypeDef* G_TIM_Handler;      /* Pointer to TIMER handler */

/* TIM1 data information*/
TIM_DataLinkTypeDef TIM1_DataLink;

/* TIM1 polling timeout value. Number of Solver loop. (can be changed)*/
uint32_t G_TIM1_PollTimeOut = 10;

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] etc_discovery_TIM.c
 */
