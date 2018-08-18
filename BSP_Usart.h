/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef BSP_Usart_H
#define BSP_Usart_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"

/* Exported types ------------------------------------------------------------*/

/* Exported define -----------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define UART5_RECEIVE_DATE() GPIO_SetBits(GPIOD,GPIO_Pin_1)//
#define UART5_SEND_DATE() GPIO_ResetBits(GPIOD,GPIO_Pin_1)

#define BEEP_ON() GPIO_ResetBits(GPIOE,GPIO_Pin_15)
#define BEEP_OFF() GPIO_SetBits(GPIOE,GPIO_Pin_15)
/* Exported variables --------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
/* extern void BSP_Usarts_Config(vu32 UsartTxId);  // * @brief  initializes Usart1 and Usart2.
void Usart_RCC_Configuration(void);
void Usart_NVIC_Config(void);
void Usart_GPIO_Configuration(void);
void Usart_WorkModeConfig(void); */
void BSP_Usarts_Config(void);
void Usart_Initialize(void);
void Usart_GPIO_Configuration(void);
void Usart_RCC_Configuration(void);
void Usart_NVIC_Config(void);
#endif
