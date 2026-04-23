#include <widgets/weather.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <helpers.h>

void WeatherWidget::drawContents(int top_x, int top_y, int width, int height) {
    ulSetTextColor(C_ORANGE);
    ulDrawString(top_x, top_y, "WEATHER");

    // "NSW" badge top-right of weather box
    drawBadge(top_x + width - 26, top_y + 4, 24, 11, C_BADGE_NSW, C_WHITE, "NSW");

    // Large temperature
    ulSetTextColor(C_WHITE);
    ulDrawString(top_x, top_y + 18, "22 C");

    // 3 forecast columns  (spaced evenly in COL_W)
    // Each column is ~38px wide; labels + temps
    ulSetTextColor(C_LTGREY);
    ulDrawString(top_x,      top_y + 50, "5P");
    ulDrawString(top_x + 38, top_y + 50, "9P");
    ulDrawString(top_x + 76, top_y + 50, "9P");

    ulSetTextColor(C_GREY);
    ulDrawString(top_x,      top_y + 64, "24");
    ulDrawString(top_x + 38, top_y + 64, "19");
    ulDrawString(top_x + 76, top_y + 64, "14");
}