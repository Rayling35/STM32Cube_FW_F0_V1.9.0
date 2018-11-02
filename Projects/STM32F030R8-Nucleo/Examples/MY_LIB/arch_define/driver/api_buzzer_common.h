/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_BUZZER_COMMON_H
#define __API_BUZZER_COMMON_H


               /*-----------API--------------*/
typedef int (*buzzer_api_1)(struct device *Dev, uint16_t frequency, uint8_t volume);

struct buzzer_common_api {
	buzzer_api_1 output;
};


               /*-----------APP--------------*/
static inline int buzzer_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline int buzzer_output(struct device *Dev, uint16_t frequency, uint8_t volume)
{
	const struct buzzer_common_api *D_api = Dev->api;
	return D_api->output(Dev, frequency, volume);
}


#endif
