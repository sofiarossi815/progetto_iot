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
void CellsCheck(int  cellarray[]){
	char str[32];
	uint16_t distance;
	for (int i = 0; i < 8; i++) {
			OneCellRotation();
			HAL_Delay(2000);
			distance = vl53l1x_getDistance();
			HAL_Delay(1000);
			sprintf(str, "DISTANCE: %d\n\r", distance);
			HAL_UART_Transmit(&huart1, str, 32, 1000);
			if (distance >= 1 && distance <= 40){
				cellarray[i] = 1;
			}
			else {
				cellarray[i] = 0;
			}
		HAL_Delay(1000);
		}
}

void UntangleCable(){
	HAL_GPIO_WritePin(STEPPER_DIR_PORT, STEPPER_DIR_PIN, GPIO_PIN_SET);
	HAL_Delay(2);
	for (int i = 0; i < 200; i++) {
		HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_SET);
		HAL_Delay(2);
		HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_RESET);
		HAL_Delay(2);
	}
	HAL_GPIO_WritePin(STEPPER_DIR_PORT, STEPPER_DIR_PIN, GPIO_PIN_RESET);
	HAL_Delay(2);
}
