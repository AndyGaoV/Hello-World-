/**
  ******************************************************************************
  * @file    DisplayHandle.c
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
#define DisplayHandle_GLOBALS
#include "DisplayHandle.h"
#include "BSP_Display.h"
#include "Usart_Handlle.h"
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
My_Picture LED_ZhuangTai[6]={
	{40,248,303,358,HongDeng,HuiDeng,LvDeng,HuangDeng,0,0,0,0,0,0,0},//1��
	{163,248,303,358,HongDeng,HuiDeng,LvDeng,HuangDeng,0,0,0,0,0,0,0},//2��
	{287,248,303,358,HongDeng,HuiDeng,LvDeng,HuangDeng,0,0,0,0,0,0,0},//3��
	{411,248,303,358,HongDeng,HuiDeng,LvDeng,HuangDeng,0,0,0,0,0,0,0},//4��
	{537,248,303,358,HongDeng,HuiDeng,LvDeng,HuangDeng,0,0,0,0,0,0,0},//5��
	{662,248,303,358,HongDeng,HuiDeng,LvDeng,HuangDeng,0,0,0,0,0,0,0},//6��
};
My_TanCeQi TanCeQi[30]={
	{0,0,0,0,0,0},
	{1,35,50,0,0,200},
	{2,35,50,0,0,210},
	{3,35,50,0,0,220},
	{4,35,50,0,0,230},
	{5,35,50,0,0,240},
	{6,35,50,0,0,250},
	{7,35,50,0,0,260},
	{8,35,50,0,0,270},
	{9,35,50,0,0,280},
	{10,35,50,0,0,290},
	{11,35,50,0,0,300},
	{12,35,50,0,0,310},
	{13,35,50,0,0,320},
	{14,35,50,0,0,330},
	{15,35,50,0,0,340},
	{16,35,50,0,0,350},
	{17,35,50,0,0,360},
	{18,35,50,0,0,370},
	{19,35,50,0,0,380},
	{20,35,50,0,0,390},
	{21,35,50,0,0,400},
	{22,35,50,0,0,410},
	{23,35,50,0,0,420},
	{24,35,50,0,0,430},
	{25,35,50,0,0,440},
	{26,35,50,0,0,450},
	{27,35,50,0,0,460},
	{28,35,50,0,0,470},
	{29,35,50,0,0,480},
};

My_Alarm BaoJing=
    {0,"����Ũ��ֵ��&","����Ũ��ֵ����&",0,0,0,0,0,0,0}//1#
    ;

/**
 * @brief  Configures the different GPIO ports.
 * @param  None
 * @retval None
 */
/**
  * @brief  ���챨��������ʾ����.
  * @param  None
  * @retval None
  */
extern u8 YeMa;
extern u8 Floor;
extern u8 ChunChu_ShunXu;
u8 Str_YeShu[33]={" 01/ 02&"};
extern u8 ExtAlarmXuLie[];
extern FlagStatus FLag_ZhongYing;
u16 BJTiaoShu=0;// �������汨������
u16 DangQianYeShu=1;//������ѯҳ����ʾ�ĵ�ǰҳ��
u16 ZongYeShu=0;//������ѯҳ�������ʾ����ҳ��
u16 DangQianYeShu_New=1;//����100�������������ı������Ӧ�ĵ�ǰҳ��
u16 ZongYeShu_New=0;//����100�������������ı������Ӧ����ҳ��
u16 ZongTiaoShu=0;//��ౣ��ı���������
u8 JDQ_ZhuangTai[6]={0};//����̵������������״̬
/**
  * @brief ��ʾ������ѯ�����ҳ����
  * @param  �ı������� �ı������׵�ַ �ı����ݸ���
  * @retval
  */
