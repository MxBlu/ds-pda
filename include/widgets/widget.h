#pragma once

#include <vector>

#include <ulib/ulib.h>
// Just to shut up the language server up
#include <nds/arm9/video.h>

#include <spritesheet/common.h>
#include <colours.h>

#define WIDGET_PAD 8
#define WIDGET_WIDTH 116
#define WIDGET_HEIGHT 90
#define WIDGET_BORDER 2
#define WIDGET_SHADOW_OFFSET 2
#define WIDGET_INNER_PAD 8
#define WIDGET_TITLE_SEP 12

#define C_BG C_GREY_DEEP_NIGHT

class Widget {
protected:
    const char *title;
    u16 bgColour;
    u16 borderColour;
    u16 titleColour;

    Widget(const char *title, u16 bgColour, u16 borderColour, u16 titleColour) : 
        title(title), bgColour(bgColour), borderColour(borderColour), titleColour(titleColour) {};

    virtual void drawContents(int top_x, int top_y, int width, int height) = 0;
private:
    void drawTitle(const char *title, int top_x, int top_y, int width, int height);
public:
    virtual std::vector<lucide_icon_entry_t> getPreloadIcons() { return {}; };
    void draw(int top_x, int top_y, int width, int height);
};