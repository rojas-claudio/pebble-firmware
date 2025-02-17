#pragma once

#include "applib/graphics/gcolor_definitions.h"
#include "applib/graphics/gtypes.h"
#include <stdint.h>

void system_theme_set(GColor8 s_new_theme);
void menu_theme_set(GColor8 s_new_theme);
void timeline_future_theme_set(GColor8 s_new_theme);

GColor8 system_theme_get(void);
GColor8 menu_theme_get(void);
GColor8 timeline_future_theme_get(void);