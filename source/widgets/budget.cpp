#include <widgets/budget.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <helpers.h>

void BudgetWidget::draw(int top_x, int top_y, int width, int height) {
    drawBox(top_x,  top_y,  width, height, C_BUDGET,  C_WHITE); // Budget BR

    int bx = top_x + 4;
    int by = top_y + 4;

    ulSetTextColor(C_WHITE);
    ulDrawString(bx, by, "BUDGET");
    ulDrawString(bx, by + 14, "$450 / $800");

    // Progress bar
    int barW = width - 8;
    int filledW = (barW * 56) / 100;
    int barY = by + 30;
    ulDrawFillRect(bx, barY, bx + barW, barY + 8, C_GREY);
    ulDrawFillRect(bx, barY, bx + filledW, barY + 8, RGB15(18, 8, 22));
}