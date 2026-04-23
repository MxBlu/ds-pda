#include <widgets/budget.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <helpers.h>

void BudgetWidget::drawContents(int top_x, int top_y, int width, int height) {
    ulSetTextColor(C_WHITE);
    ulDrawString(top_x, top_y, "BUDGET");
    ulDrawString(top_x, top_y + 14, "$450 / $800");

    // Progress bar
    int barW = width - 8;
    int filledW = (barW * 56) / 100;
    int barY = top_y + 30;
    ulDrawFillRect(top_x, barY, top_x + barW, barY + 8, C_GREY);
    ulDrawFillRect(top_x, barY, top_x + filledW, barY + 8, RGB15(18, 8, 22));
}