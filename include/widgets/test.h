#pragma once

#include <widgets/widget.h>

class TestWidget : public Widget {
protected:
    void drawContents(int top_x, int top_y, int width, int height);
public:
    TestWidget() : Widget("TEST", C_BG, C_WHITE, C_WHITE) {};
};