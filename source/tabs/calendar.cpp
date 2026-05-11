#include <tabs/calendar.h>

#include <ulib/ulib.h>

#include <spritesheet/spritesheet_12.h>
#include <icons.h>
#include <colours.h>
#include <fonts.h>

#define ITEM_HEIGHT 36
#define ITEM_PADDING_X 2
#define ITEM_PADDING_Y 2
#define ITEM_ACCENT_RECT_WIDTH 2
#define ITEM_TIME_PADDING_X 8
#define ITEM_SUBJECT_LOCATION_PADDING_X 68
#define ITEM_TIME_START_X(paddedX) (paddedX + ITEM_ACCENT_RECT_WIDTH + ITEM_TIME_PADDING_X)
#define ITEM_SUBJECT_LOCATION_START_X(paddedX) (paddedX + ITEM_ACCENT_RECT_WIDTH + ITEM_SUBJECT_LOCATION_PADDING_X)
#define ITEM_SUBJECT_TIME_OFFSET_Y 4
#define ITEM_LOCATION_OFFSET_Y 20

#define PRIORITY_ITEM_HEIGHT 28
#define PRIORITY_ITEM_TEXT_OFFSET_Y 9
#define PRIORITY_ITEM_ICON_OFFSET_X 4
#define PRIORITY_ITEM_ICON_OFFSET_Y 7
#define PRIORITY_ITEM_SUBJECT_PADDING_X 22
#define PRIORITY_ITEM_TIME_OFFSET_X 8

typedef struct calendar_entry {
    char event_name[32];
    char location[32];
    char time[16];
} calendar_entry;

const calendar_entry demo_agenda[] = {
    { "Work", "", "All day" },
    { "Morning Tea", "Cafe", "10:00am" },
    { "Afternoon Tea", "Cafe", "12:00pm" },
    { "Lunch", "Home", "1:00pm" },
    { "Dinner", "", "7:00pm" },
    { "Bed-time", "", "10:00am" },
};
const int num_events = 6;
const calendar_entry priority_event = { "Holiday", "", "10 days" };

void CalendarTab::update() {
    if (ul_keys.touch.deltaY != 0) {
        int maxScrollY = (num_events * ITEM_HEIGHT) - CONTENT_AREA_HEIGHT + PRIORITY_ITEM_HEIGHT;
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

void CalendarTab::draw(int top_x, int top_y, int width, int height) {
    int startIndex = this->pos_y / ITEM_HEIGHT;
    int maxIndex = startIndex + height / ITEM_HEIGHT + 1;

    selectFont(FONT_PROGGY_10);
    for (int i = startIndex; i < maxIndex; i++) {
        const calendar_entry *entry = &demo_agenda[i];

        int itemY = top_y - this->pos_y + i * ITEM_HEIGHT;

        int paddedX = top_x + ITEM_PADDING_X;
        int paddedY = itemY + ITEM_PADDING_Y;
        int paddedWidth = width - 2 * ITEM_PADDING_X;
        int paddedHeight = ITEM_HEIGHT - 2 * ITEM_PADDING_Y;

        // Highlight background
        ulDrawFillRect(paddedX, paddedY, paddedX + paddedWidth, paddedY + paddedHeight, C_GREY_CHARCOAL);

        // Accent rectangle
        ulDrawFillRect(paddedX, paddedY, paddedX + ITEM_ACCENT_RECT_WIDTH, paddedY + paddedHeight, C_BLUE_MAYA_BLUE);

        // Time
        ulSetTextColor(C_WHITE);
        drawStringBaselineAligned(ITEM_TIME_START_X(paddedX), paddedY + ITEM_SUBJECT_TIME_OFFSET_Y, entry->time);

        // Event name
        ulSetTextColor(C_WHITE);
        drawStringBaselineAligned(ITEM_SUBJECT_LOCATION_START_X(paddedX), paddedY + ITEM_SUBJECT_TIME_OFFSET_Y, entry->event_name);

        // Location
        if (entry->location[0] != '\0') {
            ulSetTextColor(C_GREY);
            drawStringBaselineAligned(ITEM_SUBJECT_LOCATION_START_X(paddedX), paddedY + ITEM_LOCATION_OFFSET_Y, entry->location);
        }
    }

    // Priority item
    int priorityItemY = top_y + height - PRIORITY_ITEM_HEIGHT;
    ulDrawFillRect(top_x, priorityItemY, top_x + width, priorityItemY + PRIORITY_ITEM_HEIGHT, C_BLUE_MIDNIGHT_NAVY);

    // Priority item icon
    drawIcon(LUCIDE_12_TABLE[LUCIDE_12_ICON_CALENDAR], top_x + PRIORITY_ITEM_ICON_OFFSET_X, priorityItemY + PRIORITY_ITEM_ICON_OFFSET_Y, C_BLUE_MAYA_BLUE);

    // Priority item event name
    selectFont(FONT_PROGGY_10);
    ulSetTextColor(C_WHITE);
    drawStringBaselineAligned(top_x + PRIORITY_ITEM_SUBJECT_PADDING_X, priorityItemY + PRIORITY_ITEM_TEXT_OFFSET_Y, priority_event.event_name);

    // Priority item time, right-aligned
    selectFont(FONT_PROGGY_12B);
    ulSetTextColor(C_WHITE);
    drawStringBaselineAlignedRightAligned(
        top_x + width - PRIORITY_ITEM_TIME_OFFSET_X, priorityItemY + PRIORITY_ITEM_TEXT_OFFSET_Y, priority_event.time);

    // Priority item divider
    ulDrawLine(top_x, priorityItemY, top_x + width, priorityItemY, C_BLUE_DEEP_OCEAN_BLUE);
}