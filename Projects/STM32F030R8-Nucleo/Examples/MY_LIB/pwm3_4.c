/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "pwm3_4.h"
#include "api_define.h"


TIM_HandleTypeDef TimHandle3;

static void _PWM3_4_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	TIM3_CHANNEL4_CLK_ENABLE();
	
	GPIO_InitStruct.Pin       = TIM3_CHANNEL4_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = TIM3_CHANNEL4_AF;
	HAL_GPIO_Init(TIM3_CHANNEL4_PORT, &GPIO_InitStruct);
	
	TIM3_CLK_ENABLE();
}

static void pwm3_4_init(void)
{
	_PWM3_4_MspInit();
	printf("PWM3_4 HAL init\r\n");
}

static int pwm3_4_pin_set(uint32_t period_cycles, uint32_t pulse_cycles, uint32_t prescaler)
{
	TIM_OC_InitTypeDef sConfig;
	
	TimHandle3.Instance               = TIM3;
	TimHandle3.Init.Prescaler         = prescaler;
	TimHandle3.Init.CounterMode       = TIM_COUNTERMODE_UP;
	TimHandle3.Init.Period            = period_cycles;
	TimHandle3.Init.ClockDivision     = 0;
	TimHandle3.Init.RepetitionCounter = 0;
	TimHandle3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_PWM_Init(&TimHandle3);
	
	sConfig.OCMode       = TIM_OCMODE_PWM1;
	sConfig.Pulse        = pulse_cycles;
	sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
	sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
	sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;
	sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	HAL_TIM_PWM_ConfigChannel(&TimHandle3, &sConfig, TIM3_CHANNEL4);
	
	return HAL_TIM_PWM_Start(&TimHandle3, TIM3_CHANNEL4);
}

static struct pwm_api Pwm3_4_api = {
	.init    = pwm3_4_init,
	.pin_set = pwm3_4_pin_set,
};

struct pwm_api* pwm3_4_binding(void)
{
	return &Pwm3_4_api;
}
