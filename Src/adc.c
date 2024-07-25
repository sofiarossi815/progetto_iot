// ##################################################
// #	Prj:	 xxx
// #	Autor:   Giuseppe Coviello	
// #	File:    adc.c
// #	Desc:			
// ##################################################

// ##################################################
// #	 			INCLUDE	
// ##################################################
#include "adc.h"


/****************************************************************************
 *                  Public Variable and Buffer Prototypes                   *
 ****************************************************************************/
ADC_HandleTypeDef adc_handle;
ADC_ChannelConfTypeDef xChannel;
int8_t offset_vinp0;

uint32_t adc_value_raw;
float adc_value;

uint8_t is_adc_conversion_done;
// ==================================================
// *	 	      	EXTERN 					*
// ==================================================


void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	/* Parameters for ADC initialization */
	__HAL_RCC_ADCDIG_CLK_ENABLE();
	__HAL_RCC_ADCANA_CLK_ENABLE();

	/* Configure ADC PINs */
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode  = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//  /* DMA controller clock enable */
	//  __HAL_RCC_DMA_CLK_ENABLE();
	//
	//  hdma_adc.Instance = DMA1_Channel1;
	//  hdma_adc.Init.Request = DMA_REQUEST_ADC_DS;
	//  hdma_adc.Init.Direction = DMA_PERIPH_TO_MEMORY;
	//  hdma_adc.Init.PeriphInc = DMA_PINC_DISABLE;
	//  hdma_adc.Init.MemInc = DMA_MINC_ENABLE;
	//  hdma_adc.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	//  hdma_adc.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	//  hdma_adc.Init.Mode = DMA_NORMAL;
	//  hdma_adc.Init.Priority = DMA_PRIORITY_LOW;
	//
	//  if(HAL_DMA_Init(&hdma_adc) != HAL_OK) {
	//    Error_Handler();
	//  }
	//
	//  __HAL_LINKDMA(hadc, DMA_Handle, hdma_adc);

}


/// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//// x		     	MX_ADC_Init  					x
//// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/* @brief ADC Initialization Function
 * @param None
 * @retval None
 */
void MX_ADC_Init(void)
{
	/* Enable the ADC peripheral */
	adc_handle.Instance = ADC;
	adc_handle.Init.DataRatio = USER_RATIO;
	adc_handle.Init.DataWidth = USER_DATAWIDTH;
	adc_handle.Init.InvertOutputBitMode = ADC_INVERT_OUTBIT_SING;
	adc_handle.Init.OverrunMode = ADC_NEW_DATA_IS_KEPT;
	adc_handle.Init.SampleRate = USER_SAMPLERATE;
	adc_handle.Init.SampleRateMsb = USER_SAMPLERATE_MSB;
	adc_handle.Init.SamplingMode = LL_ADC_SAMPLING_AT_END;
	adc_handle.Init.SequenceLength = ADC_SEQ_LEN_01;
	//adc_handle.DMA_Handle = &hdma_adc;

	if (HAL_ADC_Init(&adc_handle) != HAL_OK)
	{
		Error_Handler();
	}

	//Enable interrupt
	HAL_NVIC_EnableIRQ(ADC_IRQn);

}//EOR

/// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//// x		     	ADC_Select_GenCh  					x
//// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void ADC_Select_GenCh(void){

	/* Set the input channel */
	xChannel.ChannelType = ADC_CH_VINP0_TO_SINGLE_POSITIVE_INPUT;
	xChannel.SequenceNumber = ADC_SEQ_POS_01;
	xChannel.VoltRange = ADC_VIN_RANGE_3V6;
	if (HAL_ADC_ConfigChannel(&adc_handle, &xChannel)!= HAL_OK){
		Error_Handler();
	}//if

	/* Set the GAIN */
	if(LL_ADC_GET_CALIB_GAIN_FOR_VINPX_3V6() != 0xFFF){
		LL_ADC_SetCalibPoint1Gain(ADC, LL_ADC_GET_CALIB_GAIN_FOR_VINPX_3V6() );
		offset_vinp0 = LL_ADC_GET_CALIB_OFFSET_FOR_VINPX_3V6();
		LL_ADC_SetCalibPoint1Offset(ADC, offset_vinp0);
		offset_vinp0 = 0;
	}//if
	else{
		LL_ADC_SetCalibPoint1Gain(ADC, LL_ADC_DEFAULT_RANGE_VALUE_3V6);
	}//else
	LL_ADC_SetCalibPointForSinglePos3V6(ADC, LL_ADC_CALIB_POINT_1);

}//EOR

/// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//// x		     	ADC_Select_BattCh  					x
//// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void ADC_Select_BattCh(void){
	/* Set the input channe2 */
	xChannel.ChannelType = ADC_CH_BATTERY_LEVEL_DETECTOR;
	xChannel.SequenceNumber = ADC_SEQ_POS_01;
	if (HAL_ADC_ConfigChannel(&adc_handle, &xChannel)!= HAL_OK)
	{
		Error_Handler();
	}
}//EOR

/// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//// x		     	ADC_Select_TempCh  				  x
//// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void ADC_Select_TempCh(void){

	/* Set the input channe2 */
	xChannel.ChannelType = ADC_CH_TEMPERATURE_SENSOR;
	xChannel.SequenceNumber = ADC_SEQ_POS_01;
	xChannel.VoltRange = ADC_VIN_RANGE_1V2;
	if (HAL_ADC_ConfigChannel(&adc_handle, &xChannel)!= HAL_OK){
		Error_Handler();
	}//if
	LL_ADC_SetCalibPoint1Gain(ADC, LL_ADC_DEFAULT_RANGE_VALUE_1V2);
	LL_ADC_SetCalibPoint1Offset(ADC, 0xFF);

}//EOR



/// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//// x		     	ADC_internal_temperature  				  x
//// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void ADC_internal_temperature(void){

	ADC_Select_TempCh();
	//Interrupt
	is_adc_conversion_done=0;
	HAL_ADC_Start_IT(&adc_handle);
	while(!is_adc_conversion_done);	//wait forever..put a timeout
	HAL_ADC_Stop_IT(&adc_handle);
	//Polling
	//HAL_ADC_Start(&adc_handle);
	//HAL_ADC_PollForConversion(&adc_handle,5000);
	adc_value_raw=HAL_ADC_GetValue(&adc_handle);
	adc_value = (float)LL_ADC_GetADCConvertedValueTemp(adc_handle.Instance, adc_value_raw, USER_DATAWIDTH)/100;
	sprintf(app_buffer,"Internal temperature [degC] %d.%03d\r\n", PRINT_INT(adc_value),PRINT_FLOAT(adc_value));
	HAL_UART_Transmit(&huart1, app_buffer, strlen(app_buffer),1000);
}//EOR

/// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//// x		     	ADC_internal_battery  				  x
//// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void ADC_internal_battery(void){

	ADC_Select_BattCh();
	HAL_ADC_Start(&adc_handle);
	HAL_ADC_PollForConversion(&adc_handle,5000);
	adc_value_raw=HAL_ADC_GetValue(&adc_handle);
	adc_value = (float)LL_ADC_GetADCConvertedValueBatt(adc_handle.Instance, adc_value_raw, USER_DATAWIDTH, offset_vinp0);
	sprintf(app_buffer,"Battery voltage %d.%03d mV\r\n", PRINT_INT(adc_value),PRINT_FLOAT(adc_value));
	HAL_UART_Transmit(&huart1, app_buffer, strlen(app_buffer),1000);
}//EOR

/// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//// x		     	ADC_generic_channel
//// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void ADC_generic_channel(void){
	//
	ADC_Select_GenCh();
	HAL_ADC_Start(&adc_handle);
	HAL_ADC_PollForConversion(&adc_handle,5000);
	adc_value_raw=HAL_ADC_GetValue(&adc_handle);
	adc_value = (float)LL_ADC_GetADCConvertedValueSingle(adc_handle.Instance, adc_value_raw, LL_ADC_VIN_RANGE_3V6, USER_DATAWIDTH,offset_vinp0);
	sprintf(app_buffer,"ADC value PB3 %d.%03d mV\r\n", PRINT_INT(adc_value),PRINT_FLOAT(adc_value));
	HAL_UART_Transmit(&huart1, app_buffer, strlen(app_buffer),1000);
}//EOR


/// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//// x		     	ADC_IRQHandler		  x
//// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void ADC_IRQHandler(void) {
	HAL_ADC_IRQHandler(&adc_handle);
}//EOR


/// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//// x		     	HAL_ADC_ConvCpltCallback		  x
//// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc){
	is_adc_conversion_done=1;
}//EOR


/// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//// x		     	HAL_ADC_ErrorCallback    		  x
//// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
	/* Prevent unused argument(s) compilation warning */
	__NOP();
	UNUSED(hadc);


}//EOR