void Display_Alarm_YeMa(void)
{
	if (ChunChu_ShunXu==0)
	{
		if (BJTiaoShu<8)
		{
			ZongYeShu=1;
		}
		else
		{
			if (BJTiaoShu%7==0)
			{
				ZongYeShu=BJTiaoShu/7;
			}
			else
			{
				ZongYeShu=BJTiaoShu/7+1;
			}
		}
	}
	else
	{
		ZongYeShu=ZongTiaoShu/7+1;
		if (BJTiaoShu%7==0)
		{
			ZongYeShu_New=BJTiaoShu/7;
		}
		else
		{
			ZongYeShu_New=BJTiaoShu/7+1;
		}
	}
	if (DangQianYeShu<10)
	{
		Str_YeShu[0]=0x20;
		Str_YeShu[1]=0x20;
		Str_YeShu[2]=DangQianYeShu%10+0x30;
	}
	else if (DangQianYeShu<100)
	{
		Str_YeShu[0]=0x20;
		Str_YeShu[1]=DangQianYeShu/10+0x30;
		Str_YeShu[2]=DangQianYeShu%10+0x30;
	}
	else if (DangQianYeShu<1000)
	{
		Str_YeShu[0]=DangQianYeShu/100+0x30;
		Str_YeShu[1]=(DangQianYeShu%100)/10+0x30;
		Str_YeShu[2]=DangQianYeShu%10+0x30;
	}
	if (ZongYeShu<10)
	{
		Str_YeShu[4]=ZongYeShu%10+0x30;
		Str_YeShu[5]=0x20;
		Str_YeShu[6]=0x20;
	}
	else if (ZongYeShu<100)
	{
		Str_YeShu[4]=ZongYeShu/10+0x30;
		Str_YeShu[5]=ZongYeShu%10+0x30;
		Str_YeShu[6]=0x20;
	}
	else if (ZongYeShu<1000)
	{
		Str_YeShu[4]=ZongYeShu/100+0x30;
		Str_YeShu[5]=(ZongYeShu%100)/10+0x30;
		Str_YeShu[6]=ZongYeShu%10+0x30;
	}

	DisplayBaoJingWord(40,Str_YeShu);
}
/**
  * @brief ��ʾ������ѯ����ĵ�ַ��
  * @param  �ı������� �ı������׵�ַ �ı����ݸ���
  * @retval
  */
/*void Display_BJ_DiZhi(u16 WordAreaNum,My_Alarm *DiZhi)
{
	Command[0]=0x97;//ָ��
	Command[1]=(u8)(WordAreaNum>>8);
	Command[2]=(u8)WordAreaNum;
	if ((DiZhi->TanCeQiDiZhi<10))
	{
		Command[3]=0x20;
		Command[4]=DiZhi->TanCeQiDiZhi+0x30;
		DisplaySendCommand(5);
	}
	else if (DiZhi->TanCeQiDiZhi<100)
	{
		Command[3]=DiZhi->TanCeQiDiZhi/10+0X30;
		Command[4]=DiZhi->TanCeQiDiZhi%10+0X30;
		DisplaySendCommand(5);
	}
	else//����4λ����ʾ������
	{
		Command[3]='?';
		Command[4]='?';
		Command[5]='?';
		Command[6]='?';
		DisplaySendCommand(7);
	}
}*/
void Display_BJ_DiZhi(u16 WordAreaNum,u16 DiZhi)
{
	Command[0]=0x97;//ָ��
	Command[1]=(u8)(WordAreaNum>>8);
	Command[2]=(u8)WordAreaNum;
	if (read_24256data(DiZhi*8+1)<10)
	{
		Command[3]=0x20;
		Command[4]=read_24256data(DiZhi*8+1)+0x30;
		DisplaySendCommand(5);
	}
	else if (read_24256data(DiZhi*8+1)<100)
	{
		Command[3]=read_24256data(DiZhi*8+1)/10+0X30;
		Command[4]=read_24256data(DiZhi*8+1)+0X30;
		DisplaySendCommand(5);
	}
	else//����4λ����ʾ������
	{
		Command[3]='?';
		Command[4]='?';
		Command[5]='?';
		Command[6]='?';
		DisplaySendCommand(7);
	}
}
/**
  * @brief ��ʾ������ѯ�����������
  * @param  �ı������� �ı������׵�ַ �ı����ݸ���
  * @retval
  */
