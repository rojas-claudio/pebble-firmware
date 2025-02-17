/*
 * Copyright 2024 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "services/normal/timeline/timeline.h"
#include "services/common/system_theme.h"

#define TIMELINE_NUM_VISIBLE_ITEMS (2)

#define TIMELINE_PAST_COLOR PBL_IF_COLOR_ELSE(GColorChromeYellow, GColorLightGray)
#define TIMELINE_FUTURE_COLOR PBL_IF_COLOR_ELSE(timeline_future_theme_get(), GColorLightGray)
#define TIMELINE_DOT_COLOR GColorBlack

typedef TimelineIterDirection TimelineDirection;
