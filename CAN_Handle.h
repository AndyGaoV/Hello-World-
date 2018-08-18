/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef CAN_Handle_H
#define CAN_Handle_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "Usart_Handlle.h"
#include "BSP_ID.h"
/* Exported types ------------------------------------------------------------*/

/* Exported define -----------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
typedef union
{
	struct 
	{
		unsigned DangQianZhen:5;
		unsigned ZhenZongShu:4;
		unsigned MingLing:4;
		unsigned MuDiDiZhi:8;
		unsigned YuanDiZhi:8;
	unsigned :3;
	}Item;
	u32 IDValue;
}CANTxID;
extern u8 BaoChun_shezhizhi[9];
/* Exported functions ------------------------------------------------------- */
void CAN_AdjustTime(ttime *time);
void CAN_SendAlarm(u8 num);
void CAN_MessageSend(void);
void CAN_Com(void);
#endif
