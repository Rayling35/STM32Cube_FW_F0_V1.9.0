/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __EEYE_LCD_DRIVER_H
#define __EEYE_LCD_DRIVER_H


enum seg7_eeye {
	SEG_1  = 0,
	SEG_2  = 2,
	SEG_3  = 4,
	SEG_4  = 6,
	SEG_5  = 8,
	SEG_6  = 10,
	SEG_7  = 12,
	SEG_8  = 14,
	SEG_9  = 46,
	SEG_10 = 44,
	SEG_11 = 42,
	SEG_12 = 40,
	SEG_13 = 38,
	SEG_14 = 36,
	SEG_15 = 34,
	SEG_16 = 32,
	SEG_17 = 50,
	SEG_18 = 16,
	SEG_19 = 18,
	SEG_20 = 20,
	SEG_21 = 22,
	SEG_22 = 24,
	SEG_23 = 26,
	SEG_24 = 28,
	SEG_25 = 30,
};

struct eeye_lcd_data {
	struct device *Ht1622;
};

struct device* eeye_lcd_device_binding(void);


#endif
