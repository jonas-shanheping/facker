/**
******************************************************************************
* @file    TIM/TIM_TimeBase/Src/main.c 
* @author  MCD Application Team
* @version V1.0.3
* @date    04-November-2016
* @brief   This sample code shows how to use STM32F4xx TIM HAL API to generate
*          4 signals in PWM.
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
 * @{
 */

/** @addtogroup TIM_TimeBase
 * @{
 */ 

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
    ft_system_init();

    memset(gstr_irs.s_buf, 0x55, sizeof(gstr_irs.s_buf));

    int i = 0;

    BSP_LED_Off(LED4);
    for(i=0; i<100000; i++);
    BSP_LED_On(LED4);
    for(i=0; i<1000000000; i++);
    BSP_LED_Off(LED4);

    ft_timer_handle(TIMER3, TIMER_START);

    gstr_irs.s_flag = 1;

    /* Infinite loop */
    while (1){
        for(i=0; i<1000000; i++);

        BSP_LED_Toggle(LED3);
    }
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    uint8_t luc_cnt = 0;
    static uint32_t lsui_delay = 0;
    static uint8_t lsuc_flag = 0;

    #if 1
    
    if(((lsui_delay)%50) != 0){
        lsui_delay++;
        return;
    }

    luc_cnt = gstr_irs.s_cnt / 8;
    if(gstr_irs.s_flag ==  1){
        if(((gstr_irs.s_buf[luc_cnt]>>(gstr_irs.s_cnt%8))&0x01) > 0){
            if((lsuc_flag%2) == 0) BSP_LED_On(LED4);
            if((lsuc_flag%2) != 0) BSP_LED_Off(LED4);
        }
        else{
            if((lsuc_flag%2) == 0) BSP_LED_Off(LED4);
            if((lsuc_flag%2) != 0) BSP_LED_Off(LED4);
        }

        if((lsuc_flag++%2) != 0){
            gstr_irs.s_cnt++;
            lsui_delay++;
        }
    }
    else{
        lsuc_flag = 0;
        lsui_delay = 0;
        gstr_irs.s_cnt = 0;
    }

    gstr_irs.s_flag = (luc_cnt==(sizeof(gstr_irs.s_buf)-1)) ? 0 : gstr_irs.s_flag;

    #endif
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void Error_Handler(void)
{
    /* Turn LED5 on */
    BSP_LED_On(LED3);
    while(1)
        {
        }
}


#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
        {
        }
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
