/*
    Service for changing system colors. 

    -> Settings do not persist after a reboot. Need to figure that out
    -> Only option right now is Global/System Theme, which affects Launcher and TL Future

*/


#include "services/common/system_theme.h"
#include "applib/graphics/gcolor_definitions.h"
#include "applib/graphics/gtypes.h"

#include <stdio.h>
#include <stdint.h>

#if PBL_COLOR

static GColor8 s_system_theme = GColorVividCerulean;
static GColor8 s_menu_theme = GColorVividCerulean;
static GColor8 s_timeline_future_theme = GColorVividCerulean;

// typedef enum ThemeType {
//     GlobalTheme,
//     MenuTheme,
//     TimelineFutureTheme,
// } ThemeType;

// typedef enum ThemeColors {
//     GColorVividCerulean,
//     GColorLavenderIndigo,
//     GColorScreaminGreen,
// } ThemeColors;

// char[20] theme_name_get

void system_theme_set(GColor8 s_new_theme) {
    s_system_theme = s_new_theme;
    s_menu_theme = s_new_theme;
    s_timeline_future_theme = s_new_theme;
}

void menu_theme_set(GColor8 s_new_theme) {
    s_menu_theme = s_new_theme;
}

void timeline_future_theme_set(GColor8 s_new_theme) {
    s_timeline_future_theme = s_new_theme;
}

GColor8 system_theme_get(void) {
    return s_system_theme;
}

GColor8 menu_theme_get(void) {
    return s_menu_theme;
}

GColor8 timeline_future_theme_get(void) {
    return s_timeline_future_theme;
}

#else

// void system_theme_set(GColor8 s_new_theme) {
//     //Do nothing. Device doesn't have a color display.
// }

// GColor8 system_theme_get(void) {
//     //Do nothing. Device doesn't have a color display.
// }

#endif