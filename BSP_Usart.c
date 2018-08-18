/**
  ******************************************************************************
  * @file    BSP_Usart.c
  * @author  WangBo
  * @version V1.0.0
  * @date    2012-9-12
  * @brief   Usart Config.
  ******************************************************************************
  * @attention
  * ���ļ�������STM32F105��STM32F107��Usart��������оƬ
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BSP_Usart.h"
#include "BSP_ID.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
// Usart���������ã�


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

	//7.����485��ʹ֮Ϊ���
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
	//8.���ý����жϣ����жϱ�־λ

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

	//5.���ڳ�ʼ��
	USART_InitStructure.USART_BaudRate=115200;//����������Ϊ115200
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//����λ8λ
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//ֹͣλ1λ
	USART_InitStructure.USART_Parity=USART_Parity_No;//û����żУ��
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��ֹӲ�������ƣ���ֹRTS��CTS�ź�
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//���պͷ��Ͷ�ʹ��

	//USART_Init(USART1,&USART_InitStructure);
	USART_Init(USART2,&USART_InitStructure);
	//USART_Init(USART2,&USART_InitStructure);
	USART_InitStructure.USART_BaudRate=9600;//����������Ϊ9600
	USART_Init(UART5,&USART_InitStructure);

	//6.ʹ�ܴ���
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
//2.����TX2��PD5��Ϊ���ù������� PA2 PA3
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	// 3.����RX2(PD6)Ϊ��������
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
	//4.��USART��ʱ��
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

	//3.USART2�����ж���������ȫ���ж�
	//NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel=UART5_IRQn;
	NVIC_Init(&NVIC_InitStructure);
}
