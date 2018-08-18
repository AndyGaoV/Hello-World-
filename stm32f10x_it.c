/**
  ******************************************************************************
  * @file    ADC/ADC1_DMA/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "BSP_RTC.h"
#include "BSP_ID.h"
#include "main.h"
#include "stdlib.h"
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_ADC1_DMA
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
u8 SysTickFlag_1mS = 0;
u8 SysTickFlag_1mS_Disp = 0;
u8 SysTickFlag_1mS_Delay = 0;
void SysTick_Handler(void)
{
	SysTickFlag_1mS = 1;
	SysTickFlag_1mS_Disp = 1;
	SysTickFlag_1mS_Delay = 1;
}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

u8 Count_100ms=0;
u16 Count_1s=0;
FlagStatus Flag_100ms=RESET;
u16 Count_alarm=0;
u8 Int_cnt=0;
unsigned char Cnt_Tim;



extern u8 LocalAddress;
/*****************呼叫界面变量************************/
extern FlagStatus AlarmDispaly;
/*****************延伸报警界面变量************************/
extern u8 AlarmCnt;//总报警个数
extern My_Alarm BaoJing[];

/**********************************************************/
extern FlagStatus Flag_XiaoYin;
FlagStatus Dao1Miao=RESET;
extern FlagStatus FLag_ZhongYing;

u8 Count_DaiJi=0;

u8 Count_TongXunGuZhang=0;
extern ttime RTC_SystemTime;
extern u8 Duishi[];


u8 Count_DuiShi_Zhuji=0;
FlagStatus Flag_DuiShi=RESET;

u8 Count_TIM2=0;
u8 Duishi[6]={0};

void TIM2_IRQHandler(void)
{
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
#ifndef DEBUG
	IWDG_ReloadCounter();
#endif
	Count_100ms++;
	if (Count_100ms==200)//开机延时2s启动
	{
		Flag_100ms=SET;
		Count_100ms=201;
	}
	Count_1s++;
	if (Count_1s==100)
	{
		Count_1s=0;
		Dao1Miao=SET;
		// Count_DaiJi++;
		//	Count_DuiShi_Zhuji++;//30s后执行对时

//		Count_TongXunGuZhang++; //暂时不增加通讯故障报警功能 通讯故障计数器自加

	}
	/*if (Count_DuiShi_Zhuji==30)
	{
		RTC_SystemTime.yearl=((Duishi[0]/10)<<4)+((Duishi[0]%10));
		RTC_SystemTime.month=((Duishi[1]/10)<<4)+((Duishi[1]%10));
		RTC_SystemTime.day=((Duishi[2]/10)<<4)+((Duishi[2]%10));
		RTC_SystemTime.hour=((Duishi[3]/10)<<4)+((Duishi[3]%10));
		RTC_SystemTime.minute=((Duishi[4]/10)<<4)+((Duishi[4]%10));
		RTC_SystemTime.second=((Duishi[5]/10)<<4)+((Duishi[5]%10));
		Flag_DuiShi=SET;
		Count_DuiShi_Zhuji=0;
	}*/

	/*	Count_alarm++;
		if (Count_alarm==50)//500ms
		{

			for (Cnt_Tim=0;Cnt_Tim<10;Cnt_Tim++)
			{
				if (BaoJing[Cnt_Tim].AlarmState==NewAlarm)
				{
					BEEP_ON();
				}
			}

		}
		else if (Count_alarm==100)//1s
		{
			Count_alarm=0;
			BEEP_OFF();
		}  */
}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

CANTxID My_RxID;
extern u8 Value;
extern FlagStatus Flag_QuXiao;
u8 YingDa_cnt=0;
extern ttime RTC_SystemTime;
u8 Array5[24];
extern My_TanCeQi TanCeQi[];
extern My_Picture LED_ZhuangTai[];
extern u8 LiangDu;
u8 TongXun_cnt[30];
CanRxMsg RxMessage;
CanTxMsg TxMessage;

