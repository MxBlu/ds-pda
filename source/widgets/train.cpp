#include <widgets/train.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <fonts.h>
#include <helpers.h>
#include <icons.h>

#include <spritesheet/spritesheet_12.h>

void TrainWidget::drawContents(int top_x, int top_y, int width, int height) {
    // Large time
    selectFont(FONT_PROGGY_16B);
    ulSetTextColor(C_WHITE);
    drawStringBaselineAligned(top_x, top_y + 18, "08:10");

    // LIVE badge
    selectFont(FONT_PROGGY_10);
    ulSetTextColor(C_GREEN);
    drawStringBaselineAlignedRightAligned(top_x + width, top_y + 18, "OK");

    drawIcon(LUCIDE_12_TABLE[LUCIDE_12_ICON_ARROW_RIGHT], top_x, top_y + 32, C_GREY_STEEL_MIST);

    // Station
    selectFont(FONT_PROGGY_10);
    ulSetTextColor(C_GREY_STEEL_MIST);
    drawStringBaselineAligned(top_x + 16, top_y + 34, "Olympic Park");

    // Status
    ulDrawFillRect(top_x, top_y + 54, top_x + width, top_y + height + 2, C_BLUE_DEEP_CHARCOAL);

    drawIcon(LUCIDE_12_TABLE[LUCIDE_12_ICON_INFO], top_x + 4, top_y + 57, C_BLUE_MUTED_SLATE);
    selectFont(FONT_PROGGY_10);
    ulSetTextColor(C_BLUE_MUTED_SLATE);
    drawStringBaselineAligned(top_x + 20, top_y + 59, "T1: ON TIME");
}