/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __PZ_LCD_DRIVER_H
#define __PZ_LCD_DRIVER_H


struct pz_lcd_data {
	struct device *ht1621;
};

struct device* pz_lcd_device_binding(void);


#endif
