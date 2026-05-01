#pragma once

#include <widgets/widget.h>

class WeatherWidget : public Widget {
protected:
    std::vector<lucide_icon_entry_t> getPreloadIcons();
    void drawContents(int top_x, int top_y, int width, int height);

public:
    WeatherWidget() : Widget("WEATHER", C_ORANGE_GUNMETAL, C_ORANGE_BLACKENED_CURRANT, C_ORANGE_MONARCH_ORANGE) {};
};