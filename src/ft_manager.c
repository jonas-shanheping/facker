/**
  ******************************************************************************
  * @file    TIM/TIM_TimeBase/Src/ft_manager.c 
  * @author  Jonas
  * @version V1.0.0
  * @date    12-April-2017
  * @brief   it is the facker task manager file
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft_manager.h"
#include "main.h"



/* Private typedef -----------------------------------------------------------*/



/* define ------------------------------------------------------------*/
/* macro -------------------------------------------------------------*/
/* variables ---------------------------------------------------------*/
str_tm gstr_tm;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  get current task
  * @param  None
  * @retval None
  */
uint8_t get_current_task()
{
    return gstr_tm.current_task;
}


/**
 * @brief  Task manager program
 * @param  None
 * @retval None
 */
void task_manager()
{

    if(gstr_tm.current_task == IDLE){

    }
    else if(gstr_tm.current_task == IR_SEND_TASK){
        
    }
    else if(gstr_tm.current_task == IR_RECV_TASK){

    }
}


/**
 * @brief  Task Idle
 * @param  None
 * @retval None
 */
void task_idle()
{

}


/**
 * @brief  Task Idle
 * @param  None
 * @retval None
 */
void task_irs()
{

}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