/* void Display_BJ_MingCheng(u16 WordAreaNum,My_Alarm *MingCheng)
{
	u8 temp=0;
	Command[0]=0x97;//ָ��
	Command[1]=(u8)(WordAreaNum>>8);
	Command[2]=(u8)WordAreaNum;
	if (MingCheng->BaoJingLeiXin==1)
	{
		while ((MingCheng->CN_YBJ[temp]!='&')&&(temp<32))
		{
			Command[temp+3]=MingCheng->CN_YBJ[temp];
			temp++;
		}
	}
	else if (MingCheng->BaoJingLeiXin==2)
	{
		while ((MingCheng->CN_BJ[temp]!='&')&&(temp<32))
		{
			Command[temp+3]=MingCheng->CN_BJ[temp];
			temp++;
		}
	}
	DisplaySendCommand(temp+3);
} */
void Display_BJ_MingCheng(u16 WordAreaNum,My_Alarm *MingCheng,u16 MingCheng1)
{
	u8 temp=0;
	Command[0]=0x97;//ָ��
	Command[1]=(u8)(WordAreaNum>>8);
	Command[2]=(u8)WordAreaNum;
	if (read_24256data(MingCheng1*8+8)==1)
	{
		while ((MingCheng->CN_YBJ[temp]!='&')&&(temp<32))
		{
			Command[temp+3]=MingCheng->CN_YBJ[temp];
			temp++;
		}
	}
	else if (read_24256data(MingCheng1*8+8)==2)
	{
		while ((MingCheng->CN_BJ[temp]!='&')&&(temp<32))
		{
			Command[temp+3]=MingCheng->CN_BJ[temp];
			temp++;
		}
	}
	DisplaySendCommand(temp+3);
}
/**
  * @brief ��ʾ������ѯ�����ʱ����
  * @param  �ı������� �ı������׵�ַ �ı����ݸ���
  * @retval
  */
/*void Display_BJ_ShiJian(u16 WordAreaNum,My_Alarm *ShiJian)
{
	Command[0]=0x97;
	Command[1]=(u8)(WordAreaNum>>8);
	Command[2]=(u8)WordAreaNum;
	Command[3]=0x32;
	Command[4]=0x30;
	Command[5]=ShiJian->BaoJingNian/16+0x30;
	Command[6]=ShiJian->BaoJingNian%16+0x30;
	Command[7]=0x2d;//"-"
	Command[8]=ShiJian->BaoJingYue/16+0x30;
	Command[9]=ShiJian->BaoJingYue%16+0x30;
	Command[10]=0x2d;//"-"
	Command[11]=ShiJian->BaoJingRi/16+0x30;
	Command[12]=ShiJian->BaoJingRi%16+0x30;
	Command[13]=0x20;//" "
	Command[14]=ShiJian->BaoJingShi/16+0x30;
	Command[15]=ShiJian->BaoJingShi%16+0x30;
	Command[16]=0x3a;//":"
	Command[17]=ShiJian->BaoJingFen/16+0x30;
	Command[18]=ShiJian->BaoJingFen%16+0x30;
	Command[19]=0x3a;//":"
	Command[20]=ShiJian->BaoJingMiao/16+0x30;
	Command[21]=ShiJian->BaoJingMiao%16+0x30;
	DisplaySendCommand(22);
}*/
void Display_BJ_ShiJian(u16 WordAreaNum,u16 ShiJian)
{
	Command[0]=0x97;
	Command[1]=(u8)(WordAreaNum>>8);
	Command[2]=(u8)WordAreaNum;
	Command[3]=0x32;
	Command[4]=0x30;
	Command[5]=read_24256data(ShiJian*8+2)/16+0x30;
	Command[6]=read_24256data(ShiJian*8+2)%16+0x30;
	Command[7]=0x2d;//"-"
	Command[8]=read_24256data(ShiJian*8+3)/16+0x30;
	Command[9]=read_24256data(ShiJian*8+3)%16+0x30;
	Command[10]=0x2d;//"-"
	Command[11]=read_24256data(ShiJian*8+4)/16+0x30;
	Command[12]=read_24256data(ShiJian*8+4)%16+0x30;
	Command[13]=0x20;//" "
	Command[14]=read_24256data(ShiJian*8+5)/16+0x30;
	Command[15]=read_24256data(ShiJian*8+5)%16+0x30;
	Command[16]=0x3a;//":"
	Command[17]=read_24256data(ShiJian*8+6)/16+0x30;
	Command[18]=read_24256data(ShiJian*8+6)%16+0x30;
	Command[19]=0x3a;//":"
	Command[20]=read_24256data(ShiJian*8+7)/16+0x30;
	Command[21]=read_24256data(ShiJian*8+7)%16+0x30;
	if (Command[14]==0&&Command[15]==0&&Command[17]==0&&Command[18]==0&&Command[20]==0&&Command[21]==0)
	{
		ShiJian=1;
	}
	DisplaySendCommand(22);
}
/**
  * @brief �жϴ����������ϱ���,���Ƽ̵������
  * @param  �������ɼ�����Ũ��ֵ ��������
  * @retval
  */



