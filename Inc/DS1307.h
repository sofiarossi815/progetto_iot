/*
 * DS1307.h
 *
 *  Created on: 20 giu 2024
 *      Author: rossi
 */

#ifndef INC_DS1307_H_
#define INC_DS1307_H_


#include <string.h>
#include <stdio.h>
#include "util.h"
#include "rf_driver_ll_i2c.h"
#include "rf_driver_hal_i2c.h"


// ##################################################
// #				DEFINE
// ##################################################
//IIC
#define SENSOR_BUS_DS1307 								hi2cx
#define I2Cx                                            I2C1
#define I2Cx_SCL_PORT                                   GPIOA
#define I2Cx_SCL_PIN                                    GPIO_PIN_0
#define I2Cx_SCL_AF                                     GPIO_AF0_I2C1
#define I2Cx_SDA_PORT                                   GPIOB
#define I2Cx_SDA_PIN                                    GPIO_PIN_7
#define I2Cx_SDA_AF                                     GPIO_AF0_I2C1
#define __HAL_RCC_I2Cx_CLK_ENABLE                       __HAL_RCC_I2C1_CLK_ENABLE
#define __HAL_RCC_I2Cx_CLK_DISABLE                      __HAL_RCC_I2C1_CLK_DISABLE
#define __HAL_RCC_I2Cx_SCL_GPIO_CLK_ENABLE              __HAL_RCC_GPIOA_CLK_ENABLE
#define __HAL_RCC_I2Cx_SDA_GPIO_CLK_ENABLE              __HAL_RCC_GPIOB_CLK_ENABLE
#define I2Cx_IRQn                                       I2C1_IRQn
#define I2Cx_IRQHandler                                 I2C1_IRQHandler

#define BOOT_TIME_DS1307        5 //ms
#define TX_BUF_DIM_DS1307		100
#define addr_ds1307 (uint16_t)0b11010000 // 1101000 | 0 <- Write enable

// ##################################################
// #				TYPE
// ##################################################
// ==================================================
// *	 	      	EXTERN 					*
// ==================================================

extern I2C_HandleTypeDef hi2cx;
extern char tx_buffer_DS1307[TX_BUF_DIM_DS1307];


// ==================================================
// *	 			PROTOTYPES					*
// ==================================================

uint8_t bcd2bin(uint8_t data);
uint8_t bin2bcd(uint8_t data);
uint8_t rtc_read(uint8_t address);

//IIC
void MX_I2Cx_Init(void);

void rtc_write(uint8_t address, uint8_t data);
void rtc_init(uint8_t rs, uint8_t sqwe, uint8_t out);
void rtc_get_time(uint8_t *hour, uint8_t *min, uint8_t *sec);
void rtc_set_time(uint8_t hour, uint8_t min, uint8_t sec);
void rtc_get_date(uint8_t *week_day, uint8_t *day, uint8_t *month, uint8_t *year);
void rtc_set_date(uint8_t week_day, uint8_t day, uint8_t month, uint8_t year);

#endif /* INC_DS1307_H_ */
