#pragma once

#include <tabs/tab.h>
#include <spritesheet/spritesheet_16.h>

class MailTab : public Tab {
public:
    MailTab() : Tab(LUCIDE_16_TABLE[LUCIDE_16_ICON_MAIL]) {}

    void draw(int top_x, int top_y, int width, int height);
};