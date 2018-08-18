/**
  ******************************************************************************
  * @file    BSP_CAN.c
  * @author  WangBo
  * @version V1.0.0
  * @date    2012-9-12
  * @brief   CAN Config.
  ******************************************************************************
  * @attention
  * 此文件适用于STM32F105或STM32F107带双CAN控制器的芯片，单CAN控制器的芯片需要根据实际需要修改程序
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BSP_CAN.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
// CAN波特率设置：
// #define CAN_BAUDRATE  1000		/* 1MBps   */	// 根据需要选择CAN的通讯波特率
// #define CAN_BAUDRATE  500		/* 500kBps */
// #define CAN_BAUDRATE  250		/* 250kBps */
#define CAN_BAUDRATE  125			/* 125kBps */
// #define CAN_BAUDRATE  100		/* 100kBps */
// #define CAN_BAUDRATE  50			/* 50kBps  */
// #define CAN_BAUDRATE  20			/* 20kBps  */
// #define CAN_BAUDRATE  10			/* 10kBps  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  initializes CAN1 and CAN2.
  * @param  vu32 CanTxId
  * @retval None
  */
CanTxMsg My_CanTxMsg;
void BSP_CAN_Config()
{

	/* Uarts Clocks Configuration */
	CAN_RCC_Configuration();

	/* CAN NVIC configuration */
	CAN_NVIC_Config();

	/* Uarts GPIO configuration */
	CAN_GPIO_Configuration();

	/* CANs configuration */
	CAN_Initialize();

	/* IT Configuration for CAN1 */
	//10.接收中断使能，清中断标志位
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
	CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);

	CAN_ClearFlag(CAN1,CAN_FLAG_FMP0);
	CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);

	CAN_ClearFlag(CAN2,CAN_FLAG_FMP0);
	CAN_ClearITPendingBit(CAN2,CAN_IT_FMP0);

	My_CanTxMsg.IDE=CAN_ID_STD;
	My_CanTxMsg.StdId=0x400;
	My_CanTxMsg.DLC=1;
	My_CanTxMsg.RTR=CAN_RTR_DATA;
	My_CanTxMsg.Data[0]=0x01;

}

/**
  * @brief  Configures CAN1 and CAN2.
  * @param  None
  * @retval None
  */
void CAN_Initialize(void)
{
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	//6.CAN1寄存器初始化
	CAN_DeInit(CAN1);
	CAN_DeInit(CAN2);
	//7.将CAN_InitStruct中的每一个参数按缺省值填入
	CAN_StructInit(&CAN_InitStructure);
	//8.CAN1初始化
	CAN_InitStructure.CAN_TTCM=DISABLE;//失能时间触发通讯模式
	CAN_InitStructure.CAN_ABOM=ENABLE;//失能自动离线管理
	CAN_InitStructure.CAN_AWUM=DISABLE;//失能自动唤醒模式
	CAN_InitStructure.CAN_NART=DISABLE;//失能非自动重传输
	CAN_InitStructure.CAN_RFLM=DISABLE;//失能接收FIFO锁定模式
	CAN_InitStructure.CAN_TXFP=ENABLE;//使能发送FIFO优先级
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;//设置正常工作模式

	//50K
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;//同步跳跃宽度为1个tq
	CAN_InitStructure.CAN_BS1=CAN_BS1_13tq;//时间段1为3个tq
	CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;//时间段2为2个tq
	CAN_InitStructure.CAN_Prescaler=45;//波特率设置为50KBPS（蓝色传感器）
	//125K
	// CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;//同步跳跃宽度为1个tq
	// CAN_InitStructure.CAN_BS1=CAN_BS1_13tq;//时间段1为3个tq
	// CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;//时间段2为2个tq
	// CAN_InitStructure.CAN_Prescaler=18;//波特率设置为125KBPS
	//500K
	// CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;//同步跳跃宽度为1个tq
	// CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;//时间段1为3个tq
	// CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;//时间段2为2个tq
	// CAN_InitStructure.CAN_Prescaler=12;//波特率设置为500KBPS
	//	1M
	// CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;//同步跳跃宽度为1个tq
	// CAN_InitStructure.CAN_BS1=CAN_BS1_6tq;//时间段1为3个tq
	// CAN_InitStructure.CAN_BS2=CAN_BS2_5tq;//时间段2为2个tq
	// CAN_InitStructure.CAN_Prescaler=3;//波特率设置为1000KBPS
	//	80k
	// CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;//同步跳跃宽度为1个tq
	// CAN_InitStructure.CAN_BS1=CAN_BS1_13tq;//时间段1为3个tq
	// CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;//时间段2为2个tq
	// CAN_InitStructure.CAN_Prescaler=28;//波特率设置为80KBPS

	/*波特率计算公式
	BAUD=pclk1/((bs1+bs2+sjw)*CAN_Prescaler)=36000000/6*CAN_Prescaler
	CAN_Prescaler=6000000/baud;
	设BAUD=125KBPS,则 CAN_Prescaler=6000000/125000=48
	*/
	CAN_Init(CAN1,&CAN_InitStructure);
	CAN_Init(CAN2,&CAN_InitStructure);
	//CAN_Init(CAN2,&CAN_InitStructure);
	//9.CAN1过滤器设置
	CAN_FilterInitStructure.CAN_FilterNumber=0;//指定了待初始化的过滤器
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;//设定为标志符屏蔽位模式
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;//32位过滤器
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;//设定过滤器标识符的高段位
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0001;//设定过滤器标志符的低段位
	//CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//设定过滤器屏蔽标识符高段位
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//设定过滤器屏蔽标识符高段位
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;//设定过滤器屏蔽标志符低段位
	//CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;//设定过滤器屏蔽标志符低段位
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;//过滤器FIFO指向过滤器0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;//使能过滤器
	CAN_FilterInit(&CAN_FilterInitStructure);//过滤器初始化

	CAN_FilterInitStructure.CAN_FilterNumber = 14;
	CAN_FilterInit(&CAN_FilterInitStructure);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void CAN_GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* Configure CAN1 and CAN2 IOs **********************************************/
	/* GPIOB, GPIOD and AFIO clocks enable */
	//1.打开CAN1端口的外设时钟和复用时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//|RCC_APB2Periph_GPIOB
	//2.配置tx1为复用推挽输出
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_12);

	//3.配置rx1为上拉输入
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//3.配置tx2为复用推挽输出
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);

	//4.配置rx2为上拉输入
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//4.配置两端为复用功能
	//由于硬件上直接练到PA11和PA12，所以此处不用进行映射操作
	/* Remap CAN1 and CAN2 GPIOs */
	// GPIO_PinRemapConfig(GPIO_Remap1_CAN1 , ENABLE);	// 若硬件上重映射至其他IO口，此处须根据用户手册改至GPIO_Remap1_CAN1或GPIO_Remap2_CAN1
	// GPIO_PinRemapConfig(GPIO_Remap_CAN2, ENABLE);	// 若硬件上重映射至其他IO口，此处须根据用户手册改至GPIO_Remap_CAN2

}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void CAN_RCC_Configuration(void)
{
	/* Configure CAN1 and CAN2 **************************************************/
	/* CAN1 and CAN2 Periph clocks enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
}

/**
  * @brief  Configures the NVIC for CAN.
  * @param  None
  * @retval None
  */
void CAN_NVIC_Config(void)
{

	NVIC_InitTypeDef  NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x1;
	NVIC_Init(&NVIC_InitStructure);

}
