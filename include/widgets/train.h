#pragma once

#include <widgets/widget.h>

class TrainWidget : public Widget {
protected:
    void drawContents(int top_x, int top_y, int width, int height);
public:
    TrainWidget() : Widget(C_BLUE_OBSIDIAN, C_BLUE_DEEP_CHARCOAL) {};
};