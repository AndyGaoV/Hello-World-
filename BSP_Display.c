/**
  ******************************************************************************
  * @file    BSP_Display.c
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
#include "BSP_Display.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 Command[35]={0};
//u8 Command[8]={0x97,0x00,0x07,0x31,0x32,0x34,0x2E,0x35};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief 显示时间
  * @param  文本区域编号 文本数据首地址 文本数据个数
  * @retval
  */
/*void DiplayMyType(u16 WordAreaNum,My_Type *ty)
{
	//从外部存储器读参数
	DisplayTime(WordAreaNum,ty->time);
	DisplayHanZi(WordAreaNum+1,ty->State);
}  */
/**
  * @brief 调节屏幕亮度
  * @param  亮度占空比 BrightPwm:1~100
  * @retval
  */
void DisplayTouchTypeSet(void)
{
	Command[0]=0xe0;//参数配置
	Command[1]=0x03;//触控返回值配置
	Command[2]=0x78;//0x78：抬起时返回预设键值 0X79：按下或者移动时返回预设键值
	DisplaySendCommand(3);
}
/**
  * @brief 设置触控返回类型
  * @param
  * @retval
  */
void DisplaySetTouch(void)
{
	Command[0]=0xe0;
	Command[1]=0x03;
	// Command[2]=0x7a;//按下和抬起均返回键码
	Command[2]=0x78;//抬起返回键码
	DisplaySendCommand(3);
}
/**
  * @brief 调节屏幕亮度
  * @param  亮度占空比 BrightPwm:1~100
  * @retval
  */
void DisplayAdjustBright(u8 BrightPwm)
{
	Command[0]=0x5f;//指令
	Command[1]=BrightPwm;
	DisplaySendCommand(2);
}

/**
  * @brief 背光自动控制
  * @param  亮时亮度 暗时亮度 时间
  * @retval
  */
void BeiGuangZiDongKongZhi(u8 PWMON,u8 PWMOFF,u8 PWMTime)
{
	Command[0]=0x5e;//指令
	Command[1]=0x55;//指令
	Command[2]=0xaa;//指令
	Command[3]=0x5a;//指令
	Command[4]=0xa5;//指令
	Command[5]=PWMON;//指令
	Command[6]=PWMOFF;//指令
	Command[7]=PWMTime;//指令
	DisplaySendCommand(8);
}

/**
  * @brief 显示光标在指定位置
  * @param  光标状态（1：开启/0：关闭） 光标显示X坐标 光标显示y坐标
  * @retval
  */
void DisplayCursorAtDesignatedSpot(u8 CursorState,u16 X,u16 Y)
{
	Command[0]=0x44;//指令
	Command[1]=CursorState;
	/* if (CursorState==CursorOn)
	{
		Command[2]=(u8)(X>>8);
		Command[3]=(u8)X;
		Command[4]=(u8)(Y>>8);
		Command[5]=(u8)Y;
		Command[6]=0x1F;//光标宽度 0x01~0x1f
		Command[7]=0x01;//光标高度 0x01~0x1f
		DisplaySendCommand(8);
	}
	else
	{
		DisplaySendCommand(2);
	} */

	Command[2]=(u8)(X>>8);
	Command[3]=(u8)X;
	Command[4]=(u8)(Y>>8);
	Command[5]=(u8)Y;
	Command[6]=0x1F;//光标宽度 0x01~0x1f
	Command[7]=0x05;//光标高度 0x01~0x1f
	DisplaySendCommand(8);


}
/**
  * @brief 清空指定文本配置区域
  * @param  文本区域编号
  * @retval
  */
void DisplayClearWordArea(u16 WordAreaNum)
{
	Command[0]=0x97;//指令
	Command[1]=(u8)(WordAreaNum>>8);
	Command[2]=(u8)WordAreaNum;
	Command[3]=0x20;
	Command[4]=0x20;
	Command[5]=0x20;
	Command[6]=0x20;
	Command[7]=0x20;
	DisplaySendCommand(8);
}
/**
  * @brief 显示文字在指定文本配置区域
  * @param  文本区域编号 文本数据个数
  * @retval
  */
