// ##################################################
// #	Prj:	 xxx
// #	Autor:   Giuseppe Coviello	
// #	File:    util.h
// #	Desc:			
// ##################################################
#ifndef UTIL_H__
#define UTIL_H__

// ##################################################
// #	 			INCLUDE	
// ##################################################
#include <string.h>
#include <stdio.h>
#include "rf_device_hal_conf.h"
#include "rf_driver_hal.h"
#include "rf_driver_ll_gpio.h"
#include "rf_driver_hal_tim.h"
#include "uart.h"


// ##################################################
// #				DEFINE
// ##################################################

//LED
#define LED_RED_PORT	GPIOB
#define LED_RED_PIN		GPIO_PIN_2	//GPIO_BSRR_BS2
#define LED_GREEN_PORT	GPIOB
#define LED_GREEN_PIN	GPIO_PIN_4	//GPIO_BSRR_BS4
#define BUZZER_PORT	GPIOB
#define BUZZER_PIN		GPIO_PIN_15	//GPIO_BSRR_BS1

//STEPPER
#define STEPPER_PASSO_PORT 	GPIOB
#define STEPPER_PASSO_PIN 	GPIO_PIN_14
#define STEPPER_RST_PORT 	GPIOB
#define STEPPER_RST_PIN		GPIO_PIN_15
#define STEPPER_DIR_PORT 	GPIOB
#define STEPPER_DIR_PIN		GPIO_PIN_2
#define STEPPER_ZERO_PORT   GPIOA
#define STEPPER_ZERO_PIN 	GPIO_PIN_10

//SW

#define SW2_PORT		GPIOB
#define SW2_PIN			GPIO_PIN_5	//GPIO_BSRR_BS5

#define ENABLE_GPIOB_IRQ 1
#define ENABLE_GPIOA_IRQ 1


//PWM
#define TIM_PWM				TIM2
#define EnableClock_TIM_PWM()              __HAL_RCC_TIM2_CLK_ENABLE()
#define DisableClock_TIM_PWM()             __HAL_RCC_TIM2_CLK_DISABLE()


//64MHz usually
#define OUTPUT_FREQ_HZ		1000000		//1MHz
#define PRESCALER_VALUE     (uint32_t)((HAL_TIM_GetPeriphClock(TIM_PWM) / OUTPUT_FREQ_HZ) - 1)

/* Initialize TIMx peripheral as follows:
   + Prescaler = (HAL_TIM_GetPeriphClock(htimx.Instance) / 1000000) - 1
   + Period = (41 - 1)
   + ClockDivision = 0
   + Counter direction = Up
*/
//custom
#define PERIOD_HZ			440
#define PERIOD_VALUE       (uint32_t)((OUTPUT_FREQ_HZ/PERIOD_HZ)-1)  /* Period Value  */


//#define  PERIOD_VALUE       (uint32_t)(40 - 1)  /* Period Value  */
#define  PULSE1_VALUE       (uint32_t)(PERIOD_VALUE*0.50)        /* Capture Compare 1 Value  */
#define  PULSE2_VALUE       (uint32_t)(PERIOD_VALUE*0.375)       /* Capture Compare 2 Value  */
#define  PULSE3_VALUE       (uint32_t)(PERIOD_VALUE*0.25)        /* Capture Compare 3 Value  */
#define  PULSE4_VALUE       (uint32_t)(PERIOD_VALUE*0.50)       /* Capture Compare 4 Value  */
//#define  PULSE4_VALUE       (uint32_t)(PERIOD_VALUE*0.125)       /* Capture Compare 4 Value  */
#define  PULSE5_VALUE       (uint32_t)(PERIOD_VALUE*0.75)        /* Capture Compare 3 Value  */
#define  PULSE6_VALUE       (uint32_t)(PERIOD_VALUE*0.625)       /* Capture Compare 4 Value  */

  /**TIM GPIO Configuration
  PB3 / AF2   ------> TIM17_CH1
  */
#define TIM_PWM_CH1_PIN                    GPIO_PIN_6
#define TIM_PWM_CH1_AF                     GPIO_AF4_TIM2
#define TIM_PWM_CH1_PORT                   GPIOB
/**TIMx GPIO Configuration
  PB5 / AF2   ------> TIM17_BKIN
  */
#define TIM_PWM_BKIN_PIN                 	LL_GPIO_PIN_7
#define TIM_PWM_BKIN_AF                  	LL_GPIO_AF_2
#define TIM_PWM_BKIN_PORT                	GPIOB


#define TIM_PWM_CH4_PIN                    GPIO_PIN_3
#define TIM_PWM_CH4_AF                     GPIO_AF3_TIM2
#define TIM_PWM_CH4_PORT                   GPIOB


// ##################################################
// #				MACRO
// ##################################################
#define PRINT_INT(x)    ((int)(x))
#define PRINT_FLOAT(x)  (x>0)? ((int) (((x) - PRINT_INT(x)) * 1000)) : (-1*(((int) (((x) - PRINT_INT(x)) * 1000))))
// ##################################################
// #				TYPE
// ##################################################
// ==================================================
// *	 	      	EXTERN 					*
// ==================================================

extern GPIO_InitTypeDef  GPIO_InitStruct;
extern EXTI_HandleTypeDef HEXTI_InitStructure_SW1;
extern EXTI_HandleTypeDef HEXTI_InitStructure_SW2;




extern volatile uint8_t is_pressed;

extern uint8_t app_buffer[100];			//buffer appoggio



// ==================================================
// *	 			PROTOTYPES					*
// ==================================================
//GPIO
void GPIO_Init_custom(void);
//PWM


//Handler
void GPIO_interupt_handler_custom(uint32_t pin);
void Error_Handler(void);
void ADC_IRQHandler(void);

#endif
