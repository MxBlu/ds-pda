#include <widgets/weather.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <fonts.h>
#include <helpers.h>
#include <icons.h>
#include <spritesheet/spritesheet_12.h>
#include <spritesheet/spritesheet_16.h>

std::vector<lucide_icon_entry_t> WeatherWidget::getPreloadIcons() {
    return {
        LUCIDE_16_TABLE[LUCIDE_16_ICON_SUN],
        LUCIDE_12_TABLE[LUCIDE_12_ICON_SUN],
        LUCIDE_12_TABLE[LUCIDE_12_ICON_CLOUD],
        LUCIDE_12_TABLE[LUCIDE_12_ICON_MOON]
    };
}

void WeatherWidget::drawContents(int top_x, int top_y, int width, int height) {
    // "NSW" badge top-right of weather box
    selectFont(FONT_PROGGY_10);
    ulSetTextColor(this->titleColour);
    drawStringBaselineAlignedRightAligned(top_x + width, top_y - 4, "NSW");

    // Large temperature
    selectFont(FONT_PROGGY_16B);
    ulSetTextColor(C_WHITE);
    drawStringBaselineAligned(top_x + 16, top_y + 18, "22");

    // Weather icon (sunny)
    drawIcon(LUCIDE_16_TABLE[LUCIDE_16_ICON_SUN], top_x - 4, top_y + 12, this->titleColour);

    // 3 forecast columns  (spaced evenly in COL_W)
    // Each column is ~38px wide; labels + temps

    // Draw background for forecast area
    ulDrawFillRect(top_x, top_y + 34, top_x + width, top_y + height + 6, C_RED_BLACK_OLIVE);
    // Draw separator lines
    ulDrawFillRect(top_x + 31, top_y + 36, top_x + 31, top_y + height + 4, C_BLUE_DEEP_OCEAN_BLUE);
    ulDrawFillRect(top_x + 67, top_y + 36, top_x + 67, top_y + height + 4, C_BLUE_DEEP_OCEAN_BLUE);

    selectFont(FONT_PROGGY_10);
    ulSetTextColor(C_LTGREY);
    drawStringBaselineAligned(top_x + 6, top_y + 38, "9A");
    drawStringBaselineAligned(top_x + 40, top_y + 38, "12P");
    drawStringBaselineAligned(top_x + 77, top_y + 38, "5P");

    drawIcon(LUCIDE_12_TABLE[LUCIDE_12_ICON_SUN],   top_x + 6,  top_y + 49, C_YELLOW);
    drawIcon(LUCIDE_12_TABLE[LUCIDE_12_ICON_CLOUD], top_x + 43, top_y + 49, C_GREY);
    drawIcon(LUCIDE_12_TABLE[LUCIDE_12_ICON_MOON],  top_x + 77, top_y + 49, C_BLUE_MAYA_BLUE);

    selectFont(FONT_PROGGY_10);
    ulSetTextColor(C_GREY);
    drawStringBaselineAligned(top_x + 6,  top_y + 64, "24");
    drawStringBaselineAligned(top_x + 42, top_y + 64, "19");
    drawStringBaselineAligned(top_x + 77, top_y + 64, "14");

}