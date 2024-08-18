/**
 *****************************************************************************
 * @file	vl53l1x.c
 * @author 	Arnaud C.
 *****************************************************************************
 */

#include "vl53l1x.h"

/* Variables ----------------------------------------------------------------*/
uint8_t status = 0;

/* End of variables ---------------------------------------------------------*/

/* Functions ----------------------------------------------------------------*/

/**
 * vl53l1x_init: sensors initialization
 * @return 0 if succeeded
 */
int vl53l1x_init()
{
//	printf("\r\n");
//	printf("Initialization started for %d vl53l1x sensor(s)\r\n", nb_sensors);

	// Clear library configuration
	if(vl53l1x_clearCfg() != 0){
		return -1;
	}
//	printf("VL53L1X library configuration cleared...\r\n");

	// Initialization
	uint8_t sensorState = 0;
	uint8_t byteData; uint16_t wordData;

	// Retrieve sensor informations
	status = VL53L1_RdByte(VL53L1X_DEFAULT_ADDRESS, 0x010F, &byteData);
//	printf("VL53L1X Model_ID[%d]: %X\r\n", j, byteData);
	status = VL53L1_RdByte(VL53L1X_DEFAULT_ADDRESS, 0x0110, &byteData);
//	printf("VL53L1X Module_Type[%d]: %X\r\n", j, byteData);
	status = VL53L1_RdWord(VL53L1X_DEFAULT_ADDRESS, 0x010F, &wordData);
//	printf("VL53L1X[%d]: %X\r\n", j, wordData);

	// Retrieve sensor boot state
	uint8_t attempts = 10; // 2.5 sec timeout
	while(sensorState == 0 && attempts > 0){
		status = VL53L1X_BootState(VL53L1X_DEFAULT_ADDRESS, &sensorState);
		HAL_Delay(250);
		attempts--;
	}

	if(sensorState == 0) {
		// Failed to boot the sensor
		return -1;
	}

//	printf("Chip booted...\r\n");

	// Sensor init
	status = VL53L1X_SensorInit(VL53L1X_DEFAULT_ADDRESS);

	HAL_Delay(250);

	// Set new i2c address
	if((status = VL53L1X_SetI2CAddress(VL53L1X_DEFAULT_ADDRESS, 0x52)) == VL53L1_ERROR_NONE){
//		printf("tof[%d] -> new i2c addr: 0x%2X\r\n", j, tof[j].i2c_address);
	}

	/* TO DO: Understand why incrementing i2c addresses one by one does not work. */

	HAL_Delay(250);

	// Set sensor parameters
	if((status = vl53l1x_setParameters()) != VL53L1_ERROR_NONE){
		return -1;
	}
//	printf("vl53l1x parameters set...\r\n");

//	printf("\r\n");
	HAL_Delay(250);

	// Start ranging
	if((status = VL53L1X_StartRanging(VL53L1X_DEFAULT_ADDRESS)) == VL53L1_ERROR_NONE){
//		printf("vl53l1x[%d] started...\r\n", k);
	}
	HAL_Delay(250);


	return 0;
}

/**
 * vl53l1x_clearCfg: clear lib config structure
 * @return 0
 */
int vl53l1x_clearCfg()
{
	status = 0;

	return 0;
}


/**
 * vl53l1x_setParameters: set sensor parameters
 * @param i sensor index
 * @return status
 */
int vl53l1x_setParameters()
{
	status = VL53L1X_SetDistanceMode(VL53L1X_DEFAULT_ADDRESS, 1); // 1=short, 2=long
	status = VL53L1X_SetInterMeasurementInMs(VL53L1X_DEFAULT_ADDRESS, 200); // in ms, IM must be > = TB
	status = VL53L1X_SetTimingBudgetInMs(VL53L1X_DEFAULT_ADDRESS, 200); // in ms possible values [20, 50, 100, 200, 500]
	//status = VL53L1X_SetDistanceThreshold(VL53L1X_DEFAULT_ADDRESS, 500, 10, 1, 0); // config sympa
	//status = VL53L1X_SetROI(VL53L1X_DEFAULT_ADDRESS, 16, 16); // minimum ROI 4,4

	//status = VL53L1X_SetOffset(VL53L1X_DEFAULT_ADDRESS, 20); // offset compensation in mm
	//status = VL53L1X_CalibrateOffset(dev, 140, &offset); // may take few second to perform the offset cal
	//status = VL53L1X_CalibrateXtalk(dev, 1000, &xtalk); // may take few second to perform the xtalk cal

	return status;
}

/**
 * vl53l1x_getDistance: get distance value
 * @return distance
 */
uint16_t vl53l1x_getDistance(){
	uint16_t distance = 0;

	if((status = VL53L1X_GetDistance(VL53L1X_DEFAULT_ADDRESS, &distance)) != VL53L1_ERROR_NONE){
//		printf("VL53L1X_GetDistance failed...\r\n");
	}

	if((status = VL53L1X_ClearInterrupt(VL53L1X_DEFAULT_ADDRESS)) != VL53L1_ERROR_NONE){
//		printf("VL53L1X_ClearInterrupt failed...\r\n");
		return -1;
	}

	return distance;
}

/* End of functions ---------------------------------------------------------*/
