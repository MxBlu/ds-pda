#include <widgets/widget.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <helpers.h>

void Widget::draw(int top_x, int top_y, int width, int height) {
    // Draw background and border
    drawBox(top_x, top_y, width, height, this->bgColour, this->borderColour, WIDGET_BORDER);

    // Draw widget-specific contents
    drawContents(top_x + WIDGET_INNER_PAD + WIDGET_BORDER, 
        top_y + WIDGET_INNER_PAD + WIDGET_BORDER, 
        width - (WIDGET_INNER_PAD * 2) - (WIDGET_BORDER * 2), 
        height - (WIDGET_INNER_PAD * 2) - (WIDGET_BORDER * 2));
}