/******************** (C) COPYRIGHT 2021 STMicroelectronics ********************
 * File Name         : project_main.c
 * Author            : RF Application team
 * Version           : 1.0.0
 * Date              : 27-October-2021
 * Description       : File generated by the IO Mapper tool
 ********************************************************************************
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "bluenrg_lps_it.h"
#include "ble_const.h"

#include "rf_driver_hal_power_manager.h"
#include "rf_driver_hal_vtimer.h"
#include "bluenrg_lp_stack.h"
#include "bluenrg_lp_evb_com.h"
#include "bleplat.h"
#include "nvm_db.h"
#include "osal.h"
#include "user.h"
#include "pka_manager.h"
#include "rng_manager.h"
#include "aes_manager.h"
#include "ble_controller.h"
#include "User_config.h"
#include "bluenrg_lps_hw_config.h"

#include "rf_driver_hal.h"
#include "DS1307.h"
#include "vl53l1x.h"
#include "uart.h"
#include "pwm.h"
#include "adc.h"
#include "Pills.h"

#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif


/* Private includes ----------------------------------------------------------*/
#include "util.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BLE_USER_VERSION_STRING /"1.0.0/"
/* Private macro -------------------------------------------------------------*/
NO_INIT(uint32_t dyn_alloc_a[DYNAMIC_MEMORY_SIZE>>2]);
/* Private variables ---------------------------------------------------------*/

volatile uint8_t is_pressed;
uint8_t rxbuffer[2][UART_RX_BUFF_LEN];
uint8_t rxbuffer_index;
uint16_t rx_index;
uint8_t is_rx_finished;
uint8_t is_tx_finished;

uint8_t app_buffer[100];			//buffer appoggio

WakeupSourceConfig_TypeDef WakeupSourceConfig = {0};


// Variables DS1307
uint8_t sec, min, hour;
uint8_t week_day, day, month, year;
char str[32];
uint8_t rec;

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

void ModulesInit(void)
{
	uint8_t ret;

	BLE_STACK_InitTypeDef BLE_STACK_InitParams = BLE_STACK_INIT_PARAMETERS;

	LL_AHB_EnableClock(LL_AHB_PERIPH_PKA|LL_AHB_PERIPH_RNG);

	/* BlueNRG-LP stack init */
	ret = BLE_STACK_Init(&BLE_STACK_InitParams);
	if (ret != BLE_STATUS_SUCCESS)
	{
		printf("Error in BLE_STACK_Init() 0x%02x\r\n", ret);
		while(1);
	}

	BLECNTR_InitGlobal();

	HAL_VTIMER_InitType VTIMER_InitStruct = {HS_STARTUP_TIME, INITIAL_CALIBRATION, CALIBRATION_INTERVAL};
	HAL_VTIMER_Init(&VTIMER_InitStruct);
	BLEPLAT_Init();


	if (PKAMGR_Init() == PKAMGR_ERROR)
	{
		while(1);
	}

	if (RNGMGR_Init() != RNGMGR_SUCCESS)
	{
		while(1);
	}

	/* Init the AES block */
	AESMGR_Init();
}

void ModulesTick(void)
{

	/* Timer tick */
	HAL_VTIMER_Tick();

	/* Bluetooth stack tick */
	BLE_STACK_Tick();

	/* NVM manager tick */
	NVMDB_Tick();

}


/* User callback if an interrupt is associated to the wakeup source */
void HAL_PWR_MNGR_WakeupIOCallback(uint32_t source)
{
}



