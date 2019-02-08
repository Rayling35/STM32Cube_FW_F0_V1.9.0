/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __ADD_DEFINE_H
#define __ADD_DEFINE_H


#define REG_BIT_SET(value, reg, set)  set == 1 ? SET_BIT(value, 1 << reg) : CLEAR_BIT(value, 1 << reg)
#define REG_BIT_FILL(value, reg, fill)  value | fill << reg


#endif
