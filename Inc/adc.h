// ##################################################
// #	Prj:	 xxx
// #	Autor:   Giuseppe Coviello	
// #	File:    adc.h
// #	Desc:			
// ##################################################
#ifndef ADC_H__
#define ADC_H__

// ##################################################
// #	 			INCLUDE	
// ##################################################
#include <string.h>
#include <stdio.h>
#include "util.h"
// ##################################################
// #				DEFINE
// ##################################################
#define USER_SAMPLERATE_MSB       (LL_ADC_SAMPLE_RATE_MSB_4)
#define USER_SAMPLERATE           (LL_ADC_SAMPLE_RATE_0)

#define USER_DATAWIDTH        (ADC_DS_DATA_WIDTH_16_BIT)
#define USER_RATIO            (ADC_DS_RATIO_128)
// ##################################################
// #				TYPE
// ##################################################
// ==================================================
// *	 	      	EXTERN 					*
// ==================================================
extern ADC_HandleTypeDef adc_handle;
extern ADC_ChannelConfTypeDef xChannel;
extern int8_t offset_vinp0;

extern uint32_t adc_value_raw;
extern float adc_value;
extern uint8_t is_adc_conversion_done;

// ==================================================
// *	 			PROTOTYPES					*
// ==================================================
void ADC_Init(void);
void MX_ADC_Init(void);
void ADC_Select_GenCh(void);
void ADC_Select_BattCh(void);
void ADC_Select_TempCh(void);
void ADC_internal_temperature(void);
void ADC_internal_battery(void);
void ADC_generic_channel(void);

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
#endif
