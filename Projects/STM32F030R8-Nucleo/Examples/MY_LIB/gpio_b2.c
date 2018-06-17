/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "gpio_b2.h"
#include "api_define.h"


#ifdef B2_OUTPUT
static void gpio_b2_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PB2_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PB2_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PB2_PORT, &GPIO_InitStruct);
}
#endif

#ifdef B2_INPUT
static void gpio_b2_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PB2_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PB2_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PB2_PORT, &GPIO_InitStruct);
}
#endif

#ifdef B2_EXTI
static void gpio_b2_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PB2_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PB2_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(PB2_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI4_15_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void EXTI4_15_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PB2_PIN);
}
#endif

static void gpio_b2_init(void)
{
	#ifdef B2_OUTPUT
	gpio_b2_output_init();
	#endif
	#ifdef B2_INPUT
	gpio_b2_input_init();
	#endif
	#ifdef B2_EXTI
	gpio_b2_exti_init();
	#endif
	printf("GPIO_B2 HAL init\r\n");
}

static int gpio_b2_read(void)
{
	return HAL_GPIO_ReadPin(PB2_PORT, PB2_PIN);
}

static void gpio_b2_write(uint16_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PB2_PORT, PB2_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PB2_PORT, PB2_PIN, GPIO_PIN_SET);
	}
}

static void gpio_b2_toggle_write(void)
{
	HAL_GPIO_TogglePin(PB2_PORT, PB2_PIN);
}

static int gpio_b2_lock(void)
{
	return HAL_GPIO_LockPin(PB2_PORT, PB2_PIN);
}

static struct gpio_api gpio_b2_api = {
	.init         = gpio_b2_init,
	.read         = gpio_b2_read,
	.write        = gpio_b2_write,
	.toggle_write = gpio_b2_toggle_write,
	.lock         = gpio_b2_lock,
};

struct gpio_api* gpio_b2_binding(void)
{
	return &gpio_b2_api;
}
