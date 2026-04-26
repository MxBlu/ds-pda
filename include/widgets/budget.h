#pragma once

#include <widgets/widget.h>

class BudgetWidget : public Widget {
protected:
    void drawContents(int top_x, int top_y, int width, int height);
public:
    BudgetWidget() : Widget("BUDGET", C_RED_PLUM_CHARCOAL, C_PURPLE_MUTED_MULBERRY, C_PURPLE_VIBRANT_LILAC) {};
};