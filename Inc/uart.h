// ##################################################
// #	Prj:	 xxx
// #	Autor:   Giuseppe Coviello	
// #	File:    uart.h
// #	Desc:			
// ##################################################
#ifndef UART_H__
#define UART_H__

// ##################################################
// #	 			INCLUDE	
// ##################################################
#include <string.h>
#include <stdio.h>
#include "util.h"
// ##################################################
// #				DEFINE
// ##################################################
//USART
#define USARTx                             USART1
#define USARTx_IRQn                        USART1_IRQn
#define USARTx_IRQHandler                  USART1_IRQHandler

#define USARTx_TX_PIN                      GPIO_PIN_1
#define USARTx_TX_PORT                     GPIOA
#define USARTx_TX_AF                       GPIO_AF2_USART1
#define USARTx_RX_PIN                      GPIO_PIN_0
#define USARTx_RX_PORT                     GPIOB
#define USARTx_RX_AF                       GPIO_AF0_USART1
#define EnableClock_USART()                __HAL_RCC_USART_CLK_ENABLE()
#define DisableClock_USART()               __HAL_RCC_USART_CLK_DISABLE()
#define EnableClock_USART_TX_PORT()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define EnableClock_USART_RX_PORT()        __HAL_RCC_GPIOA_CLK_ENABLE()


#define UART_RX_BUFF_LEN	100
#define UART_RX_BUFF_END	10

// ##################################################
// #				TYPE
// ##################################################
// ==================================================
// *	 	      	EXTERN 					*
// ==================================================
extern UART_HandleTypeDef huart1;
extern uint8_t rxbuffer[2][UART_RX_BUFF_LEN];
extern uint8_t rxbuffer_index;
extern uint16_t rx_index;
extern uint8_t is_rx_finished;
extern uint8_t is_tx_finished;

// ==================================================
// *	 			PROTOTYPES					*
// ==================================================
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void MX_USARTx_UART_Init(void);

#endif