/**
  * @brief ��ʾ������ѯ�������Ϣ
  * @param  �ı������� �ı������׵�ַ �ı����ݸ���
  * @retval
  */

void Display_Alarm_XinXi(void)
{
	u16 cnt;//�������汨����ĵ�ַ
	u16 cnt1;//�������津�����ı���ID�ŵĹ���
	u16 cnt2;//�������津�����ı���ID�ŵ�����
	u16 cnt3,cnt4;//������ �����
	/****************************************************************************************************************/
	/*�����յ��ı�����С��100��ʱ*/
	/*�����κ������ڼ��㵱ǰҳ����Ҫ��ʾ������ĵ�ַ��������ʾ��������ı�������*/
	if (DangQianYeShu<ZongYeShu||ZongTiaoShu%7==0)//������ĸ���Ϊ7����������δ�������һҳʱ��һҳ��ʾ7��
	{
		cnt2=7;//����7��������ʱ����7���ı���
	}
	else
	{
		cnt2=ZongTiaoShu%7;//����7��������ʱ�����һҳ�ı��������
	}
	if (ZongTiaoShu<=7)
	{
		cnt=ZongTiaoShu-1;//����ҳ��ֻ��һҳʱ��������ĸ���
	}
	else
	{
		cnt=ZongTiaoShu-1-7*(DangQianYeShu-1);//����ҳ�����һҳʱ�����һҳ�ı�������
	}
	/****************************************************************************************************************/

	/****************************************************************************************************************/
	/*�����յ��ı����㳬��100��ʱ*/
	/*�����κ������ڼ��㳬���ı�����ĵ�ַ���ı�������*/
	if (DangQianYeShu_New<ZongYeShu_New||BJTiaoShu%7==0)
	{
		cnt3=7;//����7��������ʱ����7���ı���
	}
	else
	{
		cnt3=BJTiaoShu%7;//����7��������ʱ�����һҳ�ı��������
	}
	if (BJTiaoShu<=7)
	{
		cnt4=BJTiaoShu-1;//����ҳ��ֻ��һҳʱ��������ĸ���
	}
	else
	{
		cnt4=BJTiaoShu-1-7*(DangQianYeShu_New-1);//����ҳ�����һҳʱ�����һҳ�ı�������
	}
	/****************************************************************************************************************/

	if (ZongTiaoShu!=0)//�б������ʱ��
	{
		if (ChunChu_ShunXu==1)//����ı����㳬��100���ˣ���ʼ����
		{
			if (DangQianYeShu>ZongYeShu_New)
			{
				cnt3=0;
				cnt=cnt+BJTiaoShu;
			}
			for (cnt1=0;cnt1<cnt3;cnt1++)
			{
				Display_BJ_DiZhi(13+cnt1,cnt4-cnt1);
				Display_BJ_MingCheng(21+cnt1,&BaoJing,cnt4-cnt1);
				Display_BJ_ShiJian(28+cnt1,cnt4-cnt1);
			}
			for (cnt1=0;cnt1<cnt2-cnt3;cnt1++)
			{
				Display_BJ_DiZhi(13+cnt3+cnt1,cnt-cnt1);
				Display_BJ_MingCheng(21+cnt3+cnt1,&BaoJing,cnt-cnt1);
				Display_BJ_ShiJian(28+cnt3+cnt1,cnt-cnt1);
			}
		}
		else//����ı�����δ����100�������ø���
		{
			for (cnt1=0;cnt1<cnt2;cnt1++)
			{
				Display_BJ_DiZhi(13+cnt1,cnt-cnt1);
				Display_BJ_MingCheng(21+cnt1,&BaoJing,cnt-cnt1);
				Display_BJ_ShiJian(28+cnt1,cnt-cnt1);
			}
		}

	}

}
/**
  * @brief �жϴ����������ϱ���
  * @param  �������ɼ�����Ũ��ֵ ��������
  * @retval
  */

