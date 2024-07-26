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

// Riporta il motore alla posizione originale
void ReturnToZero(){
	int stop = 0;
		while(stop == 0){
			HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_SET);
			HAL_Delay(2);
			HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_RESET);
			HAL_Delay(2);
			if (HAL_GPIO_ReadPin(STEPPER_ZERO_PORT, STEPPER_ZERO_PIN)==1){
				stop = 1;
			}
		}
}

// Rotazione 45°
void OneCellRotation(){
	for (int i = 0; i < 25; i++) {
		HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_SET);
		HAL_Delay(2);
		HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_RESET);
		HAL_Delay(2);
	}
}

// Controllo del contenuto di tutte le celle
int CellsCheck(cellarray){
	uint16_t distance;
	for (int i = 0; i < len(cellarray); i++) {
			OneCellRotation();
			distance = vl53l1x_getDistance();
			if (distance >= 5 && distance <= 30){
				cellarray[i] = 1;
			}
			else {
				cellarray[i] = 0;
			}
		}
	return cellarray;
}

