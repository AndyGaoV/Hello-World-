/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef BSP_Display_H
#define BSP_Display_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "BSP_RTC.h"
#include "main.h"
/* Exported types ------------------------------------------------------------*/
typedef struct 
{
	u8 SaveDiZhi;
	u8 State;
	ttime time;
}My_Type;
/* Exported define -----------------------------------------------------------*/
/* #ifdef Display_GLOBALS
#define Display_EXT
#else
#define Display_EXT extern
#endif  */
#define CursorOn 0x01
#define CursorOff 0x00
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern u8 Command[35];

void DisplayAdjustBright(u8 BrightPwm);
void DisplaySetTouch(void);
void DisplayClearWordArea(u16 WordAreaNum);
void DisplayCursorAtDesignatedSpot(u8 CursorState,u16 X,u16 Y);
void DisplayWord(u16 WordAreaNum,u16 num,u16 num2);
void DisplayBaoJingWord(u16 WordAreaNum,u8 *Word);
void DisplayPictureAtDesignatedSpot(u16 PictureNum,u16 X,u16 Y);
void DisplayFirstPicture(u16 PictureNum);
void DisplaySendCommand(u8 SendCount);
void DisplayClearAll(void);
void DisplaySystemTime(u16 WordAreaNum,ttime Dis_time);
void DisplayTime(u16 WordAreaNum,ttime Dis_time);
void BeiGuangZiDongKongZhi(u8 PWMON,u8 PWMOFF,u8 PWMTime);

#endif
