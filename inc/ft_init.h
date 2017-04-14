/**
  ******************************************************************************
  * @file    TIM/TIM_TimeBase/Inc/ft_init.h
  * @author  Jonas
  * @version V1.0.0
  * @date    04-November-2016
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _FT_INIT_H_
#define _FT_INIT_H_

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "stm32f411e_discovery.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* User can use this section to tailor TIMx instance used and associated 
   resources */

/* Exported functions ------------------------------------------------------- */
void SystemClock_Config(void);
void ft_system_init(void);

#endif /* _FT_INIT_H_*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
