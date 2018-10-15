/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_BUTTON_EVENT_COMMON_H
#define __API_BUTTON_EVENT_COMMON_H


struct button_status {
	uint8_t flag_button_press;
	uint8_t flag_button_press_1_second;
	uint8_t flag_button_press_2_second;
	uint8_t flag_button_press_3_second;
	uint8_t flag_button_press_4_second;
	uint8_t flag_button_press_5_second;
	uint8_t flag_button_press_6_second;
	uint8_t flag_button_press_7_second;
	uint8_t flag_button_press_8_second;
	uint8_t flag_button_press_9_second;
	uint8_t flag_button_press_10_second;
	uint8_t flag_button_press_11_second;
	uint8_t flag_button_press_12_second;
	uint8_t flag_button_press_13_second;
	uint8_t flag_button_press_14_second;
	uint8_t flag_button_press_15_second;
	uint8_t flag_button_press_16_second;
	uint8_t flag_button_press_17_second;
	uint8_t flag_button_press_18_second;
	uint8_t flag_button_press_19_second;
	uint8_t flag_button_press_20_second;
	uint32_t value_get_timer;
};

               /*-----------API--------------*/
typedef uint32_t (*button_event_api_1)(struct device *Dev);
typedef int (*button_event_api_2)(struct device *Dev, struct button_status *Status);

struct button_event_common_api {
	button_event_api_1 get_press_time;
	button_event_api_2 get_press_status;
};


               /*-----------APP--------------*/
static inline int button_event_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline uint32_t button_get_press_time(struct device *Dev)
{
	const struct button_event_common_api *D_api = Dev->api;
	return D_api->get_press_time(Dev);
}

static inline int button_get_press_status(struct device *Dev, struct button_status *Status)
{
	const struct button_event_common_api *D_api = Dev->api;
	return D_api->get_press_status(Dev, Status);
}


#endif
