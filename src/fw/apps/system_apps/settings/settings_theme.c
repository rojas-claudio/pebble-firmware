/*
    Settings menu for utilizing the system_theme service.

    -> Toggles between three colors at the moment.
    -> Settings do not persist after restart.
    -> Breaks when compiling for Silk. [FIXED]
    -> Could be cleaner.
*/


#include "settings_theme.h"
#include "settings_window.h"

#include "applib/ui/ui.h"
#include "kernel/pbl_malloc.h"
#include "services/common/analytics/analytics_event.h"
#include "services/common/i18n/i18n.h"

#include "applib/graphics/gcolor_definitions.h"
#include "services/common/system_theme.h"
#include "applib/graphics/gtypes.h"

#include "system/logging.h"
#include "system/passert.h"
#include "util/string.h"

#include <string.h>

#if PBL_COLOR

typedef enum ThemeSettingsRow {
    GlobalTheme,
    MenuTheme,
    TimelineFutureTheme,
    ThemeSettingsRow_Count,
} ThemeSettingsRow;

typedef struct SettingsThemeData {
    SettingsCallbacks callbacks;
    char system_theme[20];
    char menu_theme[20];
    char tl_future_theme[20];
} SettingsThemeData;

static void prv_deinit_cb(SettingsCallbacks *context) {
    SettingsThemeData *data = (SettingsThemeData *)context;
    i18n_free_all(data);
    app_free(data);
}

static void prv_draw_row_cb(SettingsCallbacks *context, GContext *ctx,
                            const Layer *cell_layer, uint16_t row, bool selected) {
    SettingsThemeData *data = (SettingsThemeData *)context;

    const char *title = NULL;
    const char *subtitle = NULL;

    switch (row) {
        case GlobalTheme: {
            title = i18n_noop("Global"); //not sure what i18n is yet, language/region related?
            subtitle = data->system_theme;
            break;
        }
        case MenuTheme: {
            title = i18n_noop("Menu");
            subtitle = data->menu_theme;
            break;
        }
        case TimelineFutureTheme: {
            title = i18n_noop("Timeline Future");
            subtitle = data->tl_future_theme;
            break;
        }
        default: {
            WTF;
        }
    }

    menu_cell_basic_draw(ctx, cell_layer, i18n_get(title, data), i18n_get(subtitle, data), NULL);

}

static void prv_selection_changed_cb(SettingsCallbacks *context, uint16_t new_row, uint16_t old_row) {

}

static void prv_select_click_cb(SettingsCallbacks *context, uint16_t row) {
    SettingsThemeData *data = (SettingsThemeData *)context;
    switch (row) {
        case GlobalTheme: {
            GColor system_theme = system_theme_get();
            if (gcolor_equal(system_theme, GColorVividCerulean)) {
                system_theme_set(GColorLavenderIndigo);
                strcpy(data->system_theme, "Lavender Indigo");
                strcpy(data->menu_theme, "Lavender Indigo");
                strcpy(data->tl_future_theme, "Lavender Indigo");
            } else if (gcolor_equal(system_theme, GColorLavenderIndigo)) {
                system_theme_set(GColorScreaminGreen);
                strcpy(data->system_theme, "Screamin' Green");
                strcpy(data->menu_theme, "Screamin' Green");
                strcpy(data->tl_future_theme, "Screamin' Green");
            } else if (gcolor_equal(system_theme, GColorScreaminGreen)) {
                system_theme_set(GColorVividCerulean);
                strcpy(data->system_theme, "Vivid Cerulean");
                strcpy(data->menu_theme, "Vivid Cerulean");
                strcpy(data->tl_future_theme, "Vivid Cerulean");
            }
            break;
        }
        case MenuTheme: {
            GColor menu_theme = menu_theme_get();
            strcpy(data->system_theme, "Custom");
            if (gcolor_equal(menu_theme, GColorVividCerulean)) {
                menu_theme_set(GColorLavenderIndigo);
                strcpy(data->menu_theme, "Lavender Indigo");
            } else if (gcolor_equal(menu_theme, GColorLavenderIndigo)) {
                menu_theme_set(GColorScreaminGreen);
                strcpy(data->menu_theme, "Screamin' Green");
            } else if (gcolor_equal(menu_theme, GColorScreaminGreen)) {
                menu_theme_set(GColorVividCerulean);
                strcpy(data->menu_theme, "Vivid Cerulean");
            }
            break;
        }
        case TimelineFutureTheme: {
            GColor tl_future_theme = timeline_future_theme_get();
            strcpy(data->system_theme, "Custom");
            if (gcolor_equal(tl_future_theme, GColorVividCerulean)) {
                timeline_future_theme_set(GColorLavenderIndigo);
                strcpy(data->tl_future_theme, "Lavender Indigo");
            } else if (gcolor_equal(tl_future_theme, GColorLavenderIndigo)) {
                timeline_future_theme_set(GColorScreaminGreen);
                strcpy(data->tl_future_theme, "Screamin' Green");
            } else if (gcolor_equal(tl_future_theme, GColorScreaminGreen)) {
                timeline_future_theme_set(GColorVividCerulean);
                strcpy(data->tl_future_theme, "Vivid Cerulean");
            }
            break;
        }
        default:
            WTF;

    }

    settings_menu_reload_data(SettingsMenuItemTheme);
}


static uint16_t prv_num_rows_cb(SettingsCallbacks *context) {
    return ThemeSettingsRow_Count;
}

static void prv_expand_cb(SettingsCallbacks *context) {
    
}

static void prv_hide_cb(SettingsCallbacks *context) {

}

static Window *prv_init(void) {
    SettingsThemeData *data = app_zalloc_check(sizeof(SettingsThemeData));

    data->callbacks = (SettingsCallbacks) {
        .deinit = prv_deinit_cb,
        .draw_row = prv_draw_row_cb,
        .selection_changed = prv_selection_changed_cb,
        .select_click = prv_select_click_cb,
        .num_rows = prv_num_rows_cb, 
        .expand = prv_expand_cb,
        .hide = prv_hide_cb,
    };

    //Logic for getting theme names upon draw
    // -> Get theme type, current GColor and pass to service
    // -> Service will return stringized name, use for initial draw
    // -> Will probably also use for every theme change

    // strcpy(data->system_theme, "Vivid Cerulean");
    // strcpy(data->menu_theme, "Vivid Cerulean");
    // strcpy(data->tl_future_theme, "Vivid Cerulean");

    return settings_window_create(SettingsMenuItemTheme, &data->callbacks);
}

const SettingsModuleMetadata *settings_theme_get_info(void) {
    static const SettingsModuleMetadata s_module_info = {
        .name = i18n_noop("Personalization"),
        .init = prv_init,
    };

    return &s_module_info;
}

#endif