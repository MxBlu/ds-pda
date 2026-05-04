#pragma once

#include <colours.h>

// Padding from screen edges for header and widgets
#define OUTER_PAD 8
// Total header height including separator line
#define HDR_H   20
// Header text render Y position
#define HDR_TEXT_Y 8

#define C_BG C_GREY_DEEP_NIGHT
#define C_DAY_TXT C_GREY_STEEL_MIST
#define C_DATETIME_TXT C_WHITE
#define C_HEADER_SEP C_BLUE_MIDNIGHT_NAVY

void initTopScreen();
void updateTopScreen();
void drawTopScreen();