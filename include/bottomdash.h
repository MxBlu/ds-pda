#pragma once

#include <colours.h>

// ---------------------------------------------------------------------------
// Layout constants
// ---------------------------------------------------------------------------
#define TAB_COUNT           5
#define TAB_WIDTH           51
#define TAB_BAR_HEIGHT      24
#define TAB_ICON_Y          4
#define TAB_ICON_OFFSET     17
#define TAB_LAST_ICON_OFFSET 18
#define FOOTER_HEIGHT       20
#define FOOTER_TEXT_X       4
#define FOOTER_TEXT_Y_OFFSET 14

// ---------------------------------------------------------------------------
// Semantic colour aliases
// ---------------------------------------------------------------------------
#define C_BG                C_GREY_DEEP_NIGHT
#define C_TAB_INACTIVE_BG   C_GREY_CHARCOAL
#define C_TAB_ACTIVE_BG     C_GREY_DEEP_NIGHT
#define C_TAB_ICON_INACTIVE C_GREY
#define C_TAB_ICON_ACTIVE   C_WHITE
#define C_FOOTER_BG         C_GREY_CHARCOAL
#define C_FOOTER_STATUS     C_GREEN

void initBottomScreen();
void updateBottomScreen();
void drawBottomScreen();