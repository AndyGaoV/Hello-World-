/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef DisplayHandle_H
#define DisplayHandle_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "BSP_Display.h"
/* Exported types ------------------------------------------------------------*/

/* Exported define -----------------------------------------------------------*/
#ifdef DisplayHandle_GLOBALS
#define DisplayHandle_EXT
#else
#define DisplayHandle_EXT extern
#endif 

#define LvDeng 0
#define HongDeng 1
#define HuiDeng 2
#define HuangDeng 3



#define YanShenBJ_LeiBieBianHao (u16)0x0011
#define HuJiao_LeiBieBianHao (u16)0x0010
#define zhiban_LeiBieBianHao (u16)0x000f

/**ͼƬ��ź궨��***************************/
#define ZhuJieMianID 0x0000
#define BaoJingJieMianID 0x0001
#define SheZhiJieMianID 0x0002
#define BJGeShu 1000 //һ������100��


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
typedef struct 
{
	u16 All_X_Coord;
	u16 TongXin_Y_Coord;
	u16 YuBaoJing_Y_Coord;
	u16 BaoJing_Y_Coord;
	u16 Pic_Hong;
	u16 Pic_Hui;
	u16 Pic_Lv;
	u16 Pic_Huang;
	u8 GuZhang;
	u8 Old_YuBaoJing;//��Ԥ����
	u8 New_YuBaoJing;//��Ԥ����
	u8 End_YuBaoJing;//���������Ԥ����״̬
	u8 Old_BaoJing;//�ϱ���
	u8 New_BaoJing;//�±���
	u8 End_BaoJing;//��������ı���״̬
}My_Picture;

typedef struct 
{
	u8 Dizhi;
	u8 PreAlarmValue;
	u8 AlarmValue;
	u8 NongDu;
	u16 DengState;
	u16 SaveAdd;
}My_TanCeQi;

typedef struct
{
	u8 TanCeQiDiZhi;//�����������в��������Ĵ�������ַ
	unsigned char CN_YBJ[33];//Ԥ���������ַ�
    unsigned char CN_BJ[33];//���������ַ�
	u8 BaoJingNian;//����ʱ����
	u8 BaoJingYue;//����ʱ����
	u8 BaoJingRi;//����ʱ����
	u8 BaoJingShi;//����ʱ��ʱ
	u8 BaoJingFen;//����ʱ���
	u8 BaoJingMiao;//����ʱ����
	u8 BaoJingLeiXin;//�������ͣ�1ΪԤ������2Ϊ����
}My_Alarm;

extern My_Picture LED_ZhuangTai[6];
extern u16 DangQianYeShu;
extern u16 ZongYeShu;
extern u16 DangQianYeShu_New;
extern u16 ZongYeShu_New;
/* Exported functions ------------------------------------------------------- */
void Display_Alarm_YeMa(void);
void DisplayNongDu(u8 Temp);
void Display_Alarm_XinXi(void);
void DuBaoJingZhuangTai(void) ;
void XianShi_New_BJ(u8 Temp);
#endif
