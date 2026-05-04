#pragma once

#include <tabs/tab.h>
#include <spritesheet/spritesheet_16.h>

class TrainTab : public Tab {
public:
    TrainTab() : Tab(LUCIDE_16_TABLE[LUCIDE_16_ICON_TRAM_FRONT]) {}

    void draw(int top_x, int top_y, int width, int height);
};