extern u8 Count_TongXunGuZhang;
void DisplayWord(u16 WordAreaNum,u16 num,u16 num2)
{
	Command[0]=0x97;//指令
	Command[1]=(u8)(WordAreaNum>>8);
	Command[2]=(u8)WordAreaNum;
	/*	if (Count_TongXunGuZhang>=TongXunGuZhang_ShiJian)
		{
			Command[3]='?';
			Command[4]='?';
			Command[5]='?';
			Command[6]='?';
			DisplaySendCommand(7);
		}
		else
		{ */
	if ((num<10))
	{
		Command[3]=0x20;
		Command[4]=num+0x30;				
		DisplaySendCommand(5);
	}
	else if (num<100)
	{
		Command[3]=num/10+0X30;
		Command[4]=num%10+0X30;
		DisplaySendCommand(5);
	}
	else if (num==100)
	{
		Command[3]=(num/100)+0X30;
		Command[4]=(num%100/10)+0X30;
		Command[5]=(num%100%10)+0X30;
		DisplaySendCommand(6);
	}
	/*else if (num<1000)
	{
		Command[5]=0x20;
		Command[6]=num/100+0X30;
		Command[3]=(num%100)/10+0X30;
		Command[4]=num%10+0X30;
		DisplaySendCommand(7);
	}
	else if (num<10000)
	{
		Command[5]=num/1000+0x30;
		Command[6]=(num%1000)/100+0X30;
		Command[3]=(num%1000)%100/10+0X30;
		Command[4]=num%10+0X30;
		DisplaySendCommand(7);
	} */
	else//大于4位数显示“错误”
	{
		Command[3]='E';
		Command[4]='R';
		Command[5]='R';
		Command[6]='.';
		DisplaySendCommand(7);
	}
	//	}
}



/**
  * @brief 显示输入文字在指定文本输入区域
  * @param  文本区域编号 文本数据首地址 文本数据个数
  * @retval
  */
void DisplayBaoJingWord(u16 WordAreaNum,u8 *Word)
{
	u8 temp=0;
	Command[0]=0x97;//指令
	Command[1]=(u8)(WordAreaNum>>8);
	Command[2]=(u8)WordAreaNum;
	while ((Word[temp]!='&')&&(temp<32))
	{
		Command[temp+3]=Word[temp];
		temp++;
	}
	DisplaySendCommand(temp+3);
}
/**
  * @brief 清屏
  * @param
  * @retval
  */
void DisplayClearAll(void)
{
	Command[0]=0x52;//指令
	DisplaySendCommand(1);
}
/**
  * @brief 显示图标在指定位置
  * @param  图标编号 图标显示X坐标 图标显示y坐标
  * @retval
  */
void DisplayPictureAtDesignatedSpot(u16 PictureNum,u16 X,u16 Y)
{
//  Command[0]=0x9d;//指定位置显示图片
//	Command[1]=(u8)(PictureNum>>8);
//	Command[2]=(u8)PictureNum;
//	Command[3]=(u8)(X>>8);
//	Command[4]=(u8)X;
//	Command[5]=(u8)(Y>>8);
//	Command[6]=(u8)Y;
	Command[0]=0x99;//指定位置显示图标
	Command[1]=(u8)(X>>8);
	Command[2]=(u8)X;
	Command[3]=(u8)(Y>>8);
	Command[4]=(u8)Y;
	Command[5]=(u8)(PictureNum>>8);
	Command[6]=(u8)PictureNum;
	DisplaySendCommand(7);
}
/**
  * @brief 显示主界面
  * @param  图片编号 在ZTM终端助手当中
  * @retval
  */

void DisplayFirstPicture(u16 PictureNum)
{
	Command[0]=0x70;//指令
	Command[1]=(u8)(PictureNum>>8);
	Command[2]=(u8)PictureNum;
	DisplaySendCommand(3);
}
/**
  * @brief 延时
  * @param
  * @retval
  */
void delay10us1( void )
{
	u16  t = 1000;
	while ( --t );
}
/**
  * @brief 显示时间
  * @param  文本区域编号 文本数据首地址 文本数据个数
  * @retval
  */
