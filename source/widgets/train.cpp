#include <widgets/train.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <helpers.h>

void TrainWidget::draw(int top_x, int top_y, int width, int height) {
    drawBox(top_x,  top_y, width, height, C_TRAIN, C_WHITE); // Train TR

    int tx = top_x + 4;
    int ty = top_y + 4;

    ulSetTextColor(C_WHITE);
    ulDrawString(tx, ty, "NEXT TRAIN");

    // Large time
    ulSetTextColor(C_WHITE);
    ulDrawString(tx, ty + 16, "08:10");

    // LIVE badge
    ulSetTextColor(C_GREEN);
    ulDrawString(tx + 60, ty + 16, "LIVE");

    // Station
    ulSetTextColor(C_TEAL);
    ulDrawString(tx + 4, ty + 34, "OLYMPIC PK");

    // Status
    ulSetTextColor(C_LTGREY);
    ulDrawString(tx + 4, ty + 50, "T1: ON TIME");
}