/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef BSP_Timers_H
#define BSP_Timers_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"

/* Exported types ------------------------------------------------------------*/

/* Exported define -----------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
/* extern void BSP_Timerss_Config(vu32 TimersTxId);  // * @brief  initializes Timers1 and Timers2.
void Timers_RCC_Configuration(void);
void Timers_NVIC_Config(void);
void Timers_GPIO_Configuration(void);
void Timers_WorkModeConfig(void); */
void BSP_Timers_Config(void);
void Timers_Initialize(void);
void Timers_GPIO_Configuration(void);
void Timers_RCC_Configuration(void);
void Timers_NVIC_Config(void);
#endif
