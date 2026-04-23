#pragma once

#include <widgets/widget.h>

class TasksWidget : public Widget {
protected:
    void drawContents(int top_x, int top_y, int width, int height);
public:
    TasksWidget() : Widget(C_GREEN_DEEP_FOREST_SHADOW, C_GREEN_STORMY) {};
};