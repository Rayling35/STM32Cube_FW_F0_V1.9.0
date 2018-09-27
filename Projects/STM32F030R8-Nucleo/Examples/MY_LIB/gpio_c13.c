/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "gpio_c13.h"
#include "api_define.h"


#ifdef C13_OUTPUT
static void gpio_c13_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PC13_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC13_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PC13_PORT, &GPIO_InitStruct);
}
#endif

#ifdef C13_INPUT
static void gpio_c13_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PC13_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC13_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PC13_PORT, &GPIO_InitStruct);
}
#endif

#ifdef C13_EXTI
static void gpio_c13_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PC13_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC13_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(PC13_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI4_15_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void EXTI4_15_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PC13_PIN);
}
#endif

static void gpio_c13_init(void)
{
	#ifdef C13_OUTPUT
	gpio_c13_output_init();
	#endif
	#ifdef C13_INPUT
	gpio_c13_input_init();
	#endif
	#ifdef C13_EXTI
	gpio_c13_exti_init();
	#endif
	printf("GPIO_C13 HAL init\r\n");
}

static int gpio_c13_read(void)
{
	return HAL_GPIO_ReadPin(PC13_PORT, PC13_PIN);
}

static void gpio_c13_write(uint16_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PC13_PORT, PC13_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PC13_PORT, PC13_PIN, GPIO_PIN_SET);
	}
}

static void gpio_c13_toggle_write(void)
{
	HAL_GPIO_TogglePin(PC13_PORT, PC13_PIN);
}

static int gpio_c13_lock(void)
{
	return HAL_GPIO_LockPin(PC13_PORT, PC13_PIN);
}

static struct gpio_api Gpio_c13_api = {
	.init         = gpio_c13_init,
	.read         = gpio_c13_read,
	.write        = gpio_c13_write,
	.toggle_write = gpio_c13_toggle_write,
	.lock         = gpio_c13_lock,
};

struct gpio_api* gpio_c13_binding(void)
{
	return &Gpio_c13_api;
}
