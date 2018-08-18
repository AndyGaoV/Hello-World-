/**
  ******************************************************************************
  * @file    main.c
  * @author  WangBo
  * @version V1.0.0
  * @date    28-May-2012
  * @brief   Main program body.
  ******************************************************************************
  * @attention*/
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdlib.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

// #define DEBUG            //调试的时候取消屏蔽，不调试的时候屏蔽掉该语句

#define QINGCHU            //需要清除铁电数据时屏蔽，不清除的时候取消屏蔽掉该语句
#define ShuLiang_Max    6    //探测器数量最大值
#define ShuLiang_Min    1    //探测器数量最小值
#define YuBaoJing_Max    25    //预报警最大值
#define YuBaoJing_Min    5 //预报警最小值
#define BaoJing_Max    60    //报警最大值
#define BaoJing_Min    25//报警最小值
#define DiZhi_Max    10   //地址最大值
#define DiZhi_Min    0  //地址最小值
#define Nian_Max    96   //年最大值
#define Nian_Min    16  //年最小值
#define Yue_Max    12   //月最大值
#define Yue_Min    1  //月最小值
#define Ri_Max    31   //日最大值
#define Ri_Min    1  //日最小值
#define Shi_Max    23   //时最大值
#define Shi_Min    1  //时最小值
#define Fen_Max    59   //分最大值
#define Fen_Min    1  //分最小值
#define FangDai_Mode_On  60000   //防呆模式1分钟开启
#define YeShu_Max 143 //存满1000条报警时的总页数
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void IWDG_Config(void)
{
	//1.向IWDG_KR中写入0x5555，解除IWDG_PR和IWDG_RLR写保护
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

	IWDG_SetPrescaler(IWDG_Prescaler_256);//IWDG预分频系数：40KHZ/256
	IWDG_SetReload(300); //300*256/40K=1.92

	//2.向键寄存器IWDG_KR中写入0XAAAA，RELOAD IWDG COUNTER ,喂狗
	IWDG_ReloadCounter();

	//3.在IWDG_KR中写入0XCCCC，使能LSI RC 振荡器，启用独立看门狗
	IWDG_Enable();
}
extern u8 zaojia_max[7];
extern u8 zaojia_count[7];
extern u8 ZhenShiZhi[7];
extern u8 ShouDaoMax[7];
extern u8 flag_shangsheng[7];
extern u8 flag_shangshengyanximoshi[7];
extern u8 flag_xiaJiangYanXimoShi[7];
extern u8 flag_xiaJiang[7];
extern My_TanCeQi TanCeQi[];
unsigned char Count_YanXi[]={0,0,0,0,0,0};
void panduan(unsigned char temp)
{
	if (flag_shangshengyanximoshi[temp]==1)
	{
		// 每隔1S

		Count_YanXi[temp]++;
		if (ScanLocalAddress()==0x01)
		{
			if (Count_YanXi[temp]==1)
			{
				TanCeQi[temp].NongDu=rand()%8+12;
			}
			else if (Count_YanXi[temp]==2)
			{
				TanCeQi[temp].NongDu=rand()%8+20;
			}
			else if (Count_YanXi[temp]==3)
			{
				TanCeQi[temp].NongDu=rand()%8+30;
			}
			else if (Count_YanXi[temp]==4)
			{
				TanCeQi[temp].NongDu=rand()%8+40;
			}
			else
			{
				Count_YanXi[temp]=5;
				TanCeQi[temp].NongDu=zaojia_max[temp];
			}
		}
		else if (ScanLocalAddress()==0x08)
		{
			if (Count_YanXi[temp]==1)
			{
				TanCeQi[temp].NongDu=rand()%5+15;
			}
			else if (Count_YanXi[temp]==2)
			{
				TanCeQi[temp].NongDu=rand()%8+20;
			}
			else
			{
				Count_YanXi[temp]=3;
				TanCeQi[temp].NongDu=zaojia_max[temp];
			}
		}

	}
	// else if (flag_xiaJiangYanXimoShi[temp]==1)
	else if (flag_xiaJiang[temp]==0x01)
	{
		//显示随机的最大值 zaojia_max[temp]

		// TanCeQi[temp].NongDu=zaojia_max[temp];
		TanCeQi[temp].NongDu=ZhenShiZhi[temp];
	}
	else//非演戏模式显示实际值 ZhenShiZhi[temp]
	{
		Count_YanXi[temp]=0;
		flag_shangshengyanximoshi[temp]=0;
		TanCeQi[temp].NongDu=ZhenShiZhi[temp];
	}
}
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

void Hal_Init(void)
{
	RCC_ClocksTypeDef RCC_ClockFreq;
	/*
	获取RCC的信息,调试用
	请参考RCC_ClocksTypeDef结构体的内容,当时钟配置完成后,
	里面变量的值就直接反映了器件各个部分的运行频率
	*/
	RCC_GetClocksFreq(&RCC_ClockFreq);

	/* 这个配置可使外部晶振停振的时候,产生一个NMI中断,不需要用的可屏蔽掉*/
	RCC_ClockSecuritySystemCmd(ENABLE);

	/* Setup SysTick Timer for 1 msec interrupts  */
	if (SysTick_Config(SystemCoreClock / 1000))		// 1ms的滴嗒时钟
	{
		/* Capture error */
		while (1);
	}

	BSP_Usarts_Config();		// 串口初始化配置
	BSP_CAN_Config();			//CAN 初始化
	BSP_Timers_Config();		//定时器初始化
	BSP_RTC_Config();			//外部实时时钟和存储器初始化
	//BSP_MACIDInit();
	BSP_DeviceIDInit();         //器件ID初始化
#ifndef DEBUG								// 用于程序仿真模式（有看门狗，单步调试不正常），在UserConfig.h中定义
	// IWDG_Config();//独立看门狗初始化配置，调试的时候屏蔽掉
#endif

}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

