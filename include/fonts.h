#pragma once

#define NUM_FONTS 4

#define FONT_PROGGY_10 0
#define FONT_PROGGY_12B 1
#define FONT_PROGGY_16B 2

#define FONT_PROGGY_10_WIDTH 8
#define FONT_PROGGY_12B_WIDTH 7
#define FONT_PROGGY_16B_WIDTH 9

void initFonts();
void selectFont(int font);

int getCurrentFont();
int getFontBaselineOffset(int font);
int getCurrentFontBaselineOffset();

void drawStringBaselineAligned(int x, int y, const char *text);
void drawStringBaselineAlignedRightAligned(int x, int y, const char *text);
