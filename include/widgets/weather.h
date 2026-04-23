#pragma once

#include <widgets/widget.h>

class WeatherWidget : public Widget {
protected:
    void drawContents(int top_x, int top_y, int width, int height);
public:
    WeatherWidget() : Widget(C_ORANGE_GUNMETAL, C_ORANGE_BLACKENED_CURRANT) {};
};