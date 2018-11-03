/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "pwm1_2.h"
#include "api_define.h"


TIM_HandleTypeDef TimHandle1_2;

static void _PWM1_2_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	TIM1_CHANNEL2_CLK_ENABLE();
	
	GPIO_InitStruct.Pin       = TIM1_CHANNEL2_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = TIM1_CHANNEL2_AF;
	HAL_GPIO_Init(TIM1_CHANNEL2_PORT, &GPIO_InitStruct);
	
	TIM1_CLK_ENABLE();
}

static void pwm1_2_init(void)
{
	_PWM1_2_MspInit();
	printf("PWM1_2 HAL init\r\n");
}

static int pwm1_2_pin_set(uint32_t period_cycles, uint32_t pulse_cycles, uint32_t prescaler)
{
	TIM_OC_InitTypeDef sConfig;
	
	TimHandle1_2.Instance               = TIM1;
	TimHandle1_2.Init.Prescaler         = prescaler;
	TimHandle1_2.Init.CounterMode       = TIM_COUNTERMODE_UP;
	TimHandle1_2.Init.Period            = period_cycles;
	TimHandle1_2.Init.ClockDivision     = 0;
	TimHandle1_2.Init.RepetitionCounter = 0;
	TimHandle1_2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_PWM_Init(&TimHandle1_2);
	
	sConfig.OCMode       = TIM_OCMODE_PWM1;
	sConfig.Pulse        = pulse_cycles;
	sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
	sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
	sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;
	sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	HAL_TIM_PWM_ConfigChannel(&TimHandle1_2, &sConfig, TIM1_CHANNEL2);
	
	return HAL_TIM_PWM_Start(&TimHandle1_2, TIM1_CHANNEL2);
}

static struct pwm_api Pwm1_2_api = {
	.init    = pwm1_2_init,
	.pin_set = pwm1_2_pin_set,
};

struct pwm_api* pwm1_2_binding(void)
{
	return &Pwm1_2_api;
}
