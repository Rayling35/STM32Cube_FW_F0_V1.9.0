/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f0xx_hal.h"
#include "gpio_a3.h"
#include "api_define.h"


#ifdef A3_OUTPUT
static void gpio_a3_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PA3_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA3_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PA3_PORT, &GPIO_InitStruct);
}
#endif

#ifdef A3_INPUT
static void gpio_a3_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA3_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA3_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(PA3_PORT, &GPIO_InitStruct);
}
#endif

#ifdef A3_EXTI
static void gpio_a3_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PA3_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PA3_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(PA3_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI2_3_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);
}

void EXTI2_3_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PA3_PIN);
}
#endif

static void gpio_a3_init(void)
{
	#ifdef A3_OUTPUT
	gpio_a3_output_init();
	#endif
	#ifdef A3_INPUT
	gpio_a3_input_init();
	#endif
	#ifdef A3_EXTI
	gpio_a3_exti_init();
	#endif
	printf("GPIO_A3 HAL init\r\n");
}

static int gpio_a3_read(void)
{
	return HAL_GPIO_ReadPin(PA3_PORT, PA3_PIN);
}

static void gpio_a3_write(uint8_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PA3_PORT, PA3_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PA3_PORT, PA3_PIN, GPIO_PIN_SET);
	}
}

static void gpio_a3_toggle_write(void)
{
	HAL_GPIO_TogglePin(PA3_PORT, PA3_PIN);
}

static int gpio_a3_lock(void)
{
	return HAL_GPIO_LockPin(PA3_PORT, PA3_PIN);
}

static struct gpio_api Gpio_a3_api = {
	.init         = gpio_a3_init,
	.read         = gpio_a3_read,
	.write        = gpio_a3_write,
	.toggle_write = gpio_a3_toggle_write,
	.lock         = gpio_a3_lock,
};

struct gpio_api* gpio_a3_binding(void)
{
	return &Gpio_a3_api;
}
