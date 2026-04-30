#pragma once

#define NUM_FONTS 4

#define FONT_PROGGY_8 0
#define FONT_PROGGY_10 1
#define FONT_PROGGY_12B 2
#define FONT_PROGGY_16B 3

void initFonts();
void selectFont(int font);
int getCurrentFont();