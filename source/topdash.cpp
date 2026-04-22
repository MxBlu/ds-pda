#include <topdash.h>
#include <widgets/widget.h>
#include <widgets/budget.h>
#include <widgets/tasks.h>
#include <widgets/train.h>
#include <widgets/weather.h>
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

void drawTopScreen(struct tm *tm) {
    char textBuf[64];

    // ---- Background ----
    ulDrawFillRect(0, 0, 256, 192, C_TOP_BG);

    // ---- Header band ----
    ulDrawFillRect(0, 0, 256, HDR_H, C_TOP_HEADER);
    ulDrawLine(0, HDR_H, 256, HDR_H, C_TOP_BORDER);

    // Day + date  e.g. "MONDAY  APR 20"
    ulSetTextColor(C_WHITE);
    const char *dayName = DAY_NAMES[tm->tm_wday];
    ulDrawString(PAD + 2, 4, dayName);

    ulSetTextColor(C_TEAL);
    // Each char is 8px wide; advance past day name + 1 space
    int dayLen = 0;
    while (dayName[dayLen]) dayLen++;
    snprintf(textBuf, sizeof(textBuf), "%s %d", MONTH_NAMES[tm->tm_mon], tm->tm_mday);
    ulDrawString(PAD + 2 + (dayLen + 1) * 8, 4, textBuf);

    // Clock right-aligned: 5 chars wide = 40px, place at 256-40-PAD
    ulSetTextColor(C_WHITE);
    snprintf(textBuf, sizeof(textBuf), "%02d:%02d", tm->tm_hour, tm->tm_min);
    ulDrawString(256 - 40 - PAD, 4, textBuf);

    int draw_cursor_x = PAD;
    int draw_cursor_y = HDR_H + PAD;
    for (auto& widget : wm->widgets) {
        widget->draw(draw_cursor_x, draw_cursor_y, WIDGET_WIDTH, WIDGET_HEIGHT);
        draw_cursor_x += WIDGET_WIDTH + PAD;
        if (draw_cursor_x > SCREEN_WIDTH) {
            draw_cursor_x = PAD;
            draw_cursor_y += WIDGET_HEIGHT + PAD;
        }
    }
}