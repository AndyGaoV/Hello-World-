/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef Usart_Handlle_H
#define Usart_Handlle_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "Usart_Handlle.h"
#include "BSP_ID.h"
#include "main.h"
/* Exported types ------------------------------------------------------------*/

/* Exported define -----------------------------------------------------------*/
//#define BJGeShu 64  //不包括通讯故障报警是192条



/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
void ReciTouchDate(void);
void SaveDate(void);
void SaveAlarm(u8 WeiZhi);
#endif
