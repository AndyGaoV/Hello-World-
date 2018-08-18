/**
  ******************************************************************************
  * @file    CAN_Handle.c
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
#include "CAN_Handle.h"
#include "BSP_RTC.h"
#include "BSP_ID.h"
#include "BSP_CAN.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
// Usart波特率设置：

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
  * @brief 根据设置的探测器个数，轮询发送
  * @param  探测器个数
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
  * @brief  initializes Usart1报
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