u8 ChunChu_ShunXu=0;//���ڱ������ݵ�˳��0-100��100-0
void PanDuanBaoJingZhuangTai(u8 addr)
{
	if ((~LED_ZhuangTai[addr-1].Old_BaoJing)&LED_ZhuangTai[addr-1].New_BaoJing)
	{
		LED_ZhuangTai[addr-1].End_BaoJing=1;
		JDQ_ZhuangTai[addr-1]=1;
	}
	if ((~LED_ZhuangTai[addr-1].Old_YuBaoJing)&LED_ZhuangTai[addr-1].New_YuBaoJing)
	{
		LED_ZhuangTai[addr-1].End_YuBaoJing=1;
		JDQ_ZhuangTai[addr-1]=1;
	}
	LED_ZhuangTai[addr-1].Old_BaoJing=LED_ZhuangTai[addr-1].New_BaoJing;
	LED_ZhuangTai[addr-1].Old_YuBaoJing=LED_ZhuangTai[addr-1].New_YuBaoJing;
	if (LED_ZhuangTai[addr-1].End_YuBaoJing==1||LED_ZhuangTai[addr-1].End_BaoJing==1)
	{
		if (BJTiaoShu==BJGeShu)
		{
			BJTiaoShu=0;
			ChunChu_ShunXu=1;
		}

		if (LED_ZhuangTai[addr-1].End_YuBaoJing==1)
		{
			LED_ZhuangTai[addr-1].End_YuBaoJing=0;
			write_24256data(BJTiaoShu*8+8,1);
		}
		else if (LED_ZhuangTai[addr-1].End_BaoJing==1)
		{
			LED_ZhuangTai[addr-1].End_BaoJing=0;
			write_24256data(BJTiaoShu*8+8,2);
		}

		read_time(&RTC_SystemTime);
		write_24256data(BJTiaoShu*8+1,addr);
		write_24256data(BJTiaoShu*8+2,RTC_SystemTime.yearl);
		write_24256data(BJTiaoShu*8+3,RTC_SystemTime.month);
		write_24256data(BJTiaoShu*8+4,RTC_SystemTime.day);
		write_24256data(BJTiaoShu*8+5,RTC_SystemTime.hour);
		write_24256data(BJTiaoShu*8+6,RTC_SystemTime.minute);
		write_24256data(BJTiaoShu*8+7,RTC_SystemTime.second);
		/*	BaoJing[BJTiaoShu].TanCeQiDiZhi=read_24256data(BJTiaoShu*8+1);
			BaoJing[BJTiaoShu].BaoJingNian=read_24256data(BJTiaoShu*8+2);
			BaoJing[BJTiaoShu].BaoJingYue=read_24256data(BJTiaoShu*8+3);
			BaoJing[BJTiaoShu].BaoJingRi=read_24256data(BJTiaoShu*8+4);
			BaoJing[BJTiaoShu].BaoJingShi=read_24256data(BJTiaoShu*8+5);
			BaoJing[BJTiaoShu].BaoJingFen=read_24256data(BJTiaoShu*8+6);
			BaoJing[BJTiaoShu].BaoJingMiao=read_24256data(BJTiaoShu*8+7);
			BaoJing[BJTiaoShu].BaoJingLeiXin=read_24256data(BJTiaoShu*8+8);	 */

		/*����ֻ��1000��*/
		if (BJTiaoShu<BJGeShu)
		{
			BJTiaoShu++;
			if (ZongTiaoShu!=BJGeShu)
			{
				ZongTiaoShu++;
			}
			else
			{
				ZongTiaoShu=BJGeShu;
			}

		}


		/*���������̶���������洢����#990��#991��ַ��*/
		write_24256data(9990,(u8)(BJTiaoShu>>8));//���λ
		write_24256data(9991,(u8)BJTiaoShu);//���λ
		write_24256data(9992,(u8)(ZongTiaoShu>>8));//���λ
		write_24256data(9993,(u8)ZongTiaoShu);//���λ
		write_24256data(9994,(u8)ChunChu_ShunXu);//���λ
		/*������ڱ�����ѯ���棬�����±�������ת����������ʾ*/
		if (Floor!=ZhuJieMian)
		{
			shuru_queren[0]=1;
		}
	}
}
extern u8 Count_tanceqi;
extern u8 Count_yubaojing;
extern u8 Count_baojing;
extern u8 Count_dizhi;
extern u8 Count_nian;
extern u8 Count_yue;
extern u8 Count_ri;
extern u8 Count_shi;
extern u8 Count_fen;
void DuBaoJingZhuangTai(void)
{
//	u8 ccnt=0;
	BJTiaoShu=(read_24256data(9990)<<8)|read_24256data(9991);
	ZongTiaoShu=(read_24256data(9992)<<8)|read_24256data(9993);
	ChunChu_ShunXu= read_24256data(9994);
	if (read_24256data(9995)!=0xff)
	{

		Count_tanceqi=read_24256data(9995);
		Count_yubaojing=read_24256data(9996);
		Count_baojing=read_24256data(9997);
		Count_dizhi=read_24256data(9998);
		Count_nian=read_24256data(9999);
		Count_yue=read_24256data(10000);
		Count_ri=read_24256data(10001);
		Count_shi=read_24256data(10002);
		Count_fen=read_24256data(10003);
		BaoChun_shezhizhi[0]=Count_tanceqi;
		BaoChun_shezhizhi[1]=Count_yubaojing;
		BaoChun_shezhizhi[2]=Count_baojing;
		BaoChun_shezhizhi[3]=Count_dizhi;
		BaoChun_shezhizhi[4]=Count_nian;
		BaoChun_shezhizhi[5]=Count_yue;
		BaoChun_shezhizhi[6]=Count_ri;
		BaoChun_shezhizhi[7]=Count_shi;
		BaoChun_shezhizhi[8]=Count_fen;
	}
	/*	for (ccnt=BJTiaoShu;ccnt>0;ccnt--)
		{
			BaoJing[ccnt-1].TanCeQiDiZhi=read_24256data((ccnt-1)*8+1);
			BaoJing[ccnt-1].BaoJingNian=read_24256data((ccnt-1)*8+2);
			BaoJing[ccnt-1].BaoJingYue=read_24256data((ccnt-1)*8+3);
			BaoJing[ccnt-1].BaoJingRi=read_24256data((ccnt-1)*8+4);
			BaoJing[ccnt-1].BaoJingShi=read_24256data((ccnt-1)*8+5);
			BaoJing[ccnt-1].BaoJingFen=read_24256data((ccnt-1)*8+6);
			BaoJing[ccnt-1].BaoJingMiao=read_24256data((ccnt-1)*8+7);
			BaoJing[ccnt-1].BaoJingLeiXin=read_24256data((ccnt-1)*8+8);
		}
		for (ccnt=ZongTiaoShu;ccnt>BJTiaoShu;ccnt--)
		{
			BaoJing[ccnt-1].TanCeQiDiZhi=read_24256data((ccnt-1)*8+1);
			BaoJing[ccnt-1].BaoJingNian=read_24256data((ccnt-1)*8+2);
			BaoJing[ccnt-1].BaoJingYue=read_24256data((ccnt-1)*8+3);
			BaoJing[ccnt-1].BaoJingRi=read_24256data((ccnt-1)*8+4);
			BaoJing[ccnt-1].BaoJingShi=read_24256data((ccnt-1)*8+5);
			BaoJing[ccnt-1].BaoJingFen=read_24256data((ccnt-1)*8+6);
			BaoJing[ccnt-1].BaoJingMiao=read_24256data((ccnt-1)*8+7);
			BaoJing[ccnt-1].BaoJingLeiXin=read_24256data((ccnt-1)*8+8);
		}	*/
}




