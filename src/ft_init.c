/**
  ******************************************************************************
  * @file    TIM/TIM_TimeBase/Src/ft_init.c 
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
#include "ft_init.h"



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

/* Private functions ---------------------------------------------------------*/
/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow : 
 *            System Clock source            = PLL (HSI)
 *            SYSCLK(Hz)                     = 100000000
 *            HCLK(Hz)                       = 100000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 2
 *            APB2 Prescaler                 = 1
 *            HSI Frequency(Hz)              = 16000000
 *            PLL_M                          = 16
 *            PLL_N                          = 400
 *            PLL_P                          = 4
 *            PLL_Q                          = 7
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale2 mode
 *            Flash Latency(WS)              = 3
 * @param  None
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();
  
    /* The voltage scaling allows optimizing the power consumption when the device is 
       clocked below the maximum system frequency, to update the voltage scaling value 
       regarding system frequency refer to product datasheet.  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  
    /* Enable HSI Oscillator and activate PLL with HSI as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 0x10;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 400;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){
        
        Error_Handler();
    }
  
    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
       clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK){
        
        Error_Handler();
    }
}


/**
  * @brief  sys_timer_handle
  * @param  None
  * @retval None
  */
void sys_timer_handle(enum_tim timer_x, enum_tim timer_flag)
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
 * @brief  ft_sys_init
 * @param  None
 * @retval None
 */
void ft_system_init(void)
{
    /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
    */
    if(HAL_Init()!= HAL_OK) Error_Handler();

    /* Configure the system clock to 100 MHz */
    SystemClock_Config();

    /* Configure the system Timer */
    sys_timer_handle(TIMER3, TIMER_STOP);

    /* Configure the LED*/
    BSP_LED_Init(LED3);
    BSP_LED_Init(LED4);
    BSP_LED_Init(LED5);
    BSP_LED_Init(LED6);
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
