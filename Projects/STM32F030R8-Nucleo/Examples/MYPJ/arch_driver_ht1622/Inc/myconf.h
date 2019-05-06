/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __MYCONF_H
#define __MYCONF_H

#include "gpio_a0.h"
#include "gpio_a1.h"
#include "gpio_b1.h"


#define HT1622_CS_OUTPUT_LOW        A0_OUTPUT_LOW()
#define HT1622_CS_OUTPUT_HIGH       A0_OUTPUT_HIGH()
#define HT1622_WR_OUTPUT_LOW        A1_OUTPUT_LOW()
#define HT1622_WR_OUTPUT_HIGH       A1_OUTPUT_HIGH()
#define HT1622_DATA_OUTPUT_LOW      B1_OUTPUT_LOW()
#define HT1622_DATA_OUTPUT_HIGH     B1_OUTPUT_HIGH()


#endif
