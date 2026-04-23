#pragma once

#include <ulib/ulib.h>

#include <colours.h>

#define WIDGET_PAD 8
#define WIDGET_WIDTH 116
#define WIDGET_HEIGHT 90
#define WIDGET_BORDER 2
#define WIDGET_INNER_PAD 8

#define C_BG C_GREY_DEEP_NIGHT

class Widget {
protected:
    u16 bgColour;
    u16 borderColour;

    Widget(u16 bgColour, u16 borderColour) : bgColour(bgColour), borderColour(borderColour) {};

    virtual void drawContents(int top_x, int top_y, int width, int height) = 0;
public:
    void draw(int top_x, int top_y, int width, int height);
};