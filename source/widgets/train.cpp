#include <widgets/train.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <helpers.h>

void TrainWidget::drawContents(int top_x, int top_y, int width, int height) {
    ulSetTextColor(C_WHITE);
    ulDrawString(top_x, top_y, "NEXT TRAIN");

    // Large time
    ulSetTextColor(C_WHITE);
    ulDrawString(top_x, top_y + 16, "08:10");

    // LIVE badge
    ulSetTextColor(C_GREEN);
    ulDrawString(top_x + 60, top_y + 16, "LIVE");

    // Station
    ulSetTextColor(C_TEAL);
    ulDrawString(top_x + 4, top_y + 34, "OLYMPIC PK");

    // Status
    ulSetTextColor(C_LTGREY);
    ulDrawString(top_x + 4, top_y + 50, "T1: ON TIME");
}