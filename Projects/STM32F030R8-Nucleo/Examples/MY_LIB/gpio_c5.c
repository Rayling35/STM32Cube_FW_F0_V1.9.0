/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "gpio_c5.h"
#include "api_define.h"


#ifdef C5_OUTPUT
static void gpio_c5_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PC5_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC5_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PC5_PORT, &GPIO_InitStruct);
}
#endif

#ifdef C5_INPUT
static void gpio_c5_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PC5_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC5_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PC5_PORT, &GPIO_InitStruct);
}
#endif

#ifdef C5_EXTI
static void gpio_c5_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PC5_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC5_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(PC5_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PC5_PIN);
}
#endif

static void gpio_c5_init(void)
{
	#ifdef C5_OUTPUT
	gpio_c5_output_init();
	#endif
	#ifdef C5_INPUT
	gpio_c5_input_init();
	#endif
	#ifdef C5_EXTI
	gpio_c5_exti_init();
	#endif
	printf("GPIO_C5 HAL init\r\n");
}

static int gpio_c5_read(void)
{
	return HAL_GPIO_ReadPin(PC5_PORT, PC5_PIN);
}

static void gpio_c5_write(uint16_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PC5_PORT, PC5_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PC5_PORT, PC5_PIN, GPIO_PIN_SET);
	}
}

static void gpio_c5_toggle_write(void)
{
	HAL_GPIO_TogglePin(PC5_PORT, PC5_PIN);
}

static int gpio_c5_lock(void)
{
	return HAL_GPIO_LockPin(PC5_PORT, PC5_PIN);
}

static struct gpio_api gpio_c5_api = {
	.init         = gpio_c5_init,
	.read         = gpio_c5_read,
	.write        = gpio_c5_write,
	.toggle_write = gpio_c5_toggle_write,
	.lock         = gpio_c5_lock,
};

struct gpio_api* gpio_c5_binding(void)
{
	return &gpio_c5_api;
}