u8 zaojia_count[7]={0,0,0,0,0,0,0};
u8 zaojia_max[7]={0,0,0,0,0,0,0};
u8 ZhenShiZhi[7]={0,0,0,0,0,0,0};
u8 ShouDaoMax[7]={0,0,0,0,0,0,0};
u8 nongdu_old=0;
u8 flag_shangsheng[7]={0,0,0,0,0,0,0};
u8 flag_shangshengyanximoshi[7]={0,0,0,0,0,0,0};
u8 flag_xiaJiangYanXimoShi[7]={0,0,0,0,0,0,0};
u8 flag_xiaJiang[7]={0,0,0,0,0,0,0};																	
extern unsigned char Count_YanXi[];
extern u8 YinCan_GN;
//上升阶段 大于12 进入演戏模式 选取12-20中随机值 和20-28中随机值两个中间值，以间隔1S显示，最终显示随机最大值
//上升阶段不用实际值
//上升阶段的标志是，收到的最新的实际值比之前收到的实际最大值还要大,代表进入上升阶段，收到的实际最大值在实际值小于12的时候清零

//下降阶段，实际值小于随机最大值的时候显示实际值，实际值大于随机最大值的时候显示最大值
//下降阶段的标志是，最新收到的实际值比之前收到的实际值最大值小于3
void CAN2_RX0_IRQHandler(void)
{
	u8 temp;
	CAN_ClearFlag(CAN2,CAN_FLAG_FMP0);
	CAN_ClearITPendingBit(CAN2,CAN_IT_FMP0);
	CAN_Receive(CAN2,CAN_FIFO0,&RxMessage);
	My_RxID.IDValue=RxMessage.ExtId;

	if (RxMessage.StdId==0x505)		// 清空历史报警
	{
		YinCan_GN=4;
	}
	if (((RxMessage.StdId&0x300)==0x300)&&(RxMessage.DLC==8)&&(RxMessage.Data[5]>=0))
	{
		temp=RxMessage.StdId-0x300;

		if (ScanLocalAddress()==0x08)
		{
			//if (ZhenShiZhi[temp]>RxMessage.Data[5])//真实值就是上一次收到的值 比 这一次收到的值大3，则代表下降
			if ((ZhenShiZhi[temp]<zaojia_max[temp])&&(flag_shangshengyanximoshi[temp]==1)&&(ZhenShiZhi[temp]<ShouDaoMax[temp]))//真实值就是上一次收到的值 比 这一次收到的值大3，则代表下降
			{
				flag_xiaJiang[temp]=1;
				flag_shangsheng[temp]=0;
				Count_YanXi[temp]=0;
				flag_shangshengyanximoshi[temp]=0;
			}										    

			if((RxMessage.Data[5]>ZhenShiZhi[temp])&&(flag_shangsheng[temp]==0))
			{
				ShouDaoMax[temp]=0;
					flag_shangsheng[temp]=1;
				flag_xiaJiang[temp]=0;
			}   
			ZhenShiZhi[temp]=RxMessage.Data[5];
			// if ((flag_xiaJiang[temp]==1)&&(ZhenShiZhi[temp]>zaojia_max[temp]))//如果下降并且这次收到的值大于造假最大值，则进入下降演戏模式
			// {
				// flag_xiaJiangYanXimoShi[temp]=1;
			// }
			// else if ((flag_xiaJiang[temp]==1)&&(ZhenShiZhi[temp]<=zaojia_max[temp]))
			// {
				// flag_xiaJiangYanXimoShi[temp]=0;
			// }
			if ((ShouDaoMax[temp]<ZhenShiZhi[temp]))//如果收到的最大值小于当前收到的值，则将当前值赋值给最大值，则代表上升
			{
				ShouDaoMax[temp]=ZhenShiZhi[temp];
			
			}
			if ((flag_shangsheng[temp]==1)&&(ZhenShiZhi[temp]>15))//如果在上升阶段并且当前值大于12，则进入上升演戏模式
			{
				flag_shangshengyanximoshi[temp]=1;
			}
		}
		else
		{
			TanCeQi[temp].NongDu=RxMessage.Data[5];
		}

		switch (temp)
		{
		case 1 :
			LED_ZhuangTai[0].GuZhang=0;
			break;
		case 2 :
			LED_ZhuangTai[1].GuZhang=0;
			break;
		case 3 :
			LED_ZhuangTai[2].GuZhang=0;
			break;
		case 4 :
			LED_ZhuangTai[3].GuZhang=0;
			break;
		case 5 :
			LED_ZhuangTai[4].GuZhang=0;
			break;
		case 6 :
			LED_ZhuangTai[5].GuZhang=0;
			break;
		case 7 :
			// RTC_SystemTime.yearl=((RxMessage.Data[0]/10)<<4)+((RxMessage.Data[0]%10));
			// RTC_SystemTime.month=((RxMessage.Data[1]/10)<<4)+((RxMessage.Data[1]%10));
			// RTC_SystemTime.day=((RxMessage.Data[2]/10)<<4)+((RxMessage.Data[2]%10));
			// RTC_SystemTime.hour=((RxMessage.Data[3]/10)<<4)+((RxMessage.Data[3]%10));
			// RTC_SystemTime.minute=((RxMessage.Data[4]/10)<<4)+((RxMessage.Data[4]%10));
			// RTC_SystemTime.second=((RxMessage.Data[5]/10)<<4)+((RxMessage.Data[5]%10));
			RTC_SystemTime.yearl=RxMessage.Data[0];
			RTC_SystemTime.month=RxMessage.Data[1];
			RTC_SystemTime.day=RxMessage.Data[2];
			RTC_SystemTime.hour=RxMessage.Data[3];
			RTC_SystemTime.minute=RxMessage.Data[4];
			RTC_SystemTime.second=RxMessage.Data[5];
			write_time();
			break;
		default:
			break;
		}
	}
	else if((RxMessage.StdId==0x505)&&(RxMessage.Data[5]==0x55))
	 {
		 YinCan_GN=4;
	 }
	//CAN_ClearFlag(CAN2,CAN_FLAG_FMP0);
	//CAN_Receive(CAN2,CAN_FIFO0,&RXMessage);
}
void CAN1_RX0_IRQHandler(void)
{
	u8 temp;
	CAN_ClearFlag(CAN1,CAN_FLAG_FMP0);
	CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);
	CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
	My_RxID.IDValue=RxMessage.ExtId;
	if (((RxMessage.StdId&0x300)==0x300)&&(RxMessage.DLC==8)&&(RxMessage.Data[5]>=0))
	{
		temp=RxMessage.StdId-0x300;

		if (ScanLocalAddress()==0x08)
		{
			//if (ZhenShiZhi[temp]>RxMessage.Data[5])//真实值就是上一次收到的值 比 这一次收到的值大3，则代表下降
			if ((ZhenShiZhi[temp]<zaojia_max[temp])&&(flag_shangshengyanximoshi[temp]==1)&&(ZhenShiZhi[temp]<ShouDaoMax[temp]))//真实值就是上一次收到的值 比 这一次收到的值大3，则代表下降
			{
				flag_xiaJiang[temp]=1;
				flag_shangsheng[temp]=0;
				Count_YanXi[temp]=0;
				flag_shangshengyanximoshi[temp]=0;
			}										    

			if((RxMessage.Data[5]>ZhenShiZhi[temp])&&(flag_shangsheng[temp]==0))
			{
				ShouDaoMax[temp]=0;
					flag_shangsheng[temp]=1;
				flag_xiaJiang[temp]=0;
			}   
			ZhenShiZhi[temp]=RxMessage.Data[5];
			// if ((flag_xiaJiang[temp]==1)&&(ZhenShiZhi[temp]>zaojia_max[temp]))//如果下降并且这次收到的值大于造假最大值，则进入下降演戏模式
			// {
				// flag_xiaJiangYanXimoShi[temp]=1;
			// }
			// else if ((flag_xiaJiang[temp]==1)&&(ZhenShiZhi[temp]<=zaojia_max[temp]))
			// {
				// flag_xiaJiangYanXimoShi[temp]=0;
			// }
			if ((ShouDaoMax[temp]<ZhenShiZhi[temp]))//如果收到的最大值小于当前收到的值，则将当前值赋值给最大值，则代表上升
			{
				ShouDaoMax[temp]=ZhenShiZhi[temp];
			
			}
			if ((flag_shangsheng[temp]==1)&&(ZhenShiZhi[temp]>12))//如果在上升阶段并且当前值大于12，则进入上升演戏模式
			{
				flag_shangshengyanximoshi[temp]=1;
			}
		}
		else
		{
			TanCeQi[temp].NongDu=RxMessage.Data[5];
		}

		switch (temp)
		{
		case 1 :
			LED_ZhuangTai[0].GuZhang=0;
			break;
		case 2 :
			LED_ZhuangTai[1].GuZhang=0;
			break;
		case 3 :
			LED_ZhuangTai[2].GuZhang=0;
			break;
		case 4 :
			LED_ZhuangTai[3].GuZhang=0;
			break;
		case 5 :
			LED_ZhuangTai[4].GuZhang=0;
			break;
		case 6 :
			LED_ZhuangTai[5].GuZhang=0;
			break;
		case 7 :
			// RTC_SystemTime.yearl=((RxMessage.Data[0]/10)<<4)+((RxMessage.Data[0]%10));
			// RTC_SystemTime.month=((RxMessage.Data[1]/10)<<4)+((RxMessage.Data[1]%10));
			// RTC_SystemTime.day=((RxMessage.Data[2]/10)<<4)+((RxMessage.Data[2]%10));
			// RTC_SystemTime.hour=((RxMessage.Data[3]/10)<<4)+((RxMessage.Data[3]%10));
			// RTC_SystemTime.minute=((RxMessage.Data[4]/10)<<4)+((RxMessage.Data[4]%10));
			// RTC_SystemTime.second=((RxMessage.Data[5]/10)<<4)+((RxMessage.Data[5]%10));
			RTC_SystemTime.yearl=RxMessage.Data[0];
			RTC_SystemTime.month=RxMessage.Data[1];
			RTC_SystemTime.day=RxMessage.Data[2];
			RTC_SystemTime.hour=RxMessage.Data[3];
			RTC_SystemTime.minute=RxMessage.Data[4];
			RTC_SystemTime.second=RxMessage.Data[5];
			write_time();
			break;
		default:
			break;
 		}
	 }
	 else if((RxMessage.StdId==0x505)&&(RxMessage.Data[5]==0x55))
	 {
		 YinCan_GN=4;
	 }
}


