/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef BSP_CAN_H
#define BSP_CAN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"

/* Exported types ------------------------------------------------------------*/

/* Exported define -----------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
/* extern void BSP_CANs_Config(vu32 CANTxId);  // * @brief  initializes CAN1 and CAN2.
void CAN_RCC_Configuration(void);
void CAN_NVIC_Config(void);
void CAN_GPIO_Configuration(void);
void CAN_WorkModeConfig(void); */
void BSP_CAN_Config(void);
void CAN_Initialize(void);
void CAN_GPIO_Configuration(void);
void CAN_RCC_Configuration(void);
void CAN_NVIC_Config(void);
#endif
