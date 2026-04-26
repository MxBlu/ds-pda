#include <topdash.h>
#include <widgets/widget.h>
#include <widgets/budget.h>
#include <widgets/tasks.h>
#include <widgets/train.h>
#include <widgets/weather.h>
#include <widgets/test.h>
#include <date_names.h>
#include <helpers.h>

#include <vector>
#include <memory>
#include <nds/system.h>
#include <ulib/ulib.h>

class WidgetsManager {
public:
    std::vector<std::unique_ptr<Widget>> widgets;

    template<typename T>
    void addWidget() {
        this->widgets.push_back(std::make_unique<T>());
    };
};

WidgetsManager *wm;

void initTopScreenWidgets() {
    wm = new WidgetsManager();
    
    wm->addWidget<WeatherWidget>();
    wm->addWidget<TrainWidget>();
    wm->addWidget<TasksWidget>();
    wm->addWidget<BudgetWidget>();
}

void drawHeader(struct tm *tm) {
    char textBuf[64];

    // Get the day of the week
    const char *dayName = DAY_NAMES[tm->tm_wday];
    // Get the month and date in "MON 1" format
    snprintf(textBuf, sizeof(textBuf), "%s %d", MONTH_SHORT_NAMES[tm->tm_mon], tm->tm_mday);
    // Calculate length of day name for positioning date text
    int dayLen = 0;
    while (dayName[dayLen]) dayLen++;

    // Redraw the background for the header area (in case of artifacts from widgets)
    ulDrawFillRect(0, 0, SCREEN_WIDTH, HDR_H + OUTER_PAD, C_BG);

    // Draw day name
    ulSetTextColor(C_DAY_TXT);
    ulDrawString(OUTER_PAD, HDR_TEXT_Y, dayName);
    // Draw month + date, positioned after day name + 1 space (8px per char)
    ulSetTextColor(C_DATETIME_TXT);
    ulDrawString(OUTER_PAD + (dayLen + 1) * 8, HDR_TEXT_Y, textBuf);

    // Clock right-aligned: 5 chars wide = 40px, place at 256-40-PAD
    ulSetTextColor(C_WHITE);
    snprintf(textBuf, sizeof(textBuf), "%02d:%02d", tm->tm_hour, tm->tm_min);
    ulDrawString(SCREEN_WIDTH - OUTER_PAD - (8 * 5), HDR_TEXT_Y, textBuf);

    // Draw header separator line
    ulDrawLine(OUTER_PAD, HDR_H - 1, SCREEN_WIDTH - OUTER_PAD, HDR_H - 1, C_HEADER_SEP);
}

void drawTopScreen(struct tm *tm) {
    // Set background colour
    ulDrawFillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, C_BG);

    // Draw widgets, positioned in rows with 8px padding, max 2 per row
    int draw_cursor_x = OUTER_PAD;
    int draw_cursor_y = HDR_H + OUTER_PAD;
    int row_widget_count = 0;
    for (auto& widget : wm->widgets) {
        widget->draw(draw_cursor_x, draw_cursor_y, WIDGET_WIDTH, WIDGET_HEIGHT);
        draw_cursor_x += WIDGET_WIDTH + WIDGET_INNER_PAD;
        row_widget_count++;
        if (row_widget_count >= 2) {
            draw_cursor_x = OUTER_PAD;
            draw_cursor_y += WIDGET_HEIGHT + WIDGET_INNER_PAD;
            row_widget_count = 0;
        }
    }

    // Draw the header elements
    // We draw this last so it appears above the widgets
    drawHeader(tm);
}