/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	PowerSaveLevels stopLevel;
	volatile GPIO_PinState pin_SW1;

	/* System initialization function */
	if (SystemInit(SYSCLK_64M, BLE_SYSCLK_32M) != SUCCESS) {
		/* Error during system clock configuration take appropriate action */
		while(1);
	}

	bluenrg_lp_initialization();

	WakeupSourceConfig.RTC_enable = 0;
	WakeupSourceConfig.LPU_enable = 0;

	/* Init BLE stack, HAL virtual timer and NVM modules */
	ModulesInit();

	/*NOTE: In order to generate an user-friendly C code and helping user on his coding post-build activities,
      the generated BLE stack APIs are placed within some predefined C functions (device_initialization(), set_database(), device_scanning(), 
      set_device_discoverable(), set_connection(), set_connection_update(), discovery(), read_write_characteristics() and update_characterists()).

      Once C code has been generated, user can move and modify APIs sequence order, within and outside these default user functions, 
      according to his specific needs.
	 */
	/* Init the Bluetooth LE stack layers */
	device_initialization();

	//Init customs
	HAL_Init();
	GPIO_Init_custom();

	/* BlueNRG-LP stack tick */
	ModulesTick();

	/* Application Tick */
	APP_Tick();

	HAL_MspInit();
	GPIO_Init_custom();
	MX_USARTx_UART_Init();
	MX_TIM_Init();
	MX_ADC_Init();
	//IIC

	MX_I2Cx_Init();
	rtc_init(0, 1, 0);
	rtc_set_time(18, 18, 30);
	rtc_set_date(4, 20, 6, 24);

	HAL_Delay(1000);

	//Inizializza il VL53L1X
	if (vl53l1x_init() != VL53L1_ERROR_NONE){
		if(HAL_UART_Transmit(&huart1, (uint8_t*)"VL53L1X Init Failed\r\n", strlen("VL53L1X Init Failed\r\n"),1000)!= HAL_OK){
				/* Transfer error in transmission process */
				Error_Handler();
			}//if
	}

	//Init variables
	rx_index=0;
	is_rx_finished=0;
	rxbuffer_index=0;

	/* Start PWM signals generation */
	/* Start channel 1 */
//	if (HAL_TIM_PWM_Start(&htim_pwm, TIM_CHANNEL_1) != HAL_OK){
//		/* PWM Generation Error */
//		Error_Handler();
//	}//if
	if (HAL_TIM_PWM_Start(&htim_pwm, TIM_CHANNEL_4) != HAL_OK){
		/* PWM Generation Error */
		Error_Handler();
	}//if
	//while (1);

	while (1) {

		/* Power Save Request */
		//HAL_PWR_MNGR_Request(POWER_SAVE_LEVEL_CPU_HALT, WakeupSourceConfig, &stopLevel);

//		__HAL_TIM_SET_COMPARE(&htim_pwm, TIM_CHANNEL_4, 500);
//		HAL_Delay(2);

		// RTC PRINT DATE TIME
		rtc_get_time(&hour, &min, &sec);
		rtc_get_date(&week_day,&day,&month,&year);
		sprintf(str, "TIME %02d:%02d:%02d\n\r", hour, min, sec);
		HAL_UART_Transmit(&huart1, str, 32, 1000);
		sprintf(str, "DATE: %02d/%02d/%02d\n\r", day, month, year);
		HAL_UART_Transmit(&huart1, str, 32, 1000);
		// END RTC

		//
		HAL_Delay(100);
		uint16_t distance = vl53l1x_getDistance();
		sprintf(str, "DISTANCE: %d\n\r", distance);
		HAL_UART_Transmit(&huart1, str, 32, 1000);

		allarm(hour,min);
		HAL_Delay(1000);
	}//while

}//EOR




/******************************************************************************/
/*   USER IRQ HANDLER TREATMENT                                               */
/******************************************************************************/

PowerSaveLevels App_PowerSaveLevel_Check(PowerSaveLevels level)
{
	if(BSP_COM_TxFifoNotEmpty() || BSP_COM_UARTBusy())
		return POWER_SAVE_LEVEL_RUNNING;
	return POWER_SAVE_LEVEL_STOP_NOTIMER;
}

/* Hardware Error event. 
   This event is used to notify the Host that a hardware failure has occurred in the Controller. 
   Hardware_Code Values:
   - 0x01: Radio state error
   - 0x02: Timer overrun error
   - 0x03: Internal queue overflow error
   - 0x04: Late Radio ISR
    After this event with error code 0x01, 0x02 or 0x03, it is recommended to force a device reset.
 */


/**
 * @brief  Hardware Error event
 * @param  uint8_t Hardware_Code.
 * @retval void.
 */
void hci_hardware_error_event(uint8_t Hardware_Code)
{

	if (Hardware_Code <= 0x03)
	{
		NVIC_SystemReset();
	}
}


/**
 * This event is generated to report firmware error informations.
 * FW_Error_Type possible values:
 * Values:
  - 0x01: L2CAP recombination failure
  - 0x02: GATT unexpected response
  - 0x03: GATT unexpected request
    After this event with error type (0x01, 0x02, 0x3) it is recommended to disconnect. 
 */
void aci_hal_fw_error_event(uint8_t FW_Error_Type,
		uint8_t Data_Length,
		uint8_t Data[])
{
	if (FW_Error_Type <= 0x03)
	{
		uint16_t connHandle;

		/* Data field is the connection handle where error has occurred */
		connHandle = LE_TO_HOST_16(Data);

		aci_gap_terminate(connHandle, BLE_ERROR_TERMINATED_REMOTE_USER);
	}
}


#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{ 
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
