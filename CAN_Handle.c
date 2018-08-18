/**
  ******************************************************************************
  * @file    CAN_Handle.c
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
#include "CAN_Handle.h"
#include "BSP_RTC.h"
#include "BSP_ID.h"
#include "BSP_CAN.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
// Usart���������ã�

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CANTxID My_CANTxID;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  initializes Usart1
  * @param  vu32 UsartTxId
  * @retval None
  */
void delay1ms( void )
{
	u32  t = 10000;
	while ( --t );
}

/**
  * @brief  initializes Usart1
  * @param  vu32 UsartTxId
  * @retval None
  */
extern CanTxMsg My_CanTxMsg;
extern My_TanCeQi TanCeQi[];
extern FlagStatus Flag_100ms;
u8 CanTxCnt=0;
// u8 CanTxCnt_ChaXun=0;
extern u8 TongXun_cnt[];
/**
  * @brief �������õ�̽������������ѯ����
  * @param  ̽��������
  * @retval
  */
void CAN_Com(void)
{
	CanTxCnt++;
	TongXun_cnt[CanTxCnt]++;
	if(CanTxCnt<=BaoChun_shezhizhi[0])
	{
		My_CanTxMsg.StdId=0x400+TanCeQi[CanTxCnt].Dizhi;
		My_CanTxMsg.Data[0]=0x01;
		CAN_Transmit(CAN1,&My_CanTxMsg);
		CAN_Transmit(CAN2,&My_CanTxMsg);
	}
	if(CanTxCnt>BaoChun_shezhizhi[0]) CanTxCnt=0;	
}

/**
  * @brief  initializes Usart1��
  * @param  vu32 UsartTxId
  * @retval None
  */
void CAN_AdjustTime(ttime *time)
{
	CanTxMsg TxMessage_DuiShi;
	TxMessage_DuiShi.DLC=8;
	TxMessage_DuiShi.IDE=CAN_ID_EXT;
	TxMessage_DuiShi.RTR=CAN_RTR_DATA;
	TxMessage_DuiShi.ExtId=0x0000ffff;
	TxMessage_DuiShi.Data[0]=time->yearl;
	TxMessage_DuiShi.Data[1]=time->month;
	TxMessage_DuiShi.Data[2]=time->day;
	TxMessage_DuiShi.Data[3]=time->hour;
	TxMessage_DuiShi.Data[4]=time->minute;
	TxMessage_DuiShi.Data[5]=time->second;
	CAN_Transmit(CAN1,&TxMessage_DuiShi);
	delay1ms();
}
/**
  * @brief  initializes Usart1
  * @param  vu32 UsartTxId
  * @retval None
  */
void RecoveryComErrorCount(void)
{

}
/**
  * @brief  initializes Usart1
  * @param  vu32 UsartTxId
  * @retval None
  */

void SaveComErrorCount(void)
{
	
}
