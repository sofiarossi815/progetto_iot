/*
 * pills.h
 *
 *  Created on: 23 lug 2024
 *      Author: rossi
 */

#ifndef INC_PILLS_H_
#define INC_PILLS_H_

#include <string.h>
#include <stdio.h>
#include "pwm.h"
#include "uart.h"
#include "rf_driver_hal_tim.h"
#include "vl53l1x.h"

#define NUM_CELLS 8

void GoToCell(int cell);
void ReturnToZero(void);
void OneStepRotation(void);
void OneCellRotation(void);
void CellsCheck(int cellarray[]);
void PillsCheck(void);


#endif /* INC_PILLS_H_ */
