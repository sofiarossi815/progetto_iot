// ##################################################
// #	Prj:	 xxx
// #	Autor:   Giuseppe Coviello	
// #	File:    uart.c
// #	Desc:			
// ##################################################

// ##################################################
// #	 			INCLUDE	
// ##################################################
#include "uart.h"


/****************************************************************************
 *                  Public Variable and Buffer Prototypes                   *
 ****************************************************************************/
UART_HandleTypeDef huart1;
// ==================================================
// *	 	      	EXTERN 					*
// ==================================================


// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	HAL_UART_MspInit  					x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
 * @brief UART MSP Initialization
 * This function configures the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	if(huart->Instance==USARTx)
	{
		/* Peripheral clock enable */
		EnableClock_USART();
		EnableClock_USART_TX_PORT();
		EnableClock_USART_RX_PORT();

		GPIO_InitStruct.Pin = USARTx_TX_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = USARTx_TX_AF;
		HAL_GPIO_Init(USARTx_TX_PORT, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = USARTx_RX_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = USARTx_RX_AF;
		HAL_GPIO_Init(USARTx_RX_PORT, &GPIO_InitStruct);

		/* USARTx interrupt Init */
		HAL_NVIC_SetPriority(USARTx_IRQn, IRQ_LOW_PRIORITY );
		HAL_NVIC_EnableIRQ(USARTx_IRQn);
	}
}

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	HAL_UART_MspDeInit  					x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/**
 * @brief USART MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param husart: USART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
	if(huart->Instance==USARTx)
	{
		/* Reset peripherals */
		__HAL_RCC_USART_FORCE_RESET();
		__HAL_RCC_USART_RELEASE_RESET();

		/* Peripheral clock disable */
		__HAL_RCC_USART_CLK_DISABLE();

		HAL_GPIO_DeInit(USARTx_TX_PORT, USARTx_TX_PIN);
		HAL_GPIO_DeInit(USARTx_RX_PORT, USARTx_RX_PIN);

		/* USARTx interrupt DeInit */
		HAL_NVIC_DisableIRQ(USARTx_IRQn);
	}
}


// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	MX_USARTx_UART_Init  			x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/**
 * @brief USARTx Initialization Function
 * @param None
 * @retval None
 */
void MX_USARTx_UART_Init(void)
{
	huart1.Instance = USARTx;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		//Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		//Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		//Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
	{
		//Error_Handler();
	}
}



// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	USARTx_IRQHandler			x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/**
 * @brief This function handles USART1 global interrupt.
 */
void USARTx_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart1);
}

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	HAL_UART_TxCpltCallback			x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/**
 * @brief  Tx Transfer completed callback
 * @param  UartHandle: UART handle.
 * @note   This example shows a simple way to report end of IT Tx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle){
	if(UartHandle->Instance==USART1){
		is_tx_finished=1;
	}//if
}//EOR

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	HAL_UART_RxCpltCallback  			x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/**
 * @brief  Rx Transfer completed callback
 * @param  UartHandle: UART handle
 * @note   This example shows a simple way to report end of IT Rx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle){
//	if(UartHandle->Instance==USART1){
//		__NOP();
//	}//if
//}//EOR

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	if(huart->Instance==USART1){
		rx_index++;
		if(rx_index>=UART_RX_BUFF_END){
			is_rx_finished=1;
			rx_index=0;
			rxbuffer_index=(rxbuffer_index+1)%2;
		}//if
		HAL_UART_Receive_IT(&huart1, &rxbuffer[rxbuffer_index][rx_index],1);
	}//if
}//EOR



// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	HAL_UART_ErrorCallback  			x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/**
 * @brief  UART error callback.
 * @param  huart UART handle.
 * @retval None
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
	/* Prevent unused argument(s) compilation warning */
	UNUSED(huart);

}//EOR


