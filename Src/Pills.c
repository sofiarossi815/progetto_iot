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

static int currentCell = 0; // può essere modificato solo in questo file

// Funzione che permette di andare alla cella numero cell
void GoToCell(int cell) {
	if(cell == 0) {
		ReturnToZero();
		return;
	}

	if(cell < currentCell) {
		ReturnToZero();
	}
	int numRotations = cell - currentCell;
	for(int i = 0; i < numRotations; i++) {
		OneCellRotation();
	}
}

// Esegue il controllo della cella e se questa è piena fa suonare l'allarme per un minuto
void PillsCheck(void){
	uint16_t distance = vl53l1x_getDistance();
//	sprintf(allarme, "DISTANCE: %d\n\r", distance);
//	HAL_UART_Transmit(&huart1, allarme, 32, 1000);
	HAL_Delay(1000);
	if (distance >= 0 && distance < 24){
		if (HAL_TIM_PWM_Start(&htim_pwm, TIM_CHANNEL_1) != HAL_OK){
			/* PWM Generation Error */
			Error_Handler();
		}//if
		HAL_UART_Transmit(&huart1, "Take pills\n", 12, 1000);
		HAL_Delay(1000);
		HAL_TIM_PWM_Stop(&htim_pwm, TIM_CHANNEL_1);
	}

}

// Riporta il motore alla posizione originale
void ReturnToZero(void){
	int stop = 0;
	// Invertiamo il senso di rotazione in modo tale da sbrogliare il cavo del sensore ToF
	HAL_GPIO_WritePin(STEPPER_DIR_PORT, STEPPER_DIR_PIN, GPIO_PIN_SET);
	HAL_Delay(2);
	while(stop == 0){
		HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_SET);
		HAL_Delay(10);
		HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_RESET);
		HAL_Delay(100);
		if (HAL_GPIO_ReadPin(STEPPER_ZERO_PORT, STEPPER_ZERO_PIN)==1){
						stop = 1;
		}
	}
	OneStepRotation();
	// Dopo essere tornato alla cella 0 imposta a 0 currentCell
	currentCell = 0;
	HAL_GPIO_WritePin(STEPPER_DIR_PORT, STEPPER_DIR_PIN, GPIO_PIN_RESET);
	HAL_Delay(2);
}

// Esegue una rotazione di 1.8°
void OneStepRotation(void) {
	HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_RESET);
	HAL_Delay(10);
}

// Rotazione 45°
void OneCellRotation(void){
	// Siamo già sull'ultima cella. Non ruotare!
	// L'unico modo per tornare alla cella 0 è il return to zero
	if(currentCell == NUM_CELLS - 1) {
		return;
	}

	for (int j = 0; j < 25; j++) {
		OneStepRotation();
	}
	// Aggiorna il valore della cella corrente
	currentCell++;
}

// Controlla il contenuto di tutte le celle
void CellsCheck(int cellarray[]){
	char str[32];
	uint16_t distance;
	for (int i = 1; i < NUM_CELLS; i++) {
		OneCellRotation();
		HAL_Delay(3000);
		distance = vl53l1x_getDistance();
		HAL_Delay(1000);
		sprintf(str, "DISTANCE: %d\n", distance);
		HAL_UART_Transmit(&huart1, str, 32, 1000);
		if (distance >= 0 && distance < 24){
			cellarray[i] = 1;
		}
		else {
			cellarray[i] = 0;
		}
	HAL_Delay(1000);
	}
}