/*************共用******************/
u8 LocalAddress=0;
u8 LocalAddress_old=0;
u8 LiangDu=20;
vu16 T_1ms_Cnt = 0;
vu16 T_100ms_Cnt = 0;
vu16 T_500ms_Cnt = 0;
vu16 T_1000ms_Cnt = 0;
vu16 T_1100ms_Cnt = 0;
extern u8 Count_DaiJi;
//上电首界面


extern CANTxID My_CANTxID;
extern u8 TouchKeyValue;//串口屏返回的触控ID
extern FlagStatus Flag_100ms;
FlagStatus Flag_XiaoYin=SET;
u8 Value;

FlagStatus FLag_ZhongYing=RESET;//RESET 代表中文 Set代表英文
extern FlagStatus Flag_DuiShi;
/*************设置界面变量******************/
u8 Count_tanceqi=0;//探测器个数增减计数器
u8 Count_yubaojing=20;//预报警值增减计数器
u8 Count_baojing=40;//探测器报警值增减计数器
u8 Count_dizhi=0;//探测器地址增减计数器
u8 Count_nian=16;//年计数器
u8 Count_yue=0;//月计数器
u8 Count_ri=0;//日计数器
u8 Count_shi=0;//小时计数器
u8 Count_fen=0;//分钟计数器
char shezhi_mokuai=1;//模块选择计数器
u8 Count_SheZhi=0;//设置界面增减计数器
u8 BaoChun_shezhizhi[9]={0,20,40,0,16,1,1,0,0};//用来保存设置好的值
FlagStatus Flag_XiuGai=RESET;
vu16 FangDai_Cnt;//防呆模式计数器，避免长时间处于设置界面
/*************主界面变量******************/
u8 DengZhu_KZ=0;//声报警控制标志位：1 开，0 关
u8 ShengKZ=0;//声报警控制标志位：1 开，0 关
u8 ZhiShiDeng_KZ=0;//消音按钮指示灯控制标志位：1 开，0 关
u8 YinCan_GN=0;//隐藏功能：在主界面中顺序按下3，4，5，6号按键，该参数会自加到4，然后清除铁电中所有数据
/**************报警界面申请的变量*****************/
extern u16 DangQianYeShu;
extern u16 ZongYeShu;
extern u16 BJTiaoShu;
extern u16 ZongTiaoShu;
extern u8 ChunChu_ShunXu;
/*************************************************/
/**************输入密码界面申请的变量*****************/
u16 PassWord	= 0;
u8	Cnt_Code	= 0;
u16 Code_Set	= 0x1111;
u8	Cnt_Code_Last	= 0;

u8 Floor=ZhuJieMian;						


