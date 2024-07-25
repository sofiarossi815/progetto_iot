/*
 * Pills.c
 *
 *  Created on: 23 lug 2024
 *      Author: rossi
 */


// ##################################################
// #	 			INCLUDE
// ##################################################
#include <Pills.h>


/****************************************************************************
 *                  Public Variable and Buffer Prototypes                   *
 ****************************************************************************/

// ==================================================
// *	 	      	EXTERN 					*
// ==================================================


// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	Function  					    x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// Variables
uint8_t hour_pill = 18;
uint8_t min_pill = 20;
char allarme[32];
uint8_t hours_pill[5];



void allarm(hour,min){
	if (hour_pill == hour && min_pill == min ){
				if (HAL_TIM_PWM_Start(&htim_pwm, TIM_CHANNEL_1) != HAL_OK){
						/* PWM Generation Error */
						Error_Handler();
					}//if
				sprintf(allarme, "prendere pillola");
				HAL_UART_Transmit(&huart1, allarme, 32, 1000);
				HAL_Delay(1000);
				HAL_TIM_PWM_Stop(&htim_pwm, TIM_CHANNEL_1);
			}
}
