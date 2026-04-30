#include <widgets/train.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <fonts.h>
#include <helpers.h>

void TrainWidget::drawContents(int top_x, int top_y, int width, int height) {
    // Large time
    selectFont(FONT_PROGGY_16B);
    ulSetTextColor(C_WHITE);
    drawStringBaselineAligned(top_x, top_y + 16, "08:10");

    // LIVE badge
    selectFont(FONT_PROGGY_12B);
    ulSetTextColor(C_GREEN);
    drawStringBaselineAligned(top_x + 60, top_y + 16, "LIVE");

    // Station
    selectFont(FONT_PROGGY_10);
    ulSetTextColor(C_TEAL);
    drawStringBaselineAligned(top_x + 4, top_y + 34, "OLYMPIC PK");

    // Status
    selectFont(FONT_PROGGY_10);
    ulSetTextColor(C_LTGREY);
    drawStringBaselineAligned(top_x + 4, top_y + 50, "T1: ON TIME");
}