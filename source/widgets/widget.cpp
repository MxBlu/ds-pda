#include <widgets/widget.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <helpers.h>

void Widget::draw(int top_x, int top_y, int width, int height) {
    // Draw the box shadow
    ulDrawFillRect(
        top_x + WIDGET_SHADOW_OFFSET, 
        top_y + WIDGET_SHADOW_OFFSET, 
        top_x + width + WIDGET_SHADOW_OFFSET, 
        top_y + height + WIDGET_SHADOW_OFFSET, C_BLACK);
    // Draw background and border
    drawBox(top_x, top_y, width, height, this->bgColour, this->borderColour, WIDGET_BORDER);

    // Draw title
    drawTitle(this->title, top_x, top_y, width, height);

    // Draw widget-specific contents
    drawContents(top_x + WIDGET_INNER_PAD + WIDGET_BORDER, 
        top_y + WIDGET_INNER_PAD + WIDGET_BORDER, 
        width - (WIDGET_INNER_PAD * 2) - (WIDGET_BORDER * 2), 
        height - (WIDGET_INNER_PAD * 2) - (WIDGET_BORDER * 2));
}

void Widget::drawTitle(const char *title, int top_x, int top_y, int width, int height) {
    ulSetTextColor(this->titleColour);
    ulDrawString(top_x + 4, top_y + 4, title);
    // Draw separator line
    ulDrawFillRect(top_x + 4, top_y + 4 + WIDGET_TITLE_SEP, top_x + width - 4, top_y + 4 + WIDGET_TITLE_SEP, this->borderColour);
}