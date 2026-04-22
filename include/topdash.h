#pragma once

#include <time.h>

#include <colours.h>

// Padding from screen edges for header and widgets
#define OUTER_PAD 8
// Total header height including separator line
#define HDR_H   41
// Header text render Y position
#define HDR_TEXT_Y 13

#define WIDGET_WIDTH 124
#define WIDGET_HEIGHT 100

#define C_BG C_GREY_DEEP_NIGHT
#define C_DAY_TXT C_GREY_STEEL_MIST
#define C_DATETIME_TXT C_WHITE
#define C_HEADER_SEP C_BLUE_MIDNIGHT_NAVY

void initTopScreenWidgets();
void drawTopScreen(struct tm*);