extern My_TanCeQi TanCeQi[];
/*��ʾÿ����������Ũ��ֵ��ͨѶ��Ԥ�����ͱ���״̬*/
//state = 0 ������Ҫ��ʾ state = 1 ,����Ҫ��ʾ������������б����ж�
void DisplayNongDu(u8 Temp)
{
	if (Temp<=BaoChun_shezhizhi[0])
	{
		/*ͨѶ�����ж�*/
		if (LED_ZhuangTai[Temp-1].GuZhang>=5)
		{
			LED_ZhuangTai[Temp-1].GuZhang=5;
			/*ͨѶ���������*/
			DisplayPictureAtDesignatedSpot(LED_ZhuangTai[Temp-1].Pic_Hong,LED_ZhuangTai[Temp-1].All_X_Coord,LED_ZhuangTai[Temp-1].TongXin_Y_Coord);
		}
		else
		{
			LED_ZhuangTai[Temp-1].GuZhang++;
			/*ͨѶ�������̵�*/
			DisplayPictureAtDesignatedSpot(LED_ZhuangTai[Temp-1].Pic_Lv,LED_ZhuangTai[Temp-1].All_X_Coord,LED_ZhuangTai[Temp-1].TongXin_Y_Coord);
		}
		/*�ɼ�����Ũ��ֵ����Ԥ����ֵ*/
		if (TanCeQi[Temp].NongDu>BaoChun_shezhizhi[1])
		{
			DisplayWord(Temp,TanCeQi[Temp].NongDu,0);//��ʾŨ��ֵ
			/*�ɼ�����Ũ��ֵ����Ԥ����ֵ��С�ڱ���ֵʱ��Ԥ�����Ƶ���,���������*/
			if (TanCeQi[Temp].NongDu<=BaoChun_shezhizhi[2])
			{
				LED_ZhuangTai[Temp-1].New_YuBaoJing=1;
				LED_ZhuangTai[Temp-1].New_BaoJing=0;
				DisplayPictureAtDesignatedSpot(LED_ZhuangTai[Temp-1].Pic_Huang,LED_ZhuangTai[Temp-1].All_X_Coord,LED_ZhuangTai[Temp-1].YuBaoJing_Y_Coord);
				DisplayPictureAtDesignatedSpot(LED_ZhuangTai[Temp-1].Pic_Hui,LED_ZhuangTai[Temp-1].All_X_Coord,LED_ZhuangTai[Temp-1].BaoJing_Y_Coord);
			}
			/*�ɼ�����Ũ��ֵ���ڱ���ֵʱ�������������Ԥ���������*/
			else if ((TanCeQi[Temp].NongDu>BaoChun_shezhizhi[2])&&(TanCeQi[Temp].NongDu<=100))
			{
				LED_ZhuangTai[Temp-1].New_BaoJing=1;
				DisplayPictureAtDesignatedSpot(LED_ZhuangTai[Temp-1].Pic_Hui,LED_ZhuangTai[Temp-1].All_X_Coord,LED_ZhuangTai[Temp-1].YuBaoJing_Y_Coord);
				DisplayPictureAtDesignatedSpot(LED_ZhuangTai[Temp-1].Pic_Hong,LED_ZhuangTai[Temp-1].All_X_Coord,LED_ZhuangTai[Temp-1].BaoJing_Y_Coord);
			}
			PanDuanBaoJingZhuangTai(Temp);
		}
		/*�ɼ�����Ũ��ֵС��Ԥ����ֵʱ��Ԥ�����ƣ���������*/
		else
		{
			DisplayWord(Temp+6,TanCeQi[Temp].NongDu,0);
			DisplayPictureAtDesignatedSpot(LED_ZhuangTai[Temp-1].Pic_Hui,LED_ZhuangTai[Temp-1].All_X_Coord,LED_ZhuangTai[Temp-1].YuBaoJing_Y_Coord);
			DisplayPictureAtDesignatedSpot(LED_ZhuangTai[Temp-1].Pic_Hui,LED_ZhuangTai[Temp-1].All_X_Coord,LED_ZhuangTai[Temp-1].BaoJing_Y_Coord);
			LED_ZhuangTai[Temp-1].New_YuBaoJing=0;
			LED_ZhuangTai[Temp-1].Old_YuBaoJing=0;
			LED_ZhuangTai[Temp-1].New_BaoJing=0;
			LED_ZhuangTai[Temp-1].Old_BaoJing=0;
			JDQ_ZhuangTai[Temp-1]=0;
		}
	}
	else//��ǰ̽��������С��TEMPֵ���򽫵ƺͼ̵�����״̬������
	{
		LED_ZhuangTai[Temp-1].New_YuBaoJing=0;
		LED_ZhuangTai[Temp-1].Old_YuBaoJing=0;
		LED_ZhuangTai[Temp-1].New_BaoJing=0;
		LED_ZhuangTai[Temp-1].Old_BaoJing=0;
		JDQ_ZhuangTai[Temp-1]=0;
	}
}
/*�ڱ�����ѯ������ʾ�����ı���*/
void XianShi_New_BJ(u8 Temp)
{
	if (Temp<=BaoChun_shezhizhi[0])
	{
		if (TanCeQi[Temp].NongDu>BaoChun_shezhizhi[1])
		{
			if (TanCeQi[Temp].NongDu<=BaoChun_shezhizhi[2])
			{
				LED_ZhuangTai[Temp-1].New_YuBaoJing=1;
			}
			/*�ɼ�����Ũ��ֵ���ڱ���ֵʱ�������������Ԥ���������*/
			else if ((TanCeQi[Temp].NongDu>BaoChun_shezhizhi[2])&&(TanCeQi[Temp].NongDu<=100))
			{
				LED_ZhuangTai[Temp-1].New_BaoJing=1;
			}
			PanDuanBaoJingZhuangTai(Temp);
		}
		/*�ɼ�����Ũ��ֵС��Ԥ����ֵʱ��Ԥ�����ƣ���������*/
		else
		{
			LED_ZhuangTai[Temp-1].New_YuBaoJing=0;
			LED_ZhuangTai[Temp-1].Old_YuBaoJing=0;
			LED_ZhuangTai[Temp-1].New_BaoJing=0;
			LED_ZhuangTai[Temp-1].Old_BaoJing=0;
			JDQ_ZhuangTai[Temp-1]=0;
		}
	}
	else//��ǰ̽��������С��TEMPֵ���򽫵ƺͼ̵�����״̬������
	{
		LED_ZhuangTai[Temp-1].New_YuBaoJing=0;
		LED_ZhuangTai[Temp-1].Old_YuBaoJing=0;
		LED_ZhuangTai[Temp-1].New_BaoJing=0;
		LED_ZhuangTai[Temp-1].Old_BaoJing=0;
		JDQ_ZhuangTai[Temp-1]=0;
	}
}