void DisplaySystemTime(u16 WordAreaNum,ttime Dis_time)
{
	Command[0]=0x97;
	Command[1]=(u8)(WordAreaNum>>8);
	Command[2]=(u8)WordAreaNum;
	Command[3]=0x32;
	Command[4]=0x30;
	Command[5]=Dis_time.yearl/16+0x30;
	Command[6]=Dis_time.yearl%16+0x30;
	Command[7]=0x2d;//"-"
	Command[8]=Dis_time.month/16+0x30;
	Command[9]=Dis_time.month%16+0x30;
	Command[10]=0x2d;//"-"
	Command[11]=Dis_time.day/16+0x30;
	Command[12]=Dis_time.day%16+0x30;
	Command[13]=0x20;//" "
	Command[14]=Dis_time.hour/16+0x30;
	Command[15]=Dis_time.hour%16+0x30;
	Command[16]=0x3a;//":"
	Command[17]=Dis_time.minute/16+0x30;
	Command[18]=Dis_time.minute%16+0x30;
	Command[19]=0x3a;//":"
	Command[20]=Dis_time.second/16+0x30;
	Command[21]=Dis_time.second%16+0x30;
	DisplaySendCommand(22);
	/*Command[0]=0x97;
	Command[1]=(u8)((WordAreaNum+1)>>8);
	Command[2]=(u8)(WordAreaNum+1);
	Command[3]=Dis_time.hour/16+0x30;
	Command[4]=Dis_time.hour%16+0x30;
	Command[5]=0x3a;//":"
	Command[6]=Dis_time.minute/16+0x30;
	Command[7]=Dis_time.minute%16+0x30;
	Command[8]=0x3a;//":"
	Command[9]=Dis_time.second/16+0x30;
	Command[10]=Dis_time.second%16+0x30;
	DisplaySendCommand(11);*/
}
/**
  * @brief 显示时间
  * @param  文本区域编号 文本数据首地址 文本数据个数
  * @retval
  */
void DisplayTime(u16 WordAreaNum,ttime Dis_time)
{
	Command[0]=0x97;
	Command[1]=(u8)(WordAreaNum>>8);
	Command[2]=(u8)WordAreaNum;
	Command[3]=0x32;
	Command[4]=0x30;
	Command[5]=Dis_time.yearl/16+0x30;
	Command[6]=Dis_time.yearl%16+0x30;
	Command[7]=0x2d;//"-"
	Command[8]=Dis_time.month/16+0x30;
	Command[9]=Dis_time.month%16+0x30;
	Command[10]=0x2d;//"-"
	Command[11]=Dis_time.day/16+0x30;
	Command[12]=Dis_time.day%16+0x30;
	Command[13]=0x20;//" "
	Command[14]=Dis_time.hour/16+0x30;
	Command[15]=Dis_time.hour%16+0x30;
	Command[16]=0x3a;//":"
	Command[17]=Dis_time.minute/16+0x30;
	Command[18]=Dis_time.minute%16+0x30;
	Command[19]=0x3a;//":"
	Command[20]=Dis_time.second/16+0x30;
	Command[21]=Dis_time.second%16+0x30;
	DisplaySendCommand(22);
}

extern FlagStatus FLag_ZhongYing;


/**
  * @brief 232发送命令给串口屏
  * @param  图片编号 在ZTM终端助手当中
  * @retval
  */
void DisplaySendCommand(u8 SendCount)
{
	u8 Count;
	//发送帧头 0xaa
	USART_SendData(USART2,0xaa);
	while (USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	//发送命令主体
	for (Count=0;Count<SendCount;Count++)
	{
		USART_SendData(USART2,Command[Count]);
		while (USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	}
	//发送帧尾 cc 33 c3 3c
	USART_SendData(USART2,0xcc);
	while (USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	USART_SendData(USART2,0x33);
	while (USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	USART_SendData(USART2,0xc3);
	while (USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	USART_SendData(USART2,0x3c);
	while (USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	delay10us1();
}
