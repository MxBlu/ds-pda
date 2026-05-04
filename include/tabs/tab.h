#pragma once

#include <spritesheet/common.h>

class Tab {
protected:
    Tab(lucide_icon_entry_t icon) : icon(icon) {};
public:
    lucide_icon_entry_t icon;
    int pos_y = 0;

    virtual void draw(int top_x, int top_y, int width, int height) = 0;
};