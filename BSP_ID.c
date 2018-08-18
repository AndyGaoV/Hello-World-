/**
  ******************************************************************************
  * @file    BSP_ID.c
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
#include "BSP_ID.h"
#include "DisplayHandle.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Configures Timers1 and Timers2.
  * @param  None
  * @retval None
  */
void BSP_DeviceIDInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
	//拨码开关
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0;//IN5,IN6,sw1-4
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//输入和输出接口
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//IN1-4
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;//IN7-8
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//WDI
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;//OUT1-4
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);


	Out1_H();
	Out2_H();
	Out3_H();
	Out4_H();
}
u8 shuru_new[7]={0};
u8 shuru_old[7]={0};
u8 shuru_queren[7]={0};
void DuKaiGuanLiangShuRu(void)
{
	u8 i=0;
	if (IN1==0)
	{
		shuru_new[0]=1;				   //按下
	}
	else
	{
		shuru_new[0]=0;				  //未按
	}
	if (IN2==0)
	{
		shuru_new[1]=1;
	}
	else
	{
		shuru_new[1]=0;
	}
	if (IN3==0)
	{
		shuru_new[2]=1;
	}
	else
	{
		shuru_new[2]=0;
	}
	if (IN4==0)
	{
		shuru_new[3]=1;
	}
	else
	{
		shuru_new[3]=0;
	}
	if (IN5==0)
	{
		shuru_new[4]=1;
	}
	else
	{
		shuru_new[4]=0;
	}
	if (IN6==0)
	{
		shuru_new[5]=1;
	}
	else
	{
		shuru_new[5]=0;
	}
	if (IN7==0)
	{
		shuru_new[6]=1;
	}
	else
	{
		shuru_new[6]=0;
	}
	for (i=0;i<7;i++)
	{
		if (shuru_old[i]&(~shuru_new[i]))
		{
			shuru_queren[i]=1;
		}
		shuru_old[i]=shuru_new[i];
	}

}
/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
u8 ScanLocalAddress(void) //扫描本机地址
{
	u8 addr3=0,addr2=0,addr1=0,addr0=0;
	u8 DeviceID;

	addr3=!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0);//ad3
	addr2=!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1);//ad2
	addr1=!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2);//ad1
	addr0=!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3);//ad0
	DeviceID=((addr3<<3)|(addr2<<2)|(addr1<<1)|addr0);
	return DeviceID;
}
extern u8 JDQ_ZhuangTai[6];
extern u8 DengZhu_KZ;
extern u8 ShengKZ;
extern u8 ZhiShiDeng_KZ;
extern vu16 T_500ms_Cnt;
/**
  * @brief 判断传感器的新老报警,控制继电器输出
  * @param  传感器的地址
  * @retval
  */
extern My_Picture LED_ZhuangTai[];
void KongZhi_JDQ(void)
{
	u8 i;
	if (shuru_queren[6]==1)
	{
		shuru_queren[6]=0;
		for (i=0;i<6;i++)
		{
			if (JDQ_ZhuangTai[i]==1)
			{
				JDQ_ZhuangTai[i]=2;
			}
		}
	}
	else
	{
		if (JDQ_ZhuangTai[0]==1||
		        JDQ_ZhuangTai[1]==1||
		        JDQ_ZhuangTai[2]==1||
		        JDQ_ZhuangTai[3]==1||
		        JDQ_ZhuangTai[4]==1||
		        JDQ_ZhuangTai[5]==1)
		{
			Out1_L();
			// Out3_L();
			{
				if (T_500ms_Cnt==500)
				{
					DengZhu_KZ=SET;
					ZhiShiDeng_KZ=SET;
					if ((LED_ZhuangTai[0].New_BaoJing==1)
					        ||(LED_ZhuangTai[1].New_BaoJing==1)
					        ||(LED_ZhuangTai[2].New_BaoJing==1)
					        ||(LED_ZhuangTai[3].New_BaoJing==1)
					        ||(LED_ZhuangTai[4].New_BaoJing==1)
					        ||(LED_ZhuangTai[5].New_BaoJing==1)
					   ) //报警
					   {
						   ShengKZ=SET;
					   }
					else
					{
						ShengKZ=SET;
					}
				}
				if (T_500ms_Cnt>=1000)
				{
					T_500ms_Cnt=RESET;
					DengZhu_KZ=RESET;
					ZhiShiDeng_KZ=RESET;
					if ((LED_ZhuangTai[0].New_BaoJing==1)
					        ||(LED_ZhuangTai[1].New_BaoJing==1)
					        ||(LED_ZhuangTai[2].New_BaoJing==1)
					        ||(LED_ZhuangTai[3].New_BaoJing==1)
					        ||(LED_ZhuangTai[4].New_BaoJing==1)
					        ||(LED_ZhuangTai[5].New_BaoJing==1)
					   ) //报警
					   {
						   ShengKZ=SET;
					   }
					else
					{
						ShengKZ=RESET;
					}
				}
			}
			
		}
		else if (JDQ_ZhuangTai[0]==2||
		        JDQ_ZhuangTai[1]==2||
		        JDQ_ZhuangTai[2]==2||
		        JDQ_ZhuangTai[3]==2||
		        JDQ_ZhuangTai[4]==2||
		        JDQ_ZhuangTai[5]==2)
		{
			T_500ms_Cnt=RESET;
			Out1_L();
			Out3_H();
			DengZhu_KZ=SET;
			ZhiShiDeng_KZ=SET;
			ShengKZ=RESET;
		}
		else if (JDQ_ZhuangTai[0]==0||
		        JDQ_ZhuangTai[1]==0||
		        JDQ_ZhuangTai[2]==0||
		        JDQ_ZhuangTai[3]==0||
		        JDQ_ZhuangTai[4]==0||
		        JDQ_ZhuangTai[5]==0)
		{
			T_500ms_Cnt=RESET;
			Out1_H();			
			Out3_H();
			DengZhu_KZ=RESET;
			ZhiShiDeng_KZ=RESET;
			ShengKZ=RESET;
		}
	}

	if (DengZhu_KZ==SET)
	{
		Out2_L();
		// Out3_L();
	}
	else
	{
		Out2_H();
		// Out3_H();
	}
	if (ShengKZ==SET)
	{
		Out3_L();
		// Out3_L();
	}
	else
	{
		Out3_H();
		// Out3_H();
	}
	if (ZhiShiDeng_KZ==SET)
	{
		Out4_L();
	}
	else
	{
		Out4_H();
	}
}
