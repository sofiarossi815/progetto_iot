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

void ReturnToZero();
void OneStepRotation();
void OneCellRotation();
void CellsCheck();
void UntangleCable();
void PillsCheck();


#endif /* INC_PILLS_H_ */
