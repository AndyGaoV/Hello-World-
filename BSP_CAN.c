/**
  ******************************************************************************
  * @file    BSP_CAN.c
  * @author  WangBo
  * @version V1.0.0
  * @date    2012-9-12
  * @brief   CAN Config.
  ******************************************************************************
  * @attention
  * ���ļ�������STM32F105��STM32F107��˫CAN��������оƬ����CAN��������оƬ��Ҫ����ʵ����Ҫ�޸ĳ���
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BSP_CAN.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
// CAN���������ã�
// #define CAN_BAUDRATE  1000		/* 1MBps   */	// ������Ҫѡ��CAN��ͨѶ������
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
	//10.�����ж�ʹ�ܣ����жϱ�־λ
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
	//6.CAN1�Ĵ�����ʼ��
	CAN_DeInit(CAN1);
	CAN_DeInit(CAN2);
	//7.��CAN_InitStruct�е�ÿһ��������ȱʡֵ����
	CAN_StructInit(&CAN_InitStructure);
	//8.CAN1��ʼ��
	CAN_InitStructure.CAN_TTCM=DISABLE;//ʧ��ʱ�䴥��ͨѶģʽ
	CAN_InitStructure.CAN_ABOM=ENABLE;//ʧ���Զ����߹���
	CAN_InitStructure.CAN_AWUM=DISABLE;//ʧ���Զ�����ģʽ
	CAN_InitStructure.CAN_NART=DISABLE;//ʧ�ܷ��Զ��ش���
	CAN_InitStructure.CAN_RFLM=DISABLE;//ʧ�ܽ���FIFO����ģʽ
	CAN_InitStructure.CAN_TXFP=ENABLE;//ʹ�ܷ���FIFO���ȼ�
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;//������������ģʽ

	//50K
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;//ͬ����Ծ���Ϊ1��tq
	CAN_InitStructure.CAN_BS1=CAN_BS1_13tq;//ʱ���1Ϊ3��tq
	CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;//ʱ���2Ϊ2��tq
	CAN_InitStructure.CAN_Prescaler=45;//����������Ϊ50KBPS����ɫ��������
	//125K
	// CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;//ͬ����Ծ���Ϊ1��tq
	// CAN_InitStructure.CAN_BS1=CAN_BS1_13tq;//ʱ���1Ϊ3��tq
	// CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;//ʱ���2Ϊ2��tq
	// CAN_InitStructure.CAN_Prescaler=18;//����������Ϊ125KBPS
	//500K
	// CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;//ͬ����Ծ���Ϊ1��tq
	// CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;//ʱ���1Ϊ3��tq
	// CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;//ʱ���2Ϊ2��tq
	// CAN_InitStructure.CAN_Prescaler=12;//����������Ϊ500KBPS
	//	1M
	// CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;//ͬ����Ծ���Ϊ1��tq
	// CAN_InitStructure.CAN_BS1=CAN_BS1_6tq;//ʱ���1Ϊ3��tq
	// CAN_InitStructure.CAN_BS2=CAN_BS2_5tq;//ʱ���2Ϊ2��tq
	// CAN_InitStructure.CAN_Prescaler=3;//����������Ϊ1000KBPS
	//	80k
	// CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;//ͬ����Ծ���Ϊ1��tq
	// CAN_InitStructure.CAN_BS1=CAN_BS1_13tq;//ʱ���1Ϊ3��tq
	// CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;//ʱ���2Ϊ2��tq
	// CAN_InitStructure.CAN_Prescaler=28;//����������Ϊ80KBPS

	/*�����ʼ��㹫ʽ
	BAUD=pclk1/((bs1+bs2+sjw)*CAN_Prescaler)=36000000/6*CAN_Prescaler
	CAN_Prescaler=6000000/baud;
	��BAUD=125KBPS,�� CAN_Prescaler=6000000/125000=48
	*/
	CAN_Init(CAN1,&CAN_InitStructure);
	CAN_Init(CAN2,&CAN_InitStructure);
	//CAN_Init(CAN2,&CAN_InitStructure);
	//9.CAN1����������
	CAN_FilterInitStructure.CAN_FilterNumber=0;//ָ���˴���ʼ���Ĺ�����
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;//�趨Ϊ��־������λģʽ
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;//32λ������
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;//�趨��������ʶ���ĸ߶�λ
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0001;//�趨��������־���ĵͶ�λ
	//CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//�趨���������α�ʶ���߶�λ
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//�趨���������α�ʶ���߶�λ
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;//�趨���������α�־���Ͷ�λ
	//CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;//�趨���������α�־���Ͷ�λ
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;//������FIFOָ�������0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;//ʹ�ܹ�����
	CAN_FilterInit(&CAN_FilterInitStructure);//��������ʼ��

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
	//1.��CAN1�˿ڵ�����ʱ�Ӻ͸���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//|RCC_APB2Periph_GPIOB
	//2.����tx1Ϊ�����������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_12);

	//3.����rx1Ϊ��������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//3.����tx2Ϊ�����������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);

	//4.����rx2Ϊ��������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//4.��������Ϊ���ù���
	//����Ӳ����ֱ������PA11��PA12�����Դ˴����ý���ӳ�����
	/* Remap CAN1 and CAN2 GPIOs */
	// GPIO_PinRemapConfig(GPIO_Remap1_CAN1 , ENABLE);	// ��Ӳ������ӳ��������IO�ڣ��˴�������û��ֲ����GPIO_Remap1_CAN1��GPIO_Remap2_CAN1
	// GPIO_PinRemapConfig(GPIO_Remap_CAN2, ENABLE);	// ��Ӳ������ӳ��������IO�ڣ��˴�������û��ֲ����GPIO_Remap_CAN2

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
