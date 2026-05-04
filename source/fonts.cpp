#include <fonts.h>
#include <ulib/ulib.h>

#include "proggy_square_10_bin.h"
#include "proggy_square_12b_bin.h"
#include "proggy_square_16b_bin.h"

// We would like 6px, 8px, 12px, 16px
// but we can't practically get 6px and 8px

UL_FONT *fonts[NUM_FONTS];
int currentFont = -1;

// Offsets to keep mixed-font text baseline-aligned.
static const int fontBaselineOffsets[NUM_FONTS] = {0, -2, -5, 0};

void initFonts() {
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

int getFontBaselineOffset(int font) {
   if (font < 0 || font >= NUM_FONTS) return 0;
   return fontBaselineOffsets[font];
}

int getCurrentFontBaselineOffset() {
   return getFontBaselineOffset(currentFont);
}

void drawStringBaselineAligned(int x, int y, const char *text) {
   ulDrawString(x, y + getCurrentFontBaselineOffset(), text);
}

void drawStringBaselineAlignedRightAligned(int x, int y, const char *text) {
   int textWidth = ulGetStringWidth(text);
   ulDrawString(x - textWidth, y + getCurrentFontBaselineOffset(), text);
}