/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef BSP_RTC_H
#define BSP_RTC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"

/* Exported types ------------------------------------------------------------*/
 typedef struct
{
	u8 yearh;
	u8 yearl;
	u8 month;
	u8 day;
	u8 hour;
	u8 minute;
	u8 second ;
} 	ttime ; 

/* Exported define -----------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define SCL_0() GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define SCL_1() GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define SDA_0() GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define SDA_1() GPIO_SetBits(GPIOB,GPIO_Pin_9)

#define SCL2_0() GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define SCL2_1() GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define SDA2_0() GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define SDA2_1() GPIO_SetBits(GPIOB,GPIO_Pin_7)
/* Exported variables --------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
/* extern void BSP_RTCs_Config(vu32 TimersTxId);  // * @brief  initializes Timers1 and Timers2.
void Timers_RCC_Configuration(void);
void Timers_NVIC_Config(void);
void Timers_GPIO_Configuration(void);
void Timers_WorkModeConfig(void); */
extern ttime RTC_SystemTime;
void BSP_RTC_Config(void);
FlagStatus init_1307( void );
u8 rbyte_1307( u8  adr);
void write_time(void);
void  read_time(ttime *time);
void SendSystemTimeASCII(void);
u8 read_24256data( u16  adr ) ;
void write_24256data( u16 adr, u8 num);
void QingChu_24256data(u16 adr, u8 num,u16 ii);
#endif
