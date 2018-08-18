/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef MAIN_H
#define MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "BSP_CAN.h"
#include "BSP_Usart.h"
#include "BSP_Timers.h"
#include "Usart_Handlle.h"
#include "BSP_Display.h"
#include "DisplayHandle.h"
#include "BSP_RTC.h"
#include "BSP_ID.h"
#include "CAN_Handle.h"
//#include <stdio.h>
/* Exported types ------------------------------------------------------------*/

/* Exported define -----------------------------------------------------------*/
/******************触控配置编号设置*******************/
/*0 所有界面共同拥有的 */
#define Key_YanShenBJ 0x01
#define Key_hujiao 0x02
#define Key_zhiban 0x03
#define Key_TiaoGuang 0x05
#define Key_ZhongYinQieHuan 0x07
/*1 欢迎界面 */

/*2 报警点设置界面 */
#define Key_QingKongBaoJing 0x19
/*3 延伸报警界面 */
#define Key_BaoJingSheZhi 0x08
#define Key_ShiShiLiShi 0x09
#define Key_ShangFan 0x0b
#define Key_XiaFan 0x0c
#define Key_XiaoYin 0x0d
/*4 轮机员呼叫界面 */
#define Key_LunJiZhang 0x0e
#define Key_DaGuanLun 0x0f
#define Key_ErGuanLun 0x10
#define Key_SanGuanLun 0x11
#define Key_DianJiYuan 0x12
#define Key_CanTing 0x13
#define Key_HuiYiShi 0x14
#define Key_QunHu 0x15
#define Key_JiKongShi 0x16
#define Key_BenDiZhiBan 0x77
/*5 轮机员值班界面 */
/*6 安全报警界面 */
#define Key_KaiQi 0x17
#define Key_FuWei 0x18
/******触控配置编号设置——完***********/

/******************图片编号设置*******************/
#define Tu_BaoJingSheZhi 0x01
#define Tu_YanSheShiShi_CN 0x02
#define Tu_YanSheLiShi_CN 0x03
#define Tu_YanSheShiShi_EN 0x04
#define Tu_YanSheLiShi_EN 0x05
#define Tu_HuJiao_CN 0x08
#define Tu_HuJiao_EN 0x09
#define Tu_ZhiBan_CN 0x0a
#define Tu_ZhiBan_EN 0x0b
/*****************图片编号设置——完*************/

/******************图标设置*******************/

/*****************图标设置设置——完*************/

/******************程序分段编号设置*******************/

/*****************程序分段编号设置——完*************/

#define Flash 0x02
#define Liang 0x01
#define Mie 0x00
#define OldFlash 0x03

#define ZhuJi 0x80
#define GuangBo 0x00
#define LunJIZhang 0x01
#define DaGuanLun 0x02
#define CanTing 0x04
#define JiaKongTai 0x08

#define ZhuJieMian 0x00
#define BaoJingChaXun 0x01
#define SheZhi 0x02
#define MiMaJieMian	0x04

#define YingDa 0xff
#define LiangDu_DaiJi 5
#define ShiJian_DaiJi 30

#define TongXunGuZhang_ShiJian 20
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
void ReciTouchDate(void);
#endif

