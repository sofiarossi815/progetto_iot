/*
 * DS1307.c
 *
 *  Created on: 20 giu 2024
 *      Author: Rossi
 */

// ##################################################
// #	 			INCLUDE
// ##################################################
#include "DS1307.h"

/****************************************************************************
 *                  Public Variable and Buffer Prototypes                   *
 ****************************************************************************/
//IIC
I2C_HandleTypeDef hi2cx;

/* I2C TIMING in Fast Mode */
__IO uint32_t timing = __LL_I2C_CONVERT_TIMINGS(0x01, 0x03, 0x02, 0x03, 0x09);



// ==================================================
// *	 	      	EXTERN 					*
// ==================================================

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	MX_I2Cx_Init  			x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/**
 * @brief I2Cx Initialization Function
 * @param None
 * @retval None
 */
void MX_I2Cx_Init(void){

	hi2cx.Instance = I2Cx;
	hi2cx.Init.Timing = timing;
	hi2cx.Init.OwnAddress1 = (0x1e*2);
	hi2cx.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2cx.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2cx.Init.OwnAddress2 = 0;
	hi2cx.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2cx.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2cx.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2cx) != HAL_OK)
	{
		//Error_Handler();
	}
	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2cx, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		//Error_Handler();
	}

	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2cx, 0) != HAL_OK)
	{
		//Error_Handler();
	}

}//EOR

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	HAL_I2C_MspInit 			x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/**
 * @brief I2C MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	if(hi2c->Instance==I2Cx)
	{
		__HAL_RCC_I2Cx_SCL_GPIO_CLK_ENABLE();
		__HAL_RCC_I2Cx_SDA_GPIO_CLK_ENABLE();

		GPIO_InitStruct.Pin = I2Cx_SCL_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = I2Cx_SCL_AF;
		HAL_GPIO_Init(I2Cx_SCL_PORT, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = I2Cx_SDA_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = I2Cx_SDA_AF;
		HAL_GPIO_Init(I2Cx_SDA_PORT, &GPIO_InitStruct);

		/* Peripheral clock enable */
		__HAL_RCC_I2Cx_CLK_ENABLE();

		/* I2Cx interrupt Init */
		HAL_NVIC_SetPriority(I2Cx_IRQn, IRQ_LOW_PRIORITY );
		HAL_NVIC_EnableIRQ(I2Cx_IRQn);
	}
}

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	HAL_I2C_MspDeInit 			x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/**
 * @brief I2C MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
	if(hi2c->Instance==I2Cx)
	{
		/* Peripheral clock disable */
		__HAL_RCC_I2Cx_CLK_DISABLE();

		HAL_GPIO_DeInit(I2Cx_SCL_PORT, I2Cx_SCL_PIN);
		HAL_GPIO_DeInit(I2Cx_SDA_PORT, I2Cx_SDA_PIN);

		/* I2Cx interrupt DeInit */
		HAL_NVIC_DisableIRQ(I2Cx_IRQn);
	}
}

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	I2C1_IRQHandler  				x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void I2C1_IRQHandler(void)
{
	__NOP();
}

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	HAL_I2C_MasterTxCpltCallback  	x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *I2cHandle)
{
	__NOP();
}


// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	Functions 						x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
uint8_t bcd2bin(uint8_t data){
 return ((data>>4)*10)+(data&0x0F);
}

uint8_t bin2bcd(uint8_t data){
	return ((data/10)<<4)|(data%10);
}

uint8_t rtc_read(uint8_t address)
{
	uint8_t data;

	if(HAL_I2C_Mem_Read(&hi2cx,addr_ds1307,address,I2C_MEMADD_SIZE_8BIT,&data,1,100)!=HAL_OK){
		_Error_Handler(__FILE__,__LINE__);
	}

	return data;
}

void rtc_write(uint8_t address, uint8_t data)
{
	if(HAL_I2C_Mem_Write(&hi2cx,addr_ds1307,address,I2C_MEMADD_SIZE_8BIT,&data,1,100)!=HAL_OK){
		//_Error_Handler(__FILE__,__LINE__);
	}
}

void rtc_init(uint8_t rs, uint8_t sqwe, uint8_t out)
{
	rs&=3;
	if (sqwe) rs|=0x10;
	if (out) rs|=0x80;

	rtc_write(0x07,rs);
}

void rtc_get_time(uint8_t *hour, uint8_t *min, uint8_t *sec)
{
	uint8_t data[3];
	if(HAL_I2C_Mem_Read(&hi2cx,addr_ds1307,0x00,I2C_MEMADD_SIZE_8BIT,data,3,1000)!=HAL_OK){
		//_Error_Handler(__FILE__,__LINE__);
	}

	*sec=bcd2bin(data[0]);
	*min=bcd2bin(data[1]);
	*hour=bcd2bin(data[2]);
}

void rtc_set_time(uint8_t hour, uint8_t min,uint8_t sec)
{
	uint8_t data[3]={bin2bcd(sec),bin2bcd(min),bin2bcd(hour)};
	if(HAL_I2C_Mem_Write(&hi2cx,addr_ds1307,0x00,I2C_MEMADD_SIZE_8BIT,data,3,1000)!=HAL_OK){
		//_Error_Handler(__FILE__,__LINE__);
	}
}

void rtc_get_date(uint8_t *week_day, uint8_t *day, uint8_t *month, uint8_t *year)
{
	uint8_t data[4]={0,0,0,0};
	if(HAL_I2C_Mem_Read(&hi2cx,addr_ds1307,0x03,I2C_MEMADD_SIZE_8BIT,data,4,1000)!=HAL_OK){
		//_Error_Handler(__FILE__,__LINE__);
	}

	*week_day=data[0];
	*day=bcd2bin(data[1]);
	*month=bcd2bin(data[2]);
	*year=bcd2bin(data[3]);
}

void rtc_set_date(uint8_t week_day, uint8_t day, uint8_t month, uint8_t year)
{
	uint8_t data[4]={week_day,bin2bcd(day),bin2bcd(month),bin2bcd(year)};
	if(HAL_I2C_Mem_Write(&hi2cx,addr_ds1307,0x03,I2C_MEMADD_SIZE_8BIT,data,4,1000)!=HAL_OK){
		//_Error_Handler(__FILE__,__LINE__);
	}
}

