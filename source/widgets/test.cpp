#include <widgets/test.h>

#include <ulib/ulib.h>

#include <helpers.h>

void TestWidget::drawContents(int top_x, int top_y, int width, int height) {
    ulDrawFillRect(top_x, top_y, top_x + width, top_y + height, C_WHITE);
}