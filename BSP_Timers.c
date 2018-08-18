/**
  ******************************************************************************
  * @file    BSP_Timers.c
  * @author  WangBo
  * @version V1.0.0
  * @date    2012-9-12
  * @brief   Timers Config.
  ******************************************************************************
  * @attention
  * 此文件适用于STM32F105或STM32F107带Timers控制器的芯片
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BSP_Timers.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  initializes Timers1
  * @param  vu32 TimersTxId
  * @retval None
  */
void BSP_Timers_Config(void)
{
	/* Uarts Clocks Configuration */
	Timers_RCC_Configuration();

	/* Timers NVIC configuration */
	Timers_NVIC_Config();

	/* Uarts GPIO configuration */
	Timers_GPIO_Configuration();

	/* IT Configuration for Timers1 */
	Timers_Initialize();

	/* IT Configuration for Timers2 */
	//8.设置接收中断，清中断标志位
	 //3.使能中断，清中断标志位
	 TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	 TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
}




/**
  * @brief  Configures Timers1 and Timers2.
  * @param  None
  * @retval None
  */
void Timers_Initialize(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruture;
	
	//2.配置TIM2初始化结构体 72000000/2000/3600=10hz
	 TIM_TimeBaseInitStruture.TIM_ClockDivision=0x0;
	 TIM_TimeBaseInitStruture.TIM_CounterMode=TIM_CounterMode_Up;
	 //TIM_TimeBaseInitStruture.TIM_Period=7199; //200ms
	 //TIM_TimeBaseInitStruture.TIM_Period=17999; //500ms
	 //TIM_TimeBaseInitStruture.TIM_Period=3599;//100ms
	 //TIM_TimeBaseInitStruture.TIM_Period=4319;//120ms
	 //TIM_TimeBaseInitStruture.TIM_Period=1799;//50ms
	 //TIM_TimeBaseInitStruture.TIM_Period=4499;//125ms
	 TIM_TimeBaseInitStruture.TIM_Period=359;//10ms
	 TIM_TimeBaseInitStruture.TIM_Prescaler=1999;
	 TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruture);
	 
	  //4.开启TIM2
	 TIM_Cmd(TIM2,ENABLE);
}
/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void Timers_GPIO_Configuration(void)
{
	//GPIO_InitTypeDef GPIO_InitStructure;
	

}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void Timers_RCC_Configuration(void)
{
	/* Configure Timers1 and Timers2 **************************************************/
	/* Timers1 and Timers2 Periph clocks enable */
	//4.打开Timers的时钟
	//1.给外设配置时钟 TIM2为72Mhz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
}

/**
  * @brief  Configures the NVIC for Timers.
  * @param  None
  * @retval None
  */
void Timers_NVIC_Config(void)
{
	
	//1.定时器2允许并配置全局中断
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);


}
