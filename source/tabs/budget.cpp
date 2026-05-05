#include <ulib/ulib.h>

#include <tabs/budget.h>

#include <colours.h>

void BudgetTab::update() {

}

void BudgetTab::draw(int top_x, int top_y, int width, int height) {
    ulDrawFillRect(top_x, top_y, top_x + width, top_y + height, C_WHITE);
}