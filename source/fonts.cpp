#include <fonts.h>
#include <ulib/ulib.h>

#include "proggy_square_8_120h_bin.h"
#include "proggy_square_10_bin.h"
#include "proggy_square_12b_bin.h"
#include "proggy_square_16b_bin.h"

// We would like 6px, 8px, 12px, 16px
// but we can't practically get 6px and 8px
// 8px is hacked in with 120% height, but 6px is just not possible to get with a good quality

UL_FONT *fonts[NUM_FONTS];
int currentFont = -1;

void initFonts() {
   fonts[FONT_PROGGY_8] = ulLoadFontFile((const char *)proggy_square_8_120h_bin, sizeof(proggy_square_8_120h_bin));
   if (!fonts[FONT_PROGGY_8]) printf("\n Failed to load font size 8!");

   fonts[FONT_PROGGY_10] = ulLoadFontFile((const char *)proggy_square_10_bin, sizeof(proggy_square_10_bin));
   if (!fonts[FONT_PROGGY_10]) printf("\n Failed to load font size 10!");

   fonts[FONT_PROGGY_12B] = ulLoadFontFile((const char *)proggy_square_12b_bin, sizeof(proggy_square_12b_bin));
   if (!fonts[FONT_PROGGY_12B]) printf("\n Failed to load font size 12!");

   fonts[FONT_PROGGY_16B] = ulLoadFontFile((const char *)proggy_square_16b_bin, sizeof(proggy_square_16b_bin));
   if (!fonts[FONT_PROGGY_16B]) printf("\n Failed to load font size 16!");

   ulSetFont(fonts[FONT_PROGGY_10]);
   currentFont = FONT_PROGGY_10;
}

void selectFont(int font) {
   if (font < 0 || font >= NUM_FONTS) return;
   ulSetFont(fonts[font]);
   currentFont = font;
}

int getCurrentFont() {
   return currentFont;
}