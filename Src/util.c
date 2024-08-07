// ##################################################
// #	Prj:	 xxx
// #	Autor:   Giuseppe Coviello	
// #	File:    util.c
// #	Desc:			
// ##################################################

// ##################################################
// #	 			INCLUDE	
// ##################################################
#include "util.h"


/****************************************************************************
 *                  Public Variable and Buffer Prototypes                   *
 ****************************************************************************/
GPIO_InitTypeDef  GPIO_InitStruct;
//Exti
EXTI_HandleTypeDef HEXTI_InitStructure_SW1;
EXTI_HandleTypeDef HEXTI_InitStructure_SW2;

// ==================================================
// *	 	      	EXTERN 					*
// ==================================================


/// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//// x		     	GPIO_Init_custom  					x
//// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void GPIO_Init_custom(void){

	EXTI_ConfigTypeDef EXTI_Config_InitStructure = {0};

	//Clock enable
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	//for exti
	__HAL_RCC_SYSCFG_CLK_ENABLE();

    // Red Led
	GPIO_InitStruct.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pin=LED_RED_PIN;
	GPIO_InitStruct.Pull=GPIO_NOPULL;
	GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_RED_PORT,&GPIO_InitStruct);
	HAL_GPIO_WritePin(LED_RED_PORT, LED_RED_PIN, GPIO_PIN_SET);

	//Green LED
	GPIO_InitStruct.Pin=LED_GREEN_PIN;
	HAL_GPIO_Init(LED_GREEN_PORT,&GPIO_InitStruct);
	HAL_GPIO_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, GPIO_PIN_SET);

	//RGB LED
	GPIO_InitStruct.Pin = BUZZER_PIN;
	GPIO_InitStruct.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull=GPIO_PULLUP;
	GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);

	//Stepper Passo
	GPIO_InitStruct.Pin=STEPPER_PASSO_PIN;
	HAL_GPIO_Init(STEPPER_PASSO_PORT,&GPIO_InitStruct);
	HAL_GPIO_WritePin(STEPPER_PASSO_PORT, STEPPER_PASSO_PIN, GPIO_PIN_RESET);

	//Stepper Reset
	GPIO_InitStruct.Pin=STEPPER_RST_PIN;
	HAL_GPIO_Init(STEPPER_RST_PORT,&GPIO_InitStruct);
	HAL_GPIO_WritePin(STEPPER_RST_PORT, STEPPER_RST_PIN, GPIO_PIN_SET);

	//Stepper Reset
	GPIO_InitStruct.Pin=STEPPER_DIR_PIN;
	HAL_GPIO_Init(STEPPER_DIR_PORT,&GPIO_InitStruct);
	HAL_GPIO_WritePin(STEPPER_DIR_PORT, STEPPER_DIR_PIN, GPIO_PIN_RESET);

	GPIO_InitStruct.Pin = STEPPER_ZERO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    EXTI_Config_InitStructure.Line =    LL_EXTI_LINE_PA10;
	EXTI_Config_InitStructure.Trigger = EXTI_TRIGGER_RISING_EDGE;
	EXTI_Config_InitStructure.Type =    EXTI_TYPE_EDGE;

	HAL_EXTI_SetConfigLine(&HEXTI_InitStructure_SW1, &EXTI_Config_InitStructure);
	HAL_EXTI_RegisterCallback(&HEXTI_InitStructure_SW1, HAL_EXTI_COMMON_CB_ID, GPIO_interupt_handler_custom);
	HAL_EXTI_Cmd(&HEXTI_InitStructure_SW1 , ENABLE);

	HAL_EXTI_ClearPending(&HEXTI_InitStructure_SW1);

	/* Enable and set line 10 Interrupt to the lowest priority */
	HAL_NVIC_SetPriority(GPIOA_IRQn, IRQ_LOW_PRIORITY );
	HAL_NVIC_EnableIRQ(GPIOA_IRQn);


	//SW2
	GPIO_InitStruct.Mode=GPIO_MODE_INPUT;
	GPIO_InitStruct.Pin=SW2_PIN;
	GPIO_InitStruct.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(SW2_PORT,&GPIO_InitStruct);

	EXTI_Config_InitStructure.Line =    LL_EXTI_LINE_PB5;
	EXTI_Config_InitStructure.Trigger = EXTI_TRIGGER_RISING_EDGE;
	EXTI_Config_InitStructure.Type =    EXTI_TYPE_EDGE;

	HAL_EXTI_SetConfigLine(&HEXTI_InitStructure_SW2, &EXTI_Config_InitStructure);
	HAL_EXTI_RegisterCallback(&HEXTI_InitStructure_SW2, HAL_EXTI_COMMON_CB_ID, GPIO_interupt_handler_custom);
	HAL_EXTI_Cmd(&HEXTI_InitStructure_SW2 , ENABLE);

	HAL_EXTI_ClearPending(&HEXTI_InitStructure_SW2);

	/* Enable and set line 5 Interrupt to the lowest priority */
	HAL_NVIC_SetPriority(GPIOB_IRQn, IRQ_LOW_PRIORITY );
	HAL_NVIC_EnableIRQ(GPIOB_IRQn);

}//EOR



// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	HAL_MspInit  					x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/**
 * Initializes the Global MSP.
 */
void HAL_MspInit(void)
{
	/* System interrupt init*/
	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, IRQ_LOW_PRIORITY );
}
//


// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	GPIO_interupt_handler_custom  			x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void GPIO_interupt_handler_custom(uint32_t pin){

}//EOR



// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	Error_Handler  			x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* User can add his own implementation to report the HAL error return state */
	while(1);
}//EOR

