#pragma once

#include <tabs/tab.h>
#include <spritesheet/spritesheet_16.h>

class TasksTab : public Tab {
public:
    TasksTab() : Tab(LUCIDE_16_TABLE[LUCIDE_16_ICON_SQUARE_CHECK_BIG]) {}

    void draw(int top_x, int top_y, int width, int height);
};