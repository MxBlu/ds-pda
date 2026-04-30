#include <widgets/weather.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <fonts.h>
#include <helpers.h>

void WeatherWidget::drawContents(int top_x, int top_y, int width, int height) {
    // "NSW" badge top-right of weather box
    selectFont(FONT_PROGGY_10);
    ulSetTextColor(this->titleColour);
    drawStringBaselineAlignedRightAligned(top_x + width, top_y - 6, "NSW");

    // Large temperature
    selectFont(FONT_PROGGY_16B);
    ulSetTextColor(C_WHITE);
    drawStringBaselineAligned(top_x, top_y + 18, "22 C");

    // 3 forecast columns  (spaced evenly in COL_W)
    // Each column is ~38px wide; labels + temps
    selectFont(FONT_PROGGY_10);
    ulSetTextColor(C_LTGREY);
    drawStringBaselineAligned(top_x,      top_y + 50, "5P");
    drawStringBaselineAligned(top_x + 38, top_y + 50, "9P");
    drawStringBaselineAligned(top_x + 76, top_y + 50, "9P");

    selectFont(FONT_PROGGY_10);
    ulSetTextColor(C_GREY);
    drawStringBaselineAligned(top_x,      top_y + 64, "24");
    drawStringBaselineAligned(top_x + 38, top_y + 64, "19");
    drawStringBaselineAligned(top_x + 76, top_y + 64, "14");
}