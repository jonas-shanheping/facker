/**
  ******************************************************************************
  * @file    TIM/TIM_TimeBase/Inc/ft_send.h
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
#ifndef _FT_SEND_H_
#define _FT_SEND_H_

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "stm32f411e_discovery.h"
/* Exported types ------------------------------------------------------------*/


#define  IR_SEND_BUF_LENS    32


typedef struct{
  uint8_t s_buf[IR_SEND_BUF_LENS];
  uint8_t s_flag;
  uint8_t s_lens;
  uint32_t s_cnt;
}str_irs;




/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* User can use this section to tailor TIMx instance used and associated 
   resources */


/* Exported functions ------------------------------------------------------- */
extern str_irs gstr_irs;

#endif /* _FT_SEND_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
