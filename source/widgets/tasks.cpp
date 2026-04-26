#include <widgets/tasks.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <helpers.h>

void TasksWidget::drawContents(int top_x, int top_y, int width, int height) {
    ulSetTextColor(C_GREY);
    ulDrawString(top_x, top_y + 14, "EXPIRED");
}