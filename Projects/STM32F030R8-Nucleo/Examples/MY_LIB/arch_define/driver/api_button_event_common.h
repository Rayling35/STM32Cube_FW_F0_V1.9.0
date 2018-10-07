/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_BUTTON_EVENT_COMMON_H
#define __API_BUTTON_EVENT_COMMON_H


struct button_status {
	uint8_t flag_button_press;
	uint8_t flag_button_press_3_second;
	uint8_t flag_button_press_5_second;
	uint8_t flag_button_press_8_second;
	uint8_t flag_button_press_10_second;
	uint8_t flag_button_press_15_second;
	uint8_t flag_button_press_20_second;
	uint8_t flag_button_press_30_second;
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
