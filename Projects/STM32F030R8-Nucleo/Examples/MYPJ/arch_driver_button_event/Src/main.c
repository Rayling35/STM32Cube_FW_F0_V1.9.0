/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f0xx_hal.h"
#include "cmsis_os.h"
#include "device.h"
#include "button_event_driver.h"
#include "api_button_event_common.h"
#include "main.h"


static struct button_status My_button_press_status;
static uint8_t button_click;

static void button_thread(const void *button_event)
{
	struct device *Button = (struct device *)button_event;
	button_click = 0;
	
	while(1) {
		button_get_press_status(Button, &My_button_press_status);
		if(My_button_press_status.flag_button_press) {
			while(1) {
				button_get_press_status(Button, &My_button_press_status);
				if(!My_button_press_status.flag_button_press) {
					button_click = 1;
					break;
				}
			}
		}
	}
}

static void main_thread(const void *argument)
{
	while(1) {
		if(button_click) {
			button_click = 0;
			printf("Button click\r\n");
		}
		if(My_button_press_status.flag_button_press_3_second) {
			printf("Button press 3 seconds\r\n");
		}
		if(My_button_press_status.flag_button_press_5_second) {
			printf("Button press 5 seconds\r\n");
		}
		if(My_button_press_status.flag_button_press_8_second) {
			printf("Button press 8 seconds\r\n");
		}
		if(My_button_press_status.flag_button_press_10_second) {
			printf("Button press 10 seconds\r\n");
		}
		if(My_button_press_status.flag_button_press_15_second) {
			printf("Button press 15 seconds\r\n");
		}
		if(My_button_press_status.flag_button_press_20_second) {
			printf("Button press 20 seconds\r\n");
		}
		if(My_button_press_status.flag_button_press_30_second) {
			printf("Button press 30 seconds\r\n");
		}
	}
}

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Button_event = button_event_device_binding();
	
	button_event_init(Button_event);
	printf("All device init\r\n");
	
	osThreadDef(main, main_thread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(main), NULL);
	
	osThreadDef(button, button_thread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(button), Button_event);
	
	osKernelStart();
	while(1) {
	}
}
