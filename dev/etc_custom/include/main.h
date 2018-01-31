/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define GPIO_EXT_Pin GPIO_PIN_13
#define GPIO_EXT_GPIO_Port GPIOC
#define UPSHIFT_IN_Pin GPIO_PIN_0
#define UPSHIFT_IN_GPIO_Port GPIOC
#define DOWNSHIFT_IN_Pin GPIO_PIN_1
#define DOWNSHIFT_IN_GPIO_Port GPIOC
#define UPSHIFT_OUT_Pin GPIO_PIN_2
#define UPSHIFT_OUT_GPIO_Port GPIOC
#define DOWNSHIFT_OUT_Pin GPIO_PIN_3
#define DOWNSHIFT_OUT_GPIO_Port GPIOC
#define TPS_0_Pin GPIO_PIN_0
#define TPS_0_GPIO_Port GPIOA
#define TPS_1_Pin GPIO_PIN_1
#define TPS_1_GPIO_Port GPIOA
#define APPS_0_Pin GPIO_PIN_2
#define APPS_0_GPIO_Port GPIOA
#define APPS_1_Pin GPIO_PIN_3
#define APPS_1_GPIO_Port GPIOA
#define BSE_Pin GPIO_PIN_4
#define BSE_GPIO_Port GPIOA
#define SERVO_ENABLE_Pin GPIO_PIN_5
#define SERVO_ENABLE_GPIO_Port GPIOA
#define ADC_EXT_Pin GPIO_PIN_4
#define ADC_EXT_GPIO_Port GPIOC
#define ADC_EXTC5_Pin GPIO_PIN_5
#define ADC_EXTC5_GPIO_Port GPIOC
#define ADC_EXTB1_Pin GPIO_PIN_1
#define ADC_EXTB1_GPIO_Port GPIOB
#define GPIO_EXTB12_Pin GPIO_PIN_12
#define GPIO_EXTB12_GPIO_Port GPIOB
#define SERVO_OUT_N_Pin GPIO_PIN_15
#define SERVO_OUT_N_GPIO_Port GPIOB
#define WS_FL_Pin GPIO_PIN_6
#define WS_FL_GPIO_Port GPIOC
#define WS_FR_Pin GPIO_PIN_7
#define WS_FR_GPIO_Port GPIOC
#define WS_BL_Pin GPIO_PIN_8
#define WS_BL_GPIO_Port GPIOC
#define WS_BR_Pin GPIO_PIN_9
#define WS_BR_GPIO_Port GPIOC
#define MC_0_Pin GPIO_PIN_10
#define MC_0_GPIO_Port GPIOA
#define MC_1_Pin GPIO_PIN_11
#define MC_1_GPIO_Port GPIOA
#define DBG_JTMS_SWDIO_Pin GPIO_PIN_13
#define DBG_JTMS_SWDIO_GPIO_Port GPIOA
#define DBG_JTCK_SWCLK_Pin GPIO_PIN_14
#define DBG_JTCK_SWCLK_GPIO_Port GPIOA
#define DBG_JTDI_Pin GPIO_PIN_15
#define DBG_JTDI_GPIO_Port GPIOA
#define DBG_JTDO_SWO_Pin GPIO_PIN_3
#define DBG_JTDO_SWO_GPIO_Port GPIOB
#define DBG_JTRST_Pin GPIO_PIN_4
#define DBG_JTRST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
