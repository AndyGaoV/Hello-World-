/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef BSP_ID_H
#define BSP_ID_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"

/* Exported types ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define IN1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define IN2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define IN3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define IN4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)
#define IN5 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)
#define IN6 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define IN7 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)
#define IN8 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)

#define Out1_H() GPIO_SetBits(GPIOC,GPIO_Pin_6)
#define Out2_H() GPIO_SetBits(GPIOC,GPIO_Pin_7)
#define Out3_H() GPIO_SetBits(GPIOC,GPIO_Pin_8)
#define Out4_H() GPIO_SetBits(GPIOC,GPIO_Pin_9)

#define Out1_L() GPIO_ResetBits(GPIOC,GPIO_Pin_6)
#define Out2_L() GPIO_ResetBits(GPIOC,GPIO_Pin_7)
#define Out3_L() GPIO_ResetBits(GPIOC,GPIO_Pin_8)
#define Out4_L() GPIO_ResetBits(GPIOC,GPIO_Pin_9)

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern u8 shuru_queren[7];
/* Exported functions ------------------------------------------------------- */
void BSP_DeviceIDInit(void);
void DuKaiGuanLiangShuRu(void);
u8 ScanLocalAddress(void); //É¨Ãè±¾»úµØÖ·
void KongZhi_JDQ(void);
#endif
