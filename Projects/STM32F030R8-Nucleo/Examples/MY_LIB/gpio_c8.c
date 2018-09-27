/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "gpio_c8.h"
#include "api_define.h"


#ifdef C8_OUTPUT
static void gpio_c8_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PC8_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC8_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PC8_PORT, &GPIO_InitStruct);
}
#endif

#ifdef C8_INPUT
static void gpio_c8_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PC8_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC8_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PC8_PORT, &GPIO_InitStruct);
}
#endif

#ifdef C8_EXTI
static void gpio_c8_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PC8_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PC8_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(PC8_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI4_15_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void EXTI4_15_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PC8_PIN);
}
#endif

static void gpio_c8_init(void)
{
	#ifdef C8_OUTPUT
	gpio_c8_output_init();
	#endif
	#ifdef C8_INPUT
	gpio_c8_input_init();
	#endif
	#ifdef C8_EXTI
	gpio_c8_exti_init();
	#endif
	printf("GPIO_C8 HAL init\r\n");
}

static int gpio_c8_read(void)
{
	return HAL_GPIO_ReadPin(PC8_PORT, PC8_PIN);
}

static void gpio_c8_write(uint16_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PC8_PORT, PC8_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PC8_PORT, PC8_PIN, GPIO_PIN_SET);
	}
}

static void gpio_c8_toggle_write(void)
{
	HAL_GPIO_TogglePin(PC8_PORT, PC8_PIN);
}

static int gpio_c8_lock(void)
{
	return HAL_GPIO_LockPin(PC8_PORT, PC8_PIN);
}

static struct gpio_api Gpio_c8_api = {
	.init         = gpio_c8_init,
	.read         = gpio_c8_read,
	.write        = gpio_c8_write,
	.toggle_write = gpio_c8_toggle_write,
	.lock         = gpio_c8_lock,
};

struct gpio_api* gpio_c8_binding(void)
{
	return &Gpio_c8_api;
}
