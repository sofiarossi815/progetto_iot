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
char allarme[32];

// Esegue il controllo della cella e se questa è piena fa suonare l'allarme per un minuto
void PillsCheck(){
	uint16_t distance = vl53l1x_getDistance();
//	sprintf(allarme, "DISTANCE: %d\n\r", distance);
//	HAL_UART_Transmit(&huart1, allarme, 32, 1000);
	HAL_Delay(1000);
	if (distance == 0 && distance <= 32){
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
	int i = 0;
	int stop = 0;
	while(stop == 0){
		HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_SET);
		HAL_Delay(10);
		HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_RESET);
		HAL_Delay(100);
		if (HAL_GPIO_ReadPin(STEPPER_ZERO_PORT, STEPPER_ZERO_PIN)==1){
						stop = 1;
		}
		i = i+1;
		if (i == 200 || i == 400 || i == 600){
			UntangleCable();
		}
	}
	OneStepRotation();
}

// Esegue una rotazione di 1.8°
void OneStepRotation() {
	HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_RESET);
	HAL_Delay(10);
}

// Rotazione 45°
void OneCellRotation(){
	for (int j = 0; j < 25; j++) {
		OneStepRotation();
	}
}

// Controlla il contenuto di tutte le celle
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
			if (distance >= 0 && distance <= 32){
				cellarray[i] = 1;
			}
			else {
				cellarray[i] = 0;
			}
		HAL_Delay(1000);
		}
}

// Inverte il verso di rotazione del motore ed esegue un giro completo
void UntangleCable(){
	HAL_GPIO_WritePin(STEPPER_DIR_PORT, STEPPER_DIR_PIN, GPIO_PIN_SET);
	HAL_Delay(2);
	for (int i = 0; i < 200; i++) {
		HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_SET);
		HAL_Delay(7);
		HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_RESET);
		HAL_Delay(7);
	}
	HAL_GPIO_WritePin(STEPPER_DIR_PORT, STEPPER_DIR_PIN, GPIO_PIN_RESET);
	HAL_Delay(2);
}

