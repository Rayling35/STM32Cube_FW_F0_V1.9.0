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


static void main_thread(const void *Button_event)
{
	struct device *Button = (struct device *)Button_event;
	struct button_status Button_status;
	uint32_t press_time;
	
	while(1) {
		press_time = button_get_press_time(Button);
		if(press_time) {
			printf("press time %d\r\n", press_time);
		}
		
		button_get_push_status(Button, &Button_status);
		if(Button_status.flag_push) {
			printf("Button push\r\n");
		}
		if(Button_status.flag_press_3_second) {
			printf("Button press 3 seconds\r\n");
		}
		if(Button_status.flag_press_5_second) {
			printf("Button press 5 seconds\r\n");
		}
		if(Button_status.flag_press_8_second) {
			printf("Button press 8 seconds\r\n");
		}
		if(Button_status.flag_press_10_second) {
			printf("Button press 10 seconds\r\n");
		}
		if(Button_status.flag_press_15_second) {
			printf("Button press 15 seconds\r\n");
		}
		if(Button_status.flag_press_20_second) {
			printf("Button press 20 seconds\r\n");
		}
		if(Button_status.flag_press_30_second) {
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
	osThreadCreate(osThread(main), Button_event);
	
	osKernelStart();
	while(1) {
	}
}
