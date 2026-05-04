#pragma once

#include <tabs/tab.h>
#include <spritesheet/spritesheet_16.h>

class CalendarTab : public Tab {
public:
    CalendarTab() : Tab(LUCIDE_16_TABLE[LUCIDE_16_ICON_CALENDAR]) {}

    void draw(int top_x, int top_y, int width, int height);
};