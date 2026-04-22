#include <widgets/tasks.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <helpers.h>

void TasksWidget::draw(int top_x, int top_y, int width, int height) {
    drawBox(top_x, top_y,  width, height, C_TASKS, C_WHITE);

    int qx = top_x + 4;
    int qy = top_y + 4;

    ulSetTextColor(C_WHITE);
    ulDrawString(qx, qy, "TASKS");

    ulSetTextColor(C_GREY);
    ulDrawString(qx, qy + 14, "EXPIRED");
}