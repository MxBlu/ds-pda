#include <tabs/mail.h>

#include <ulib/ulib.h>

#include <colours.h>
#include <fonts.h>

#define ITEM_HEIGHT 46
#define ITEM_PADDING 2
#define ACCENT_RECT_WIDTH 4
#define ACCENT_RECT_PADDING_X 4
#define ACCENT_RECT_PADDING_Y 8
#define SENDER_SUBJECT_PADDING_X 8
#define SENDER_SUBJECT_START_X(paddedX) paddedX + ACCENT_RECT_PADDING_X + ACCENT_RECT_WIDTH + SENDER_SUBJECT_PADDING_X
#define SENDER_TIME_OFFSET_Y 8
#define SUBJECT_OFFSET_Y 24
#define TIME_N_OFFSET_X 4

typedef struct mail_item {
    char sender[32];
    char subject[32];
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

void MailTab::update() {
    if (ul_keys.touch.deltaY != 0) {
        int maxScrollY = numItems * ITEM_HEIGHT - CONTENT_AREA_HEIGHT;
        // maxScrollY > 0 checks whether there's enough items to scroll
        if (maxScrollY > 0) {
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
}

void MailTab::draw(int top_x, int top_y, int width, int height) {
    int startIndex = this->pos_y / ITEM_HEIGHT;
    int maxIndex = startIndex + height / ITEM_HEIGHT + 1;

    selectFont(FONT_PROGGY_10);
    for (int i = startIndex; i <= maxIndex && i < numItems; i++) {
        const mail_item &mail = demo_mails[i];

        int itemY = top_y - this->pos_y + i * ITEM_HEIGHT;

        int paddedX = top_x + ITEM_PADDING;
        int paddedY = itemY + ITEM_PADDING;
        int paddedWidth = width - 2 * ITEM_PADDING;
        int paddedHeight = ITEM_HEIGHT - 2 * ITEM_PADDING;

        // Highlight background
        ulDrawFillRect(paddedX, paddedY, paddedX + paddedWidth, paddedY + paddedHeight, C_GREY_CHARCOAL);

        // Accent rectangle
        u16 accentColour = (i % 2 == 0) ? C_RED : C_BLUE_MAYA_BLUE;
        ulDrawFillRect(paddedX + ACCENT_RECT_PADDING_X, paddedY + ACCENT_RECT_PADDING_Y, 
            paddedX + ACCENT_RECT_PADDING_X + ACCENT_RECT_WIDTH, 
            paddedY + paddedHeight - ACCENT_RECT_PADDING_Y, accentColour);

        // Draw sender and subject
        ulSetTextColor(C_WHITE);
        drawStringBaselineAligned(SENDER_SUBJECT_START_X(paddedX), paddedY + SENDER_TIME_OFFSET_Y, mail.sender);
        drawStringBaselineAligned(SENDER_SUBJECT_START_X(paddedX), paddedY + SUBJECT_OFFSET_Y, mail.subject);

        // Draw received time on the right
        ulSetTextColor(C_GREY);
        drawStringBaselineAlignedRightAligned(
            paddedX + paddedWidth - TIME_N_OFFSET_X, paddedY + SENDER_TIME_OFFSET_Y, mail.received_time);
    }
}