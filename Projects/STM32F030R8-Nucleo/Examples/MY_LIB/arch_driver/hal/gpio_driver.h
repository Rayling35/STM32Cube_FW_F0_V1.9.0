/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_DRIVER_H
#define __GPIO_DRIVER_H


struct gpio_data {
	struct gpio_api *Gpio_hal;
};

#ifdef GPIO_A0_DEV
struct device* gpio_a0_device_binding(void);
#endif

#ifdef GPIO_A1_DEV
struct device* gpio_a1_device_binding(void);
#endif

#ifdef GPIO_A3_DEV
struct device* gpio_a3_device_binding(void);
#endif

#ifdef GPIO_A11_DEV
struct device* gpio_a11_device_binding(void);
#endif

#ifdef GPIO_B1_DEV
struct device* gpio_b1_device_binding(void);
#endif

#ifdef GPIO_B2_DEV
struct device* gpio_b2_device_binding(void);
#endif

#ifdef GPIO_C5_DEV
struct device* gpio_c5_device_binding(void);
#endif

#ifdef GPIO_C6_DEV
struct device* gpio_c6_device_binding(void);
#endif

#ifdef GPIO_C8_DEV
struct device* gpio_c8_device_binding(void);
#endif

#ifdef GPIO_C13_DEV
struct device* gpio_c13_device_binding(void);
#endif


#endif
