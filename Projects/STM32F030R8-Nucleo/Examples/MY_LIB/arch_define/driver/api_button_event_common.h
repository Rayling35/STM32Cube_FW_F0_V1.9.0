/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __BUTTON_EVENT_COMMON_API_H
#define __BUTTON_EVENT_COMMON_API_H


               /*-----------API--------------*/
typedef uint32_t (*button_event_api_1)(struct device *Dev);

struct button_event_common_api {
	button_event_api_1 get_press_time;
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


#endif
