#pragma once

#include <widgets/widget.h>

class TrainWidget : public Widget {
protected:
    void drawContents(int top_x, int top_y, int width, int height);
public:
    TrainWidget() : Widget("NEXT TRAIN", C_BLUE_OBSIDIAN, C_BLUE_DEEP_CHARCOAL, C_BLUE_MAYA_BLUE) {};
};