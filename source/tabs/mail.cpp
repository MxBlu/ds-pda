#include <tabs/mail.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <fonts.h>

typedef struct mail_item {
    char sender[32];
    char subject[64];
    char received_time[16];
} mail_item;

const mail_item demo_mails[] = {
    {"Alice", "Meeting Tomorrow", "10:00pm"},
    {"Bob", "Project Update", "2:00am"},
    {"Charlie", "Lunch Plans", "Yesterday"},
    {"Diana", "Vacation Photos", "30th April"},
    {"Eve", "Security Alert", "30th April"},
    {"Greg", "Vacation Photos", "30th April"},
    {"Tom", "Security Alert", "30th April"},
    {"Daniel", "Vacation Photos", "30th April"},
    {"Steve", "Security Alert", "30th April"}
};
const int numItems = 9;
const int itemHeight = 46;
const int itemPadding = 2;
const int contentWindowHeight = SCREEN_HEIGHT - 24 - 24; // Temp calculated content height
const int maxScrollY = numItems * itemHeight - contentWindowHeight;

void MailTab::update() {
    // maxScrollY > 0 checks whether there's enough items to scroll
    if (ul_keys.touch.deltaY != 0 && maxScrollY > 0) {
        this->pos_y -= ul_keys.touch.deltaY;

        // Clamp pos_y to valid range
        if (this->pos_y < 0) {
            this->pos_y = 0;
        }
        if (this->pos_y > maxScrollY) {
            this->pos_y = maxScrollY;
        }
    }
}

void MailTab::draw(int top_x, int top_y, int width, int height) {
    int startIndex = this->pos_y / itemHeight;
    int maxIndex = startIndex + height / itemHeight + 1;

    selectFont(FONT_PROGGY_10);
    for (int i = startIndex; i <= maxIndex && i < numItems; i++) {
        const mail_item &mail = demo_mails[i];

        int itemY = top_y - this->pos_y + i * itemHeight;

        // Highlight background
        ulDrawFillRect(top_x + itemPadding, itemY + itemPadding, 
            top_x + width - itemPadding, itemY + itemHeight - itemPadding, C_GREY_CHARCOAL);

        u16 accentColour = (i % 2 == 0) ? C_RED : C_BLUE_MAYA_BLUE;
        ulDrawFillRect(top_x + 2 * itemPadding, itemY + itemPadding + 8, 
            top_x + 4 * itemPadding, itemY + itemHeight - itemPadding - 8, accentColour);

        // Draw sender and subject
        ulSetTextColor(C_WHITE);
        drawStringBaselineAligned(top_x + 14, itemY + itemPadding + 8, mail.sender);
        drawStringBaselineAligned(top_x + 14, itemY + itemPadding + 24, mail.subject);

        // Draw received time on the right
        ulSetTextColor(C_GREY);
        drawStringBaselineAlignedRightAligned(
            top_x + width - itemPadding - 2, itemY + itemPadding + 8, mail.received_time);
    }
}