/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "gpio_a1.h"
#include "api_define.h"


#ifdef A1_OUTPUT
static void gpio_a1_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PA1_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA1_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PA1_PORT, &GPIO_InitStruct);
}
#endif

#ifdef A1_INPUT
static void gpio_a1_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA1_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA1_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PA1_PORT, &GPIO_InitStruct);
}
#endif

#ifdef A1_EXTI
static void gpio_a1_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA1_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA1_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(PA1_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI0_1_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
}

void EXTI0_1_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PA1_PIN);
}
#endif

static void gpio_a1_init(void)
{
	#ifdef A1_OUTPUT
	gpio_a1_output_init();
	#endif
	#ifdef A1_INPUT
	gpio_a1_input_init();
	#endif
	#ifdef A1_EXTI
	gpio_a1_exti_init();
	#endif
	printf("GPIO_A1 HAL init\r\n");
}

static int gpio_a1_read(void)
{
	return HAL_GPIO_ReadPin(PA1_PORT, PA1_PIN);
}

static void gpio_a1_write(uint8_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PA1_PORT, PA1_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PA1_PORT, PA1_PIN, GPIO_PIN_SET);
	}
}

static void gpio_a1_toggle_write(void)
{
	HAL_GPIO_TogglePin(PA1_PORT, PA1_PIN);
}

static int gpio_a1_lock(void)
{
	return HAL_GPIO_LockPin(PA1_PORT, PA1_PIN);
}

static struct gpio_api Gpio_a1_api = {
	.init         = gpio_a1_init,
	.read         = gpio_a1_read,
	.write        = gpio_a1_write,
	.toggle_write = gpio_a1_toggle_write,
	.lock         = gpio_a1_lock,
};

struct gpio_api* gpio_a1_binding(void)
{
	return &Gpio_a1_api;
}
