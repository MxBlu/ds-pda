#include <widgets/weather.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <helpers.h>

void WeatherWidget::draw(int top_x, int top_y, int width, int height) {
    drawBox(top_x, top_y, width, height, C_WEATHER, C_WHITE); // Weather TL

    int wx = top_x + 4;
    int wy = top_y + 4;

    ulSetTextColor(C_ORANGE);
    ulDrawString(wx, wy, "WEATHER");

    // "NSW" badge top-right of weather box
    drawBadge(top_x + width - 26, top_y + 4, 24, 11, C_BADGE_NSW, C_WHITE, "NSW");

    // Large temperature
    ulSetTextColor(C_WHITE);
    ulDrawString(wx, wy + 18, "22 C");

    // 3 forecast columns  (spaced evenly in COL_W)
    // Each column is ~38px wide; labels + temps
    ulSetTextColor(C_LTGREY);
    ulDrawString(wx,      wy + 50, "5P");
    ulDrawString(wx + 38, wy + 50, "9P");
    ulDrawString(wx + 76, wy + 50, "9P");

    ulSetTextColor(C_GREY);
    ulDrawString(wx,      wy + 64, "24");
    ulDrawString(wx + 38, wy + 64, "19");
    ulDrawString(wx + 76, wy + 64, "14");
}