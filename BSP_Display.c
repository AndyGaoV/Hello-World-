/**
  ******************************************************************************
  * @file    BSP_Display.c
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
  * @brief ��ʾʱ��
  * @param  �ı������� �ı������׵�ַ �ı����ݸ���
  * @retval
  */
/*void DiplayMyType(u16 WordAreaNum,My_Type *ty)
{
	//���ⲿ�洢��������
	DisplayTime(WordAreaNum,ty->time);
	DisplayHanZi(WordAreaNum+1,ty->State);
}  */
/**
  * @brief ������Ļ����
  * @param  ����ռ�ձ� BrightPwm:1~100
  * @retval
  */
void DisplayTouchTypeSet(void)
{
	Command[0]=0xe0;//��������
	Command[1]=0x03;//���ط���ֵ����
	Command[2]=0x78;//0x78��̧��ʱ����Ԥ���ֵ 0X79�����»����ƶ�ʱ����Ԥ���ֵ
	DisplaySendCommand(3);
}
/**
  * @brief ���ô��ط�������
  * @param
  * @retval
  */
void DisplaySetTouch(void)
{
	Command[0]=0xe0;
	Command[1]=0x03;
	// Command[2]=0x7a;//���º�̧������ؼ���
	Command[2]=0x78;//̧�𷵻ؼ���
	DisplaySendCommand(3);
}
/**
  * @brief ������Ļ����
  * @param  ����ռ�ձ� BrightPwm:1~100
  * @retval
  */
void DisplayAdjustBright(u8 BrightPwm)
{
	Command[0]=0x5f;//ָ��
	Command[1]=BrightPwm;
	DisplaySendCommand(2);
}

/**
  * @brief �����Զ�����
  * @param  ��ʱ���� ��ʱ���� ʱ��
  * @retval
  */
void BeiGuangZiDongKongZhi(u8 PWMON,u8 PWMOFF,u8 PWMTime)
{
	Command[0]=0x5e;//ָ��
	Command[1]=0x55;//ָ��
	Command[2]=0xaa;//ָ��
	Command[3]=0x5a;//ָ��
	Command[4]=0xa5;//ָ��
	Command[5]=PWMON;//ָ��
	Command[6]=PWMOFF;//ָ��
	Command[7]=PWMTime;//ָ��
	DisplaySendCommand(8);
}

/**
  * @brief ��ʾ�����ָ��λ��
  * @param  ���״̬��1������/0���رգ� �����ʾX���� �����ʾy����
  * @retval
  */
void DisplayCursorAtDesignatedSpot(u8 CursorState,u16 X,u16 Y)
{
	Command[0]=0x44;//ָ��
	Command[1]=CursorState;
	/* if (CursorState==CursorOn)
	{
		Command[2]=(u8)(X>>8);
		Command[3]=(u8)X;
		Command[4]=(u8)(Y>>8);
		Command[5]=(u8)Y;
		Command[6]=0x1F;//����� 0x01~0x1f
		Command[7]=0x01;//���߶� 0x01~0x1f
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
	Command[6]=0x1F;//����� 0x01~0x1f
	Command[7]=0x05;//���߶� 0x01~0x1f
	DisplaySendCommand(8);


}
/**
  * @brief ���ָ���ı���������
  * @param  �ı�������
  * @retval
  */
void DisplayClearWordArea(u16 WordAreaNum)
{
	Command[0]=0x97;//ָ��
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
  * @brief ��ʾ������ָ���ı���������
  * @param  �ı������� �ı����ݸ���
  * @retval
  */
extern u8 Count_TongXunGuZhang;
void DisplayWord(u16 WordAreaNum,u16 num,u16 num2)
{
	Command[0]=0x97;//ָ��
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
	else//����4λ����ʾ������
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
  * @brief ��ʾ����������ָ���ı���������
  * @param  �ı������� �ı������׵�ַ �ı����ݸ���
  * @retval
  */
void DisplayBaoJingWord(u16 WordAreaNum,u8 *Word)
{
	u8 temp=0;
	Command[0]=0x97;//ָ��
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
  * @brief ����
  * @param
  * @retval
  */
void DisplayClearAll(void)
{
	Command[0]=0x52;//ָ��
	DisplaySendCommand(1);
}
/**
  * @brief ��ʾͼ����ָ��λ��
  * @param  ͼ���� ͼ����ʾX���� ͼ����ʾy����
  * @retval
  */
void DisplayPictureAtDesignatedSpot(u16 PictureNum,u16 X,u16 Y)
{
//  Command[0]=0x9d;//ָ��λ����ʾͼƬ
//	Command[1]=(u8)(PictureNum>>8);
//	Command[2]=(u8)PictureNum;
//	Command[3]=(u8)(X>>8);
//	Command[4]=(u8)X;
//	Command[5]=(u8)(Y>>8);
//	Command[6]=(u8)Y;
	Command[0]=0x99;//ָ��λ����ʾͼ��
	Command[1]=(u8)(X>>8);
	Command[2]=(u8)X;
	Command[3]=(u8)(Y>>8);
	Command[4]=(u8)Y;
	Command[5]=(u8)(PictureNum>>8);
	Command[6]=(u8)PictureNum;
	DisplaySendCommand(7);
}
/**
  * @brief ��ʾ������
  * @param  ͼƬ��� ��ZTM�ն����ֵ���
  * @retval
  */

void DisplayFirstPicture(u16 PictureNum)
{
	Command[0]=0x70;//ָ��
	Command[1]=(u8)(PictureNum>>8);
	Command[2]=(u8)PictureNum;
	DisplaySendCommand(3);
}
/**
  * @brief ��ʱ
  * @param
  * @retval
  */
void delay10us1( void )
{
	u16  t = 1000;
	while ( --t );
}
/**
  * @brief ��ʾʱ��
  * @param  �ı������� �ı������׵�ַ �ı����ݸ���
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
  * @brief ��ʾʱ��
  * @param  �ı������� �ı������׵�ַ �ı����ݸ���
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
  * @brief 232���������������
  * @param  ͼƬ��� ��ZTM�ն����ֵ���
  * @retval
  */
void DisplaySendCommand(u8 SendCount)
{
	u8 Count;
	//����֡ͷ 0xaa
	USART_SendData(USART2,0xaa);
	while (USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	//������������
	for (Count=0;Count<SendCount;Count++)
	{
		USART_SendData(USART2,Command[Count]);
		while (USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
	}
	//����֡β cc 33 c3 3c
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