int main(void)
{
//	u8 main_cnt;

	Hal_Init();
#ifndef DEBUG
	IWDG_ReloadCounter();
#endif

	while (Flag_100ms==RESET);
	DisplayAdjustBright(30);
	BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
	DisplaySetTouch();
	LocalAddress=ScanLocalAddress();

//	AlarmDispaly=RESET;
	DisplayFirstPicture(0);//



	init_1307();
#ifndef QINGCHU
	write_24256data(9990,0);
	write_24256data(9991,0);
	write_24256data(9992,0);
	write_24256data(9993,0);
	write_24256data(9994,0);
#endif
	DuBaoJingZhuangTai();

	read_time(&RTC_SystemTime);
	srand(RTC_SystemTime.second);


	// YinCan_GN=4;		// 手动清楚历史报警
	while (1)
	{
		/*开启隐藏功能，恢复出厂值*/
		if (YinCan_GN==4)
		{
			u8 i;
			YinCan_GN=0;
			write_24256data(9990,0);
			write_24256data(9991,0);
			write_24256data(9992,0);
			write_24256data(9993,0);
			write_24256data(9994,0);
			// write_24256data(9995,0);			// 探测器个数
			write_24256data(9996,20);
			write_24256data(9997,40);
			write_24256data(9998,0);
			write_24256data(9999,16);
			write_24256data(10000,1);
			write_24256data(10001,1);
			write_24256data(10002,0);
			write_24256data(10003,0);
			BJTiaoShu=0;
			ZongTiaoShu=0;
			ChunChu_ShunXu=0;
			DangQianYeShu=1;
			ZongYeShu=1;
			// BaoChun_shezhizhi[0]=0;
			// BaoChun_shezhizhi[1]=20;
			// BaoChun_shezhizhi[2]=40;
			// BaoChun_shezhizhi[3]=0;
			// BaoChun_shezhizhi[4]=16;
			// BaoChun_shezhizhi[5]=1;
			// BaoChun_shezhizhi[6]=1;
			// BaoChun_shezhizhi[7]=0;
			// BaoChun_shezhizhi[8]=0;
			for (i=0;i<6;i++)
			{
				LED_ZhuangTai[i].New_YuBaoJing=0;
				LED_ZhuangTai[i].Old_YuBaoJing=0;
				LED_ZhuangTai[i].New_BaoJing=0;
				LED_ZhuangTai[i].Old_BaoJing=0;
			}
			Out1_H();
			Out2_H();
			Out3_H();
			Out4_H();
			Floor= ZhuJieMian;
		}
		/**/
		switch (Floor)
		{
		case SheZhi://设置界面
			shuru_queren[0]=0;
			shuru_queren[1]=0;
			FangDai_Cnt=RESET;
			DisplayFirstPicture(SheZhiJieMianID);//设置界面
			DisplayCursorAtDesignatedSpot(0,0,0);
			DisplayAdjustBright(30);
			BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
			read_time(&RTC_SystemTime);
			DisplaySystemTime(35,RTC_SystemTime);
			DisplayWord(36,BaoChun_shezhizhi[0],0);
			DisplayWord(37,BaoChun_shezhizhi[1],0);
			DisplayWord(38,BaoChun_shezhizhi[2],0);
			DisplayWord(39,BaoChun_shezhizhi[3],0);
			Count_tanceqi=BaoChun_shezhizhi[0];
			Count_yubaojing=BaoChun_shezhizhi[1];
			Count_baojing=BaoChun_shezhizhi[2];
			Count_dizhi=BaoChun_shezhizhi[3];

			Count_nian=(RTC_SystemTime.yearl/16*10)+(RTC_SystemTime.yearl%16);
			Count_yue=(RTC_SystemTime.month/16*10)+(RTC_SystemTime.month%16);
			Count_ri=(RTC_SystemTime.day/16*10)+(RTC_SystemTime.day%16);
			Count_shi=(RTC_SystemTime.hour/16*10)+(RTC_SystemTime.hour%16);
			Count_fen=(RTC_SystemTime.minute/16*10)+(RTC_SystemTime.minute%16);
			DisplayWord(41,Count_nian,0);
			DisplayWord(42,Count_yue,0);
			DisplayWord(43,Count_ri,0);
			DisplayWord(44,Count_shi,0);
			DisplayWord(45,Count_fen,0);
			while (1)
			{
#ifndef DEBUG
				IWDG_ReloadCounter();
#endif
				if (SysTickFlag_1mS == 1)					// 系统滴嗒时钟1ms时间到，作为时间基值来处理相应程序
				{
					SysTickFlag_1mS = 0;
					T_100ms_Cnt++;
					T_500ms_Cnt++;
					T_1000ms_Cnt++;
					FangDai_Cnt++	 ;
				}
				if (T_100ms_Cnt==100)
				{
					T_100ms_Cnt=0;
					DuKaiGuanLiangShuRu();
					CAN_Com();
				}
				KongZhi_JDQ();
				if (T_1000ms_Cnt==1000)//1s刷新一次系统时间
				{
					u8 i;
					T_1000ms_Cnt=0;
					read_time(&RTC_SystemTime);

					DisplaySystemTime(35,RTC_SystemTime);

					if (ScanLocalAddress()==0x08)
					{
						for (i=1;i<7;i++)
						{
							panduan(i);
							XianShi_New_BJ(i);
						}

					}
					else
					{
						for (i=1;i<7;i++)
						{
							XianShi_New_BJ(i);
						}
					}

				}
				if (FangDai_Cnt==FangDai_Mode_On)//判断是否进入防呆模式
				{
					FangDai_Cnt=RESET;
					Floor=ZhuJieMian;
					break;
				}
				if (shuru_queren[0]==1)//主界面
				{
					Floor=ZhuJieMian;
					Flag_XiuGai=RESET;
					FangDai_Cnt=RESET;
					break;
				}
				else if (shuru_queren[1]==1)//报警查询
				{
					Floor=BaoJingChaXun;
					Flag_XiuGai=RESET;
					FangDai_Cnt=RESET;
					DangQianYeShu=1;
					if (ChunChu_ShunXu==1)
					{
						DangQianYeShu_New=1;
					}

					break;
				}
				else if (shuru_queren[2]==1)//上翻
				{
					shuru_queren[2]=0;
					FangDai_Cnt=RESET;
					if (Flag_XiuGai==RESET)
					{
						if (shezhi_mokuai>0)
						{
							shezhi_mokuai--;
						}
						if (shezhi_mokuai==0)
						{
							shezhi_mokuai=9;
						}

					}
					else
					{
						if (shezhi_mokuai==1)
						{
							Count_tanceqi++;
							if (Count_tanceqi>ShuLiang_Max)
							{
								Count_tanceqi=ShuLiang_Max;
							}
						}
						if (shezhi_mokuai==2)
						{
							Count_yubaojing++;
							if (Count_yubaojing>YuBaoJing_Max)
							{
								Count_yubaojing=YuBaoJing_Max;
							}
						}
						if (shezhi_mokuai==3)
						{
							Count_baojing++;
							if (Count_baojing>BaoJing_Max)
							{
								Count_baojing=BaoJing_Max;
							}
						}
						if (shezhi_mokuai==4)
						{
							Count_dizhi++;
							if (Count_dizhi>DiZhi_Max)
							{
								Count_dizhi=DiZhi_Max;
							}
						}
						if (shezhi_mokuai==5)
						{
							if ((Count_yue==2)&&(Count_ri==29))
							{
								Count_nian=Count_nian+4;
							}
							else
							{
								Count_nian++;
							}
							if (Count_nian>Nian_Max)
							{
								Count_nian=Nian_Max;
							}
						}
						if (shezhi_mokuai==6)
						{
							if ((Count_ri==31))
							{
								if (Count_yue==1||Count_yue==3||Count_yue==5||Count_yue==8||Count_yue==10||Count_yue==12)
								{
									Count_yue=Count_yue+2;
								}
								else if (Count_yue==7)
								{
									Count_yue++;
								}
							}
							else
							{
								Count_yue++;
							}
							if (Count_yue>Yue_Max)
							{
								Count_yue=Yue_Max;
							}
						}
						if (shezhi_mokuai==7)
						{
							Count_ri++;
							if (Count_nian%4==0&&Count_yue==2)
							{
								if (Count_ri>Ri_Max-2)
								{
									Count_ri=Ri_Max-2;
								}
							}
							if (Count_nian%4!=0&&Count_yue==2)
							{
								if (Count_ri>Ri_Max-3)
								{
									Count_ri=Ri_Max-3;
								}
							}
							if (Count_yue==1||Count_yue==3||Count_yue==5||Count_yue==7||Count_yue==8||Count_yue==10)
							{
								if (Count_ri>Ri_Max)
								{
									Count_ri=Ri_Max;
								}
							}
							if (Count_yue==4||Count_yue==6||Count_yue==9||Count_yue==11)
							{
								if (Count_ri>(Ri_Max-1))
								{
									Count_ri=(Ri_Max-1);
								}
							}
						}
						if (shezhi_mokuai==8)
						{
							Count_shi++;
							if (Count_shi>Shi_Max)
							{
								Count_shi=Shi_Max;
							}
						}
						if (shezhi_mokuai==9)
						{
							Count_fen++;
							if (Count_fen>Fen_Max)
							{
								Count_fen=Fen_Max;
							}
						}

					}
					switch (shezhi_mokuai)
					{
					case 1:
						DisplayCursorAtDesignatedSpot(1,308,128+36);
						DisplayWord(36,Count_tanceqi,0);
						break;
					case 2:
						DisplayCursorAtDesignatedSpot(1,308,164+36);
						DisplayWord(37,Count_yubaojing,0);
						break;
					case 3:
						DisplayCursorAtDesignatedSpot(1,308,201+36);
						DisplayWord(38,Count_baojing,0);
						break;
					case 4:
						DisplayCursorAtDesignatedSpot(1,308,240+36);
						DisplayWord(39,Count_dizhi,0);
						break;
					case 5:
						DisplayCursorAtDesignatedSpot(1,670,128+36);
						DisplayWord(41,Count_nian,0);
						break;
					case 6:
						DisplayCursorAtDesignatedSpot(1,670,164+36);
						DisplayWord(42,Count_yue,0);
						break;
					case 7:
						DisplayCursorAtDesignatedSpot(1,670,201+36);
						DisplayWord(43,Count_ri,0);
						break;
					case 8:
						DisplayCursorAtDesignatedSpot(1,670,240+36);
						DisplayWord(44,Count_shi,0);
						break;
					case 9:
						DisplayCursorAtDesignatedSpot(1,670,279+36);
						DisplayWord(45,Count_fen,0);
						break;
					default:
						break;
					}
					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
				}
				else if (shuru_queren[3]==1)//下翻
				{
					shuru_queren[3]=0;
					FangDai_Cnt=RESET;
					if (Flag_XiuGai==RESET)
					{
						shezhi_mokuai++;
						if (shezhi_mokuai>=10)
						{
							shezhi_mokuai=1;
						}
					}
					else
					{
						if (shezhi_mokuai==1)
						{
							Count_tanceqi--;
							if (Count_tanceqi<ShuLiang_Min)
							{
								Count_tanceqi=ShuLiang_Min;
							}
							if (Count_tanceqi==0xff)
							{
								Count_tanceqi=0;
							}
						}
						if (shezhi_mokuai==2)
						{
							Count_yubaojing--;
							if (Count_yubaojing<YuBaoJing_Min)
							{
								Count_yubaojing=YuBaoJing_Min;
							}
						}
						if (shezhi_mokuai==3)
						{
							Count_baojing--;
							if (Count_baojing<BaoJing_Min)
							{
								Count_baojing=BaoJing_Min;
							}
						}
						if (shezhi_mokuai==4)
						{
							if (Count_dizhi==0)
							{
								Count_dizhi=0;
							}
							else
							{
								Count_dizhi--;
							}
							// if (Count_dizhi<DiZhi_Min)
							// {
							// Count_dizhi=DiZhi_Min;
							// }
							if (Count_dizhi==0xff)
							{
								Count_dizhi=0;
							}
						}
						if (shezhi_mokuai==5)
						{
							if ((Count_yue==2)&&(Count_ri==29))
							{
								Count_nian=Count_nian-4;
							}
							else
							{
								Count_nian--;
							}
							if (Count_nian<Nian_Min)
							{
								Count_nian=Nian_Min;
							}
						}
						if (shezhi_mokuai==6)
						{
							if ((Count_ri==31))
							{
								if (Count_yue==3||Count_yue==5||Count_yue==7||Count_yue==10||Count_yue==12)
								{
									Count_yue=Count_yue-2;
								}
								else if (Count_yue==8)
								{
									Count_yue--;
								}
							}
							else
							{
								Count_yue--;
							}
							if (Count_yue<Yue_Min)
							{
								Count_yue=Yue_Min;
							}
						}
						if (shezhi_mokuai==7)
						{
							Count_ri--;
							if (Count_ri<Ri_Min)
							{
								Count_ri=Ri_Min;
							}
						}
						if (shezhi_mokuai==8)
						{
							Count_shi--;
							if (Count_shi<Shi_Min)
							{
								Count_shi=0;
							}
							if (Count_shi==0xff)
							{
								Count_shi=0;
							}
						}
						if (shezhi_mokuai==9)
						{
							Count_fen--;
							if (Count_fen<Fen_Min)
							{
								Count_fen=0;
							}
							if (Count_fen==0xff)
							{
								Count_fen=0;
							}
						}
					}
					switch (shezhi_mokuai)
					{
					case 1:
						DisplayCursorAtDesignatedSpot(1,308,128+36);
						DisplayWord(36,Count_tanceqi,0);
						break;
					case 2:
						DisplayCursorAtDesignatedSpot(1,308,164+36);
						DisplayWord(37,Count_yubaojing,0);
						break;
					case 3:
						DisplayCursorAtDesignatedSpot(1,308,201+36);
						DisplayWord(38,Count_baojing,0);
						break;
					case 4:
						DisplayCursorAtDesignatedSpot(1,308,240+36);
						DisplayWord(39,Count_dizhi,0);
						break;
					case 5:
						DisplayCursorAtDesignatedSpot(1,670,128+36);
						DisplayWord(41,Count_nian,0);
						break;
					case 6:
						DisplayCursorAtDesignatedSpot(1,670,164+36);
						DisplayWord(42,Count_yue,0);
						break;
					case 7:
						DisplayCursorAtDesignatedSpot(1,670,201+36);
						DisplayWord(43,Count_ri,0);
						break;
					case 8:
						DisplayCursorAtDesignatedSpot(1,670,240+36);
						DisplayWord(44,Count_shi,0);
						break;
					case 9:
						DisplayCursorAtDesignatedSpot(1,670,279+36);
						DisplayWord(45,Count_fen,0);
						break;
					default:
						break;
					}
					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
				}
				else if (shuru_queren[4]==1)//修改
				{
					shuru_queren[4]=0;
					Flag_XiuGai=SET;
					FangDai_Cnt=RESET;
					if (shezhi_mokuai==0)
					{
						shezhi_mokuai=1;
					}
					switch (shezhi_mokuai)
					{
					case 1:
						DisplayCursorAtDesignatedSpot(1,308,128+36);
						DisplayWord(36,Count_tanceqi,0);
						break;
					case 2:
						DisplayCursorAtDesignatedSpot(1,308,164+36);
						DisplayWord(37,Count_yubaojing,0);
						break;
					case 3:
						DisplayCursorAtDesignatedSpot(1,308,201+36);
						DisplayWord(38,Count_baojing,0);
						break;
					case 4:
						DisplayCursorAtDesignatedSpot(1,308,240+36);
						DisplayWord(39,Count_dizhi,0);
						break;
					case 5:
						DisplayCursorAtDesignatedSpot(1,670,128+36);
						DisplayWord(41,Count_nian,0);
						break;
					case 6:
						DisplayCursorAtDesignatedSpot(1,670,164+36);
						DisplayWord(42,Count_yue,0);
						break;
					case 7:
						DisplayCursorAtDesignatedSpot(1,670,201+36);
						DisplayWord(43,Count_ri,0);
						break;
					case 8:
						DisplayCursorAtDesignatedSpot(1,670,240+36);
						DisplayWord(44,Count_shi,0);
						break;
					case 9:
						DisplayCursorAtDesignatedSpot(1,670,279+36);
						DisplayWord(45,Count_fen,0);
						break;
					default:
						break;
					}
					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);


				}
				else if (shuru_queren[5]==1)//确认
				{
					shuru_queren[5]=0;
					FangDai_Cnt=RESET;
					if (Flag_XiuGai==SET)
					{
						Flag_XiuGai=RESET;
						DisplayCursorAtDesignatedSpot(0,0,0);
						switch (shezhi_mokuai)
						{
						case 1:
							BaoChun_shezhizhi[0]=Count_tanceqi;
							write_24256data(9995,Count_tanceqi);//铁电中保存设置后的探测器个数值
							break;
						case 2:
							BaoChun_shezhizhi[1]=Count_yubaojing;
							write_24256data(9996,Count_yubaojing);//铁电中保存设置后的预报警值
							break;
						case 3:
							BaoChun_shezhizhi[2]=Count_baojing;
							write_24256data(9997,Count_baojing);//铁电中保存设置后的报警值
							break;
						case 4:
							BaoChun_shezhizhi[3]=Count_dizhi;
							write_24256data(9998,Count_dizhi);//铁电中保存设置后的地址
							break;
						case 5:
							BaoChun_shezhizhi[4]=Count_nian;
							write_24256data(9999,Count_nian);//铁电中保存设置后的年数值
							RTC_SystemTime.yearl=((Count_nian/10)<<4)+((Count_nian%10));
							break;
						case 6:
							BaoChun_shezhizhi[5]=Count_yue;
							write_24256data(10000,Count_yue);//铁电中保存设置后的月数值
							RTC_SystemTime.month=((Count_yue/10)<<4)+((Count_yue%10));
							break;
						case 7:
							BaoChun_shezhizhi[6]=Count_ri;
							write_24256data(10001,Count_ri);//铁电中保存设置后的日数值
							RTC_SystemTime.day=((Count_ri/10)<<4)+((Count_ri%10));
							break;
						case 8:
							BaoChun_shezhizhi[7]=Count_shi;
							write_24256data(10002,Count_shi);//铁电中保存设置后的小时
							RTC_SystemTime.hour=((Count_shi/10)<<4)+((Count_shi%10));
							break;
						case 9:
							BaoChun_shezhizhi[8]=Count_fen;
							write_24256data(10003,Count_fen);//铁电中保存设置后的分钟
							RTC_SystemTime.minute=((Count_fen/10)<<4)+((Count_fen%10));
							break;
						default:
							break;
						}
						shezhi_mokuai=0;
						write_time();
					}
					break;
				}
			}
			break;
		case ZhuJieMian://主界面
			shuru_queren[0]=0;
			shuru_queren[1]=0;
			DisplayFirstPicture(ZhuJieMian);//主界面
			DisplayCursorAtDesignatedSpot(0,0,0);
			DisplayAdjustBright(30);
			BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
			read_time(&RTC_SystemTime);
			DisplaySystemTime(0,RTC_SystemTime);
			while (1)
			{
#ifndef DEBUG
				IWDG_ReloadCounter();
#endif
				if (SysTickFlag_1mS == 1)					// 系统滴嗒时钟1ms时间到，作为时间基值来处理相应程序
				{
					SysTickFlag_1mS = 0;
					T_100ms_Cnt++;
					T_500ms_Cnt++;
					T_1000ms_Cnt++;

				}
				if (T_100ms_Cnt==100)
				{
					T_100ms_Cnt=0;
					DuKaiGuanLiangShuRu();
					CAN_Com();
				}

				if (T_1000ms_Cnt==1000)//1s
				{
					u8 i;
					T_1000ms_Cnt=0;
					read_time(&RTC_SystemTime);
					DisplaySystemTime(0,RTC_SystemTime);
					LocalAddress=ScanLocalAddress();
					if (LocalAddress!=LocalAddress_old)
					{
						LocalAddress_old=LocalAddress;
						if (LocalAddress==0x01)
						{
							zaojia_max[1]=rand()%2+50;
							zaojia_max[2]=rand()%2+50;
							zaojia_max[3]=rand()%2+50;
							zaojia_max[4]=rand()%2+50;
							zaojia_max[5]=rand()%2+50;
							zaojia_max[6]=rand()%2+50;
						}
						else if (LocalAddress==0x08)
						{
							zaojia_max[1]=rand()%3+29;
							zaojia_max[2]=rand()%3+29;
							zaojia_max[3]=rand()%3+29;
							zaojia_max[4]=rand()%3+29;
							zaojia_max[5]=rand()%3+29;
							zaojia_max[6]=rand()%3+29;
						}

					}
					if (ScanLocalAddress()==0x01)
					{
						for (i=1;i<7;i++)
						{
							panduan(i);
							DisplayNongDu(i);
						}
					}
					else if (ScanLocalAddress()==0x08)
					{
						for (i=1;i<7;i++)
						{
							panduan(i);
							DisplayNongDu(i);
						}
						// panduan(1);
						// DisplayNongDu(1);
					}
					else
					{
						for (i=1;i<7;i++)
						{
							DisplayNongDu(i);
						}
					}

				}
				KongZhi_JDQ();
				if (shuru_queren[0]==1)//报警界面
				{
					Floor=BaoJingChaXun;
					DangQianYeShu=1;
					if (ChunChu_ShunXu==1)
					{
						DangQianYeShu_New=1;
					}
					break;
				}
				else if (shuru_queren[1]==1)//设置界面
				{
					// Floor=SheZhi;
					Floor=MiMaJieMian;
					break;
				}
				else if (shuru_queren[2]==1)//备用
				{
					shuru_queren[2]=0;
					YinCan_GN=1;
					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
				}
				else if (shuru_queren[3]==1)//备用
				{
					shuru_queren[3]=0;
					if (YinCan_GN==1)
					{
						YinCan_GN=2;
					}
					else
					{
						YinCan_GN=0;
					}
					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
				}
				else if (shuru_queren[4]==1)//备用
				{
					shuru_queren[4]=0;
					if (YinCan_GN==2)
					{
						YinCan_GN=3;
					}
					else
					{
						YinCan_GN=0;
					}
					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
				}
				else if (shuru_queren[5]==1)//备用
				{
					shuru_queren[5]=0;
					if (YinCan_GN==3)
					{
						//  YinCan_GN=4;//软件测评过程中取消此功能，不进行此功能
						// break;
					}
					else
					{
						YinCan_GN=0;
					}
					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
				}
			}
			break;
		case BaoJingChaXun://报警界面
			shuru_queren[0]=0;
			shuru_queren[1]=0;
			DisplayFirstPicture(BaoJingChaXun);//报警界面
			DisplayCursorAtDesignatedSpot(0,0,0);
			DisplayAdjustBright(30);
			BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
			read_time(&RTC_SystemTime);
			DisplaySystemTime(20,RTC_SystemTime);
			Display_Alarm_YeMa();
			Display_Alarm_XinXi();
			while (1)
			{
#ifndef DEBUG
				IWDG_ReloadCounter();
#endif
				if (SysTickFlag_1mS == 1)					// 系统滴嗒时钟1ms时间到，作为时间基值来处理相应程序
				{
					SysTickFlag_1mS = 0;
					T_100ms_Cnt++;
					T_500ms_Cnt++;
					T_1000ms_Cnt++;
				}
				if (T_100ms_Cnt==100)
				{
					T_100ms_Cnt=0;
					DuKaiGuanLiangShuRu();
					CAN_Com();
				}
				if (T_1000ms_Cnt==1000)//1s
				{
					u8 j;
					T_1000ms_Cnt=0;
					read_time(&RTC_SystemTime);
					DisplaySystemTime(20,RTC_SystemTime);
					if (ScanLocalAddress()==0x08)
					{
						for (j=1;j<7;j++)
						{
							panduan(j);
							XianShi_New_BJ(j);

						}
					}
					else
					{
						for (j=1;j<7;j++)
						{
							XianShi_New_BJ(j);
						}
					}
				}
				KongZhi_JDQ();
				if (shuru_queren[0]==1)//主界面
				{
					Floor=ZhuJieMian;
					break;
				}
				else if (shuru_queren[1]==1)//设置界面
				{
					//Floor=SheZhi;
					Floor=MiMaJieMian;
					break;
				}
				else if (shuru_queren[3]==1)//上翻
				{
					shuru_queren[3]=0;
					DangQianYeShu++;
					if (ZongYeShu_New>DangQianYeShu_New&&ChunChu_ShunXu==1&&DangQianYeShu<=ZongYeShu_New)
					{
						DangQianYeShu_New++	 ;
					}

					if (DangQianYeShu>ZongYeShu)
					{
						DangQianYeShu=1;
						DangQianYeShu_New=1;
					}
					if (DangQianYeShu_New>ZongYeShu_New)
					{
						DangQianYeShu_New=ZongYeShu_New;
					}
					/*if (DangQianYeShu==YeShu_Max)
					{
						DisplayFirstPicture(BaoJingChaXun);//报警界面
					}

					Display_Alarm_YeMa();
					Display_Alarm_XinXi();*/
					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
					break;
				}
				else if (shuru_queren[2]==1)//下翻
				{
					shuru_queren[2]=0;
					DangQianYeShu--;
					if (DangQianYeShu<=ZongYeShu_New)
					{
						DangQianYeShu_New=DangQianYeShu;
					}

					if (DangQianYeShu<1)
					{
						DangQianYeShu=ZongYeShu;
						DisplayFirstPicture(BaoJingChaXun);//报警界面
					}
					if (DangQianYeShu_New<1)
					{
						if (ZongYeShu_New==YeShu_Max)
						{
							DangQianYeShu_New=YeShu_Max;
						}
						else
						{
							DangQianYeShu_New=1;
						}

					}


					/*	Display_Alarm_YeMa();
						Display_Alarm_XinXi();*/
					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
					break;
				}
				else if (shuru_queren[4]==1)//备用
				{
					shuru_queren[4]=0;
					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
				}
				else if (shuru_queren[5]==1)//备用
				{
					shuru_queren[5]=0;
					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
				}
			}
			break;
		case MiMaJieMian://输入密码界面

			FangDai_Cnt=RESET;
			shuru_queren[0]=0;
			shuru_queren[1]=0;
			Cnt_Code	= 0;
			PassWord	= 0;
			DisplayFirstPicture(MiMaJieMian);//报警界面
			DisplayCursorAtDesignatedSpot(0,0,0);
			DisplayAdjustBright(30);
			BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
			read_time(&RTC_SystemTime);
			DisplaySystemTime(20,RTC_SystemTime);
			// Display_Alarm_YeMa();
			// Display_Alarm_XinXi();
			while (1)
			{
#ifndef DEBUG
				IWDG_ReloadCounter();
#endif
				if (SysTickFlag_1mS == 1)					// 系统滴嗒时钟1ms时间到，作为时间基值来处理相应程序
				{
					SysTickFlag_1mS = 0;
					T_100ms_Cnt++;
					T_500ms_Cnt++;
					T_1000ms_Cnt++;
					FangDai_Cnt++;
				}
				if (T_100ms_Cnt==100)
				{
					T_100ms_Cnt=0;
					DuKaiGuanLiangShuRu();
					CAN_Com();
				}
				if (T_1000ms_Cnt==1000)//1s
				{
					u8 j;
					T_1000ms_Cnt=0;
					read_time(&RTC_SystemTime);
					DisplaySystemTime(46,RTC_SystemTime);
					if (ScanLocalAddress()==0x08)
					{
						for (j=1;j<7;j++)
						{
							panduan(j);
							XianShi_New_BJ(j);

						}
					}
					else
					{
						for (j=1;j<7;j++)
						{
							XianShi_New_BJ(j);

						}
					}

				}
				KongZhi_JDQ();

				if (FangDai_Cnt==FangDai_Mode_On)//判断是否进入防呆模式
				{
					FangDai_Cnt=RESET;
					Floor=ZhuJieMian;
					break;
				}

				if ( Cnt_Code >= 4 )
				{
					if ( PassWord == Code_Set )
					{
						Floor = SheZhi;
						break;
					}
					else
					{
						Cnt_Code = 0;
						PassWord = 0;

						Command[0]=0x97;
						Command[1]=(u8)(47>>8);
						Command[2]=(u8)47;

						Command[3]=' ';
						Command[4]=' ';
						Command[5]=' ';
						Command[6]=' ';
						Command[7]=' ';
						Command[8]=' ';
						Command[9]=' ';
						DisplaySendCommand(10);
					}
				}
				if (shuru_queren[0]==1)			// 确定
				{
					FangDai_Cnt=RESET;
					shuru_queren[0] = 0;
					Floor=ZhuJieMian;
					break;
					// if(Cnt_Code != 4)
					// {
					// Cnt_Code = 0;
					// PassWord = 0;

					// Command[0]=0x97;
					// Command[1]=(u8)(47>>8);
					// Command[2]=(u8)47;

					// Command[3]=' ';
					// Command[4]=' ';
					// Command[5]=' ';
					// Command[6]=' ';
					// Command[7]=' ';
					// Command[8]=' ';
					// Command[9]=' ';
					// DisplaySendCommand(10);
					// }
				}
				else if (shuru_queren[1]==1)	// 返回
				{
					FangDai_Cnt=RESET;
					shuru_queren[1] = 0;
					Floor=BaoJingChaXun;
					break;
				}
				else if (shuru_queren[2]==1)	// 1
				{
					FangDai_Cnt=RESET;
					shuru_queren[2] = 0;
					PassWord |= 1 << Cnt_Code*4;
					Cnt_Code++;

					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
				}
				else if (shuru_queren[3]==1)	// 2
				{
					FangDai_Cnt=RESET;
					shuru_queren[3] = 0;
					PassWord |= 2 << Cnt_Code*4;
					Cnt_Code++;

					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
				}
				else if (shuru_queren[4]==1)	// 3
				{
					FangDai_Cnt=RESET;
					shuru_queren[4]=0;
					PassWord |= 3 << Cnt_Code*4;
					Cnt_Code++;

					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
				}
				else if (shuru_queren[5]==1)	// 4
				{
					FangDai_Cnt=RESET;
					shuru_queren[5]=0;
					PassWord |= 4 << Cnt_Code*4;
					Cnt_Code++;

					DisplayAdjustBright(30);
					BeiGuangZiDongKongZhi(40,LiangDu_DaiJi,30);
				}

				if ( Cnt_Code != Cnt_Code_Last )
				{
					u8 j;
					Cnt_Code_Last = Cnt_Code;
					Command[0]=0x97;
					Command[1]=(u8)(47>>8);
					Command[2]=(u8)47;

					for ( j=0;j<Cnt_Code;j++ )
					{
						if ( j < Cnt_Code-1 )
						{
							Command[2*j+3] = '*';
						}
						else
						{
							Command[2*j+3] = ((u16)(PassWord >> (4*j)) & 0x000F) + '0';
						}
					}
					Command[4]=' ';
					Command[6]=' ';
					Command[8]=' ';

					// Command[3]=(u16)(PassWord & 0x000F) + '0';
					// Command[4]=' ';
					// Command[5]=(u16)((PassWord & 0x00F0)>>4) + '0';
					// Command[6]=' ';
					// Command[7]=(u16)((PassWord & 0x0F00)>>8) + '0';
					// Command[8]=' ';
					// Command[9]=(u16)((PassWord & 0xF000)>>12) + '0';
					// Command[3]=(u16)(PassWord & 0x000F) + '0';
					// Command[4]=' ';
					// Command[5]=(u16)((PassWord & 0x00F0)>>4) + '0';
					// Command[6]=' ';
					// Command[7]=(u16)((PassWord & 0x0F00)>>8) + '0';
					// Command[8]=' ';
					// Command[9]=(u16)((PassWord & 0xF000)>>12) + '0';
					// Command[3]=(u16)(PassWord & 0x000F) + '0';
					// Command[4]=' ';
					// Command[5]=(u16)((PassWord & 0x00F0)>>4) + '0';
					// Command[6]=' ';
					// Command[7]=(u16)((PassWord & 0x0F00)>>8) + '0';
					// Command[8]=' ';
					// Command[9]=(u16)((PassWord & 0xF000)>>12) + '0';
					DisplaySendCommand(Cnt_Code * 2 + 2);
				}
			}
			break;
		default:
			break;
		}
	}
}
