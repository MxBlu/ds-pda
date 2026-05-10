#pragma once

#include <nds.h>
#include <spritesheet/common.h>

// Screen height - tab bar height - footer height
// The +2 fixes padding for the last item
#define CONTENT_AREA_HEIGHT (SCREEN_HEIGHT - 24 - 20 - 2) 

extern int g_last_update_y;

class Tab {
protected:
    Tab(lucide_icon_entry_t icon) : icon(icon) {};
public:
    lucide_icon_entry_t icon;
    int pos_y = 0;

    virtual void update() = 0;
    virtual void draw(int top_x, int top_y, int width, int height) = 0;
};