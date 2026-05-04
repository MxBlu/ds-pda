#pragma once

#include <tabs/tab.h>
#include <spritesheet/spritesheet_16.h>

class BudgetTab : public Tab {
public:
    BudgetTab() : Tab(LUCIDE_16_TABLE[LUCIDE_16_ICON_DOLLAR_SIGN]) {}

    void draw(int top_x, int top_y, int width, int height);
};