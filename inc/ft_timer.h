/**
  ******************************************************************************
  * @file    TIM/TIM_TimeBase/Inc/ft_timer.h
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
#ifndef _FT_TIMER_H_
#define _FT_TIMER_H_

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "stm32f411e_discovery.h"

/* Exported types ------------------------------------------------------------*/


/************************Timer configuration parameters************************/
#define        TIMER_CNT        (4)

#define        TIMER1_INSTANCE           TIM1
#define        TIMER1_PRESCALER          100000
#define        TIMER1_PERIOD             2
#define        TIMER1_CLOCK_DIVISION     0
#define        TIMER1_COUNTER_MODE       TIM_COUNTERMODE_UP
#define        TIMER1_IRQn               TIM1_IRQn
#define        TIMER1_IRQHandler         TIM1_IRQHandler

#define        TIMER2_INSTANCE           TIM2
#define        TIMER2_PRESCALER          100000
#define        TIMER2_PERIOD             2
#define        TIMER2_CLOCK_DIVISION     0
#define        TIMER2_COUNTER_MODE       TIM_COUNTERMODE_UP
#define        TIMER2_IRQn               TIM2_IRQn
#define        TIMER2_IRQHandler         TIM2_IRQHandler

#define        TIMER3_INSTANCE           TIM3
#define        TIMER3_PRESCALER          100000
#define        TIMER3_PERIOD             2
#define        TIMER3_CLOCK_DIVISION     0
#define        TIMER3_COUNTER_MODE       TIM_COUNTERMODE_UP
#define        TIMER3_IRQn               TIM3_IRQn
#define        TIMER3_IRQHandler         TIM3_IRQHandler

#define        TIMER4_INSTANCE           TIM4
#define        TIMER4_PRESCALER          100000
#define        TIMER4_PERIOD             2
#define        TIMER4_CLOCK_DIVISION     0
#define        TIMER4_COUNTER_MODE       TIM_COUNTERMODE_UP
#define        TIMER4_IRQn               TIM4_IRQn
#define        TIMER4_IRQHandler         TIM4_IRQHandler

typedef enum {
    TIMER1 = 0,
    TIMER2 = 1,
    TIMER3 = 2,
    TIMER4 = 3,

    TIMER_STOP = 0,
    TIMER_START,
}enum_tim;

typedef struct{
    TIM_TypeDef *instance;
    uint32_t prescaler;
    uint32_t period;
    uint32_t clock_division;
    uint32_t counter_mode;
}str_tim;

extern TIM_HandleTypeDef gstr_tim_handle[TIMER_CNT];
extern str_tim gstr_tim[TIMER_CNT];

void ft_timer_handle(enum_tim timer_x, enum_tim timer_flag);

/*********************End---Timer configuration parameters---End*******************/


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* User can use this section to tailor TIMx instance used and associated 
   resources */

/* Exported functions ------------------------------------------------------- */

#endif /* _FT_INIT_H_*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
