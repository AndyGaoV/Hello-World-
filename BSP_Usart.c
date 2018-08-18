/**
  ******************************************************************************
  * @file    BSP_Usart.c
  * @author  WangBo
  * @version V1.0.0
  * @date    2012-9-12
  * @brief   Usart Config.
  ******************************************************************************
  * @attention
  * 此文件适用于STM32F105或STM32F107带Usart控制器的芯片
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BSP_Usart.h"
#include "BSP_ID.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
// Usart波特率设置：


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  initializes Usart1
  * @param  vu32 UsartTxId
  * @retval None
  */
extern u8 DeviceID;
void BSP_Usarts_Config(void)
{
	/* Uarts Clocks Configuration */
	Usart_RCC_Configuration();

	/* Usart NVIC configuration */
	Usart_NVIC_Config();

	/* Uarts GPIO configuration */
	Usart_GPIO_Configuration();

	/* IT Configuration for Usart1 */
	Usart_Initialize();

	//7.设置485，使之为输出
		USART_Cmd(USART2,ENABLE);
		USART_Cmd(UART5,ENABLE);

		USART_ClearFlag(USART2,USART_FLAG_RXNE);
		USART_ClearFlag(UART5,USART_FLAG_RXNE);
		
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		USART_ClearITPendingBit(UART5,USART_IT_RXNE);

		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
	
		UART5_RECEIVE_DATE();


	/* IT Configuration for USART2 */
	//8.设置接收中断，清中断标志位

	USART_ClearFlag(USART2,USART_FLAG_TC);
	USART_ClearFlag(UART5,USART_FLAG_TC);
}

/**
  * @brief  Configures Usart1 and USART2.
  * @param  None
  * @retval None
  */
void Usart_Initialize(void)
{
	USART_InitTypeDef USART_InitStructure;

	//5.串口初始化
	USART_InitStructure.USART_BaudRate=115200;//波特率设置为115200
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//数据位8位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//停止位1位
	USART_InitStructure.USART_Parity=USART_Parity_No;//没有奇偶校验
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//禁止硬件流控制，禁止RTS和CTS信号
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//接收和发送都使能

	//USART_Init(USART1,&USART_InitStructure);
	USART_Init(USART2,&USART_InitStructure);
	//USART_Init(USART2,&USART_InitStructure);
	USART_InitStructure.USART_BaudRate=9600;//波特率设置为9600
	USART_Init(UART5,&USART_InitStructure);

	//6.使能串口
	// USART_Cmd(USART1,ENABLE);
	/* USART_Cmd(USART2,ENABLE);
	USART_Cmd(USART2,ENABLE);
	USART_Cmd(UART4,ENABLE);
	USART_Cmd(UART5,ENABLE);  */
}
/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void Usart_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
//USART1: REMAP TO PB6 PB7
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	
//	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
//2.配置TX2（PD5）为复用功能推挽 PA2 PA3
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	// 3.设置RX2(PD6)为浮空输入
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	

}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void Usart_RCC_Configuration(void)
{
	/* Configure Usart1 and USART2 **************************************************/
	/* Usart1 and USART2 Periph clocks enable */
	//4.打开USART的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_UART4|RCC_APB1Periph_UART5,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
}

/**
  * @brief  Configures the NVIC for Usart.
  * @param  None
  * @retval None
  */
void Usart_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;

	//3.USART2接收中断允许并配置全局中断
	//NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel=UART5_IRQn;
	NVIC_Init(&NVIC_InitStructure);
}
