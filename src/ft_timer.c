/**
  ******************************************************************************
  * @file    TIM/TIM_TimeBase/Src/ft_timer.c 
  * @author  Jonas
  * @version V1.0.0
  * @date    12-April-2017
  * @brief   it is the facker task send file
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft_timer.h"



/* Private typedef -----------------------------------------------------------*/

/* Private define -------------------{TIMER1_INSTANCE, TIMER1_PRESCALER, TIMER1_PERIOD, TIMER1_CLOCK_DIVISION, TIMER1_COUNTER_MODE},-----------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/****************************************Timer configuration parameters declaration******************************************************/
TIM_HandleTypeDef gstr_tim_handle[TIMER_CNT];

str_tim gstr_tim[TIMER_CNT] = {
    {TIMER1_INSTANCE, TIMER1_PRESCALER, TIMER1_PERIOD, TIMER1_CLOCK_DIVISION, TIMER1_COUNTER_MODE},
    {TIMER2_INSTANCE, TIMER2_PRESCALER, TIMER2_PERIOD, TIMER2_CLOCK_DIVISION, TIMER2_COUNTER_MODE},
    {TIMER3_INSTANCE, TIMER3_PRESCALER, TIMER3_PERIOD, TIMER3_CLOCK_DIVISION, TIMER3_COUNTER_MODE},
    {TIMER4_INSTANCE, TIMER4_PRESCALER, TIMER4_PERIOD, TIMER4_CLOCK_DIVISION, TIMER4_COUNTER_MODE}
};

/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  sys_timer_handle
  * @param  None
  * @retval None
  */
void ft_timer_handle(enum_tim timer_x, enum_tim timer_flag)
{
    uint32_t uwPrescalerValue = 0;

    /*##-1- Configure the TIM peripheral #######################################*/ 
    /* -----------------------------------------------------------------------
       In this example TIM3 input clock (TIM3CLK) is set to 2 * APB1 clock (PCLK1), 
       since APB1 prescaler is different from 1.   
       TIM3CLK = 2 * PCLK1  
       PCLK1 = HCLK / 2 
       => TIM3CLK = HCLK = SystemCoreClock
       To get TIM3 counter clock at 10 KHz, the Prescaler is computed as following:
       Prescaler = (TIM3CLK / TIM3 counter clock) - 1
       Prescaler = (SystemCoreClock /10 KHz) - 1
       
       Note: 
       SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
       Each time the core clock (HCLK) changes, user had to update SystemCoreClock 
       variable value. Otherwise, any configuration based on this variable will be incorrect.
       This variable is updated in three ways:
       1) by calling CMSIS function SystemCoreClockUpdate()
       2) by calling HAL API function HAL_RCC_GetSysClockFreq()
       3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency  
       ----------------------------------------------------------------------- */  
  
    /* Compute the prescaler value to have TIM3 counter clock equal to 10 KHz 100000*/
    uwPrescalerValue = (uint32_t) ((SystemCoreClock/gstr_tim[timer_x].prescaler) - 1);
  
    /* Set TIMx instance */
    gstr_tim_handle[timer_x].Instance = gstr_tim[timer_x].instance;
   
    /* Initialize TIM3 peripheral as follow:
       + Period = 10000 - 1
       + Prescaler = ((SystemCoreClock/2)/10000) - 1
       + ClockDivision = 0
       + Counter direction = Up
    */
    gstr_tim_handle[timer_x].Init.Period = gstr_tim[timer_x].period - 1;
    gstr_tim_handle[timer_x].Init.Prescaler = uwPrescalerValue;
    gstr_tim_handle[timer_x].Init.ClockDivision = gstr_tim[timer_x].clock_division;
    gstr_tim_handle[timer_x].Init.CounterMode = gstr_tim[timer_x].counter_mode;
    if(HAL_TIM_Base_Init(&gstr_tim_handle[timer_x]) != HAL_OK){

        /* Initialization Error */
        Error_Handler();
    }

    if(((timer_flag==TIMER_START)?HAL_TIM_Base_Start_IT(&gstr_tim_handle[timer_x]):HAL_TIM_Base_Stop_IT(&gstr_tim_handle[timer_x])) != HAL_OK) {
        Error_Handler();
    }
}


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