/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
unsigned char Flag_Receive=0;
unsigned char Flag_Receive5=0;
unsigned char ReceiveDate=0;
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		USART_ClearFlag(USART1,USART_FLAG_RXNE);
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		ReceiveDate=USART_ReceiveData(USART1);
		Flag_Receive=1;
	}
}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
	if (USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
	{
		USART_ClearFlag(USART2,USART_FLAG_RXNE);
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		ReceiveDate=USART_ReceiveData(USART2);

		//	USART_SendData(USART2,ReceiveDate);
		//	while (USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);

		Flag_Receive=1;
	}
}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
	if (USART_GetITStatus(USART3,USART_IT_RXNE)==SET)
	{
		USART_ClearFlag(USART3,USART_FLAG_RXNE);
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		ReceiveDate=USART_ReceiveData(USART3);
		Flag_Receive=1;
	}
}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void UART4_IRQHandler(void)
{
	if (USART_GetITStatus(UART4,USART_IT_RXNE)==SET)
	{
		USART_ClearFlag(UART4,USART_FLAG_RXNE);
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
		ReceiveDate=USART_ReceiveData(UART4);
		//Flag_Receive5=1;
	}
}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void UART5_IRQHandler(void)
{
	if (USART_GetITStatus(UART5,USART_IT_RXNE)==SET)
	{
		USART_ClearFlag(UART5,USART_FLAG_RXNE);
		USART_ClearITPendingBit(UART5,USART_IT_RXNE);
		ReceiveDate=USART_ReceiveData(UART5);

		Flag_Receive5=1;
	}
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
