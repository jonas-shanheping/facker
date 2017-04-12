/**
  ******************************************************************************
  * @file    TIM/TIM_TimeBase/Inc/ft_manager.h
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
#ifndef _FT_MANAGER_H_
#define _FT_MANAGER_H_

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "stm32f411e_discovery.h"
/* Exported types ------------------------------------------------------------*/
enum task_name{
    IDLE = 0,
    IR_SEND_TASK,
    IR_RECV_TASK
};

typedef struct{
    uint8_t irs_flag;
    uint8_t irr_flag;
}str_tm_flag;

typedef struct{
    uint8_t current_task;
    uint8_t last_task;

    str_tm_flag task;
}str_tm;




/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* User can use this section to tailor TIMx instance used and associated 
   resources */


/* Exported functions ------------------------------------------------------- */


#endif /* _FT_SEND_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
