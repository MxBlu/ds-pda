#pragma once

#include <time.h>

#include <colours.h>

#define PAD 3
// header band height
#define HDR_H   20
// y where widget rows start
#define BOX_TOP HDR_H + PAD
// width of each column
#define COL_W   124
// x of right column
#define COL2_X  PAD + COL_W + PAD
// height of top widget row
#define ROW1_H  100
#define ROW2_Y  BOX_TOP + ROW1_H + PAD
// fill to bottom
#define ROW2_H  192 - ROW2_Y - PAD

#define WIDGET_WIDTH 124
#define WIDGET_HEIGHT 100

void initTopScreenWidgets();
void drawTopScreen(struct tm*);