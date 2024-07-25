// ##################################################
// #	Prj:	 xxx
// #	Autor:   Giuseppe Coviello	
// #	File:    pwm.c
// #	Desc:			
// ##################################################

// ##################################################
// #	 			INCLUDE	
// ##################################################
#include "pwm.h"


/****************************************************************************
 *                  Public Variable and Buffer Prototypes                   *
 ****************************************************************************/
TIM_HandleTypeDef htim_pwm;
// ==================================================
// *	 	      	EXTERN 					*
// ==================================================


/// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//// x		     	MX_TIM_Init  					x
//// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/**
 * @brief TIM17 Initialization Function
 * @param None
 * @retval None
 */
void MX_TIM_Init(void)
{
	TIM_OC_InitTypeDef sConfigOC = {0};

	htim_pwm.Instance = TIM_PWM;
	htim_pwm.Init.Prescaler = PRESCALER_VALUE;
	htim_pwm.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim_pwm.Init.Period = PERIOD_VALUE;
	htim_pwm.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim_pwm.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_PWM_Init(&htim_pwm) != HAL_OK)
	{
		Error_Handler();
	}

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_SET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.Pulse = PULSE1_VALUE;
	if (HAL_TIM_PWM_ConfigChannel(&htim_pwm, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
#ifdef TIM_PWM_CH2_PIN
	sConfigOC.Pulse = PULSE2_VALUE;
	if (HAL_TIM_PWM_ConfigChannel(&htim_pwm, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
#endif
#ifdef TIM_PWM_CH3_PIN
	sConfigOC.Pulse = PULSE3_VALUE;
	if (HAL_TIM_PWM_ConfigChannel(&htim_pwm, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}
#endif
#ifdef TIM_PWM_CH4_PIN
	sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
	sConfigOC.Pulse = PULSE4_VALUE;
	if (HAL_TIM_PWM_ConfigChannel(&htim_pwm, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler();
	}
#endif
#ifdef TIM_PWM_CH5_PIN
	sConfigOC.Pulse = PULSE5_VALUE;
	if (HAL_TIM_PWM_ConfigChannel(&htim_pwm, &sConfigOC, TIM_CHANNEL_5) != HAL_OK)
	{
		Error_Handler();
	}
#endif
#ifdef TIM_PWM_CH6_PIN
	sConfigOC.Pulse = PULSE6_VALUE;
	if (HAL_TIM_PWM_ConfigChannel(&htim_pwm, &sConfigOC, TIM_CHANNEL_6) != HAL_OK)
	{
		Error_Handler();
	}
#endif

	//  TIM_BreakDeadTimeConfigTypeDef TIM_BDTRInitStruct = {0};
	//
	//  /* Configure the Break and Dead Time feature of the TIMx */
	//  TIM_BDTRInitStruct.OffStateRunMode = TIM_OSSR_ENABLE;
	//  TIM_BDTRInitStruct.OffStateIDLEMode = TIM_OSSI_ENABLE;
	//  TIM_BDTRInitStruct.LockLevel = TIM_LOCKLEVEL_1;
	//  TIM_BDTRInitStruct.DeadTime = __HAL_TIM_CALC_DEADTIME(HAL_TIM_GetPeriphClock(TIM_PWM), 0, 100);
	//  TIM_BDTRInitStruct.BreakState = TIM_BREAK_ENABLE;
	//  TIM_BDTRInitStruct.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	//  TIM_BDTRInitStruct.BreakFilter = TIM_BREAK_FILTER_FDIV1;
	//#ifdef TIM_BDTR_BKBID
	//  TIM_BDTRInitStruct.BreakAFMode = TIM_BREAK_AFMODE_INPUT;
	//#endif /* TIM_BDTR_BKBID */
	//#ifdef TIM_BREAK2_DISABLE
	//  TIM_BDTRInitStruct.Break2State = TIM_BREAK2_DISABLE;
	//#endif /* TIM_BREAK2_DISABLE */
	//#ifdef TIM_BREAK2POLARITY_HIGH
	//  TIM_BDTRInitStruct.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
	//#endif /* TIM_BREAK2POLARITY_HIGH */
	//#ifdef TIM_BREAK2_FILTER_FDIV1
	//  TIM_BDTRInitStruct.Break2Filter = TIM_BREAK2_FILTER_FDIV1;
	//#endif /* TIM_BREAK2_FILTER_FDIV1 */
	//  TIM_BDTRInitStruct.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;
	//HAL_TIMEx_ConfigBreakDeadTime(&htim_pwm, &TIM_BDTRInitStruct);


	HAL_TIM_MspPostInit(&htim_pwm);
}

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	HAL_TIM_PWM_MspInit  					x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
 * @brief TIM_PWM MSP Initialization
 * This function configures the hardware resources used in this example
 * @param htim_pwm: TIM_PWM handle pointer
 * @retval None
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{
	if(htim_pwm->Instance==TIM_PWM)
	{
		/* Peripheral clock enable */
		EnableClock_TIM_PWM();
	}
}
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	HAL_TIM_MspPostInit  					x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if(htim->Instance==TIM_PWM)
	{
		GPIO_InitStruct.Pin = TIM_PWM_CH1_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = TIM_PWM_CH1_AF;
		HAL_GPIO_Init(TIM_PWM_CH1_PORT, &GPIO_InitStruct);

#ifdef TIM_PWM_CH2_PIN
		GPIO_InitStruct.Pin = TIM_PWM_CH2_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = TIM_PWM_CH2_AF;
		HAL_GPIO_Init(TIM_PWM_CH2_PORT, &GPIO_InitStruct);
#endif

#ifdef TIM_PWM_CH3_PIN
		GPIO_InitStruct.Pin = TIM_PWM_CH3_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = TIM_PWM_CH3_AF;
		HAL_GPIO_Init(TIM_PWM_CH3_PORT, &GPIO_InitStruct);
#endif

#ifdef TIM_PWM_CH4_PIN
		GPIO_InitStruct.Pin = TIM_PWM_CH4_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = TIM_PWM_CH4_AF;
		HAL_GPIO_Init(TIM_PWM_CH4_PORT, &GPIO_InitStruct);
#endif

#ifdef TIM_PWM_CH5_PIN
		GPIO_InitStruct.Pin = TIM_PWM_CH5_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = TIM_PWM_CH5_AF;
		HAL_GPIO_Init(TIM_PWM_CH5_PORT, &GPIO_InitStruct);
#endif /* TIM_PWM_CH5_PIN */

#ifdef TIM_PWM_CH6_PIN
		GPIO_InitStruct.Pin = TIM_PWM_CH6_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = TIM_PWM_CH6_AF;
		HAL_GPIO_Init(TIM_PWM_CH6_PORT, &GPIO_InitStruct);
#endif /* TIM_PWM_CH6_PIN */

		//    GPIO_InitTypeDef GPIO_InitStruct = {0};
		//    GPIO_InitStruct.Pin = TIM_PWM_BKIN_PIN;
		//    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
		//    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
		//    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
		//    GPIO_InitStruct.Alternate = TIM_PWM_BKIN_AF;
		//    HAL_GPIO_Init(TIM_PWM_BKIN_PORT, &GPIO_InitStruct);


	}
}

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	HAL_TIM_PWM_MspDeInit  					x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/**
 * @brief TIM MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param htim: TIM handle pointer
 * @retval None
 */
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{
	if(htim_pwm->Instance==TIM_PWM)
	{
		/* Peripheral clock disable */
		DisableClock_TIM_PWM();
	}
}

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x		     	TIM2_IRQHandler  					x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void TIM2_IRQHandler(void){

	__NOP();
}//EOR


