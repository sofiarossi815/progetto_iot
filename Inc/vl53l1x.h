/**
 *****************************************************************************
 * @file	vl53l1x.h
 * @author 	Arnaud C.
 *****************************************************************************
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef INC_VL53L1X_H_
#define INC_VL53L1X_H_

/* Includes -----------------------------------------------------------------*/
#include <stdint.h>
#include "VL53L1X_api.h"
#include "VL53l1X_calibration.h"
#include "vl53l1_error_codes.h"

/* Exported types -----------------------------------------------------------*/

/* End of exported types ----------------------------------------------------*/

/* Exported macros ----------------------------------------------------------*/
#define VL53L1X_MAX_NB	16
#define VL53L1X_DEFAULT_ADDRESS (0x29 << 1)

/* End of exported macros ---------------------------------------------------*/

/* Exported functions -------------------------------------------------------*/
int vl53l1x_init();
int vl53l1x_clearCfg();
int vl53l1x_setParameters();
uint16_t vl53l1x_getDistance();

/* End of exported functions ------------------------------------------------*/

#endif /* INC_VL53L1X_H_ */
