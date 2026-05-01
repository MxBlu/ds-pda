#include <vector>
#include <memory>
#include <nds/system.h>
#include <ulib/ulib.h>

#include <topdash.h>
#include <widgets/widget.h>
#include <widgets/budget.h>
#include <widgets/tasks.h>
#include <widgets/train.h>
#include <widgets/weather.h>
#include <widgets/test.h>
#include <date_names.h>
#include <helpers.h>
#include <fonts.h>
#include <icons.h>

class WidgetsManager {
public:
    std::vector<std::unique_ptr<Widget>> widgets;
    int pos_y = 0;

    template<typename T>
    void addWidget() {
        this->widgets.push_back(std::make_unique<T>());
    };

    int getWidgetVerticalSpacing() {
        int rows = (widgets.size() + 1) / 2;

        return rows * (WIDGET_HEIGHT + WIDGET_INNER_PAD);
    }
};

WidgetsManager *wm;

void initTopScreen() {
    wm = new WidgetsManager();
    
    wm->addWidget<WeatherWidget>();
    wm->addWidget<TrainWidget>();
    wm->addWidget<TasksWidget>();
    wm->addWidget<BudgetWidget>();

    for (auto& widget : wm->widgets) {
        for (auto& icon : widget->getPreloadIcons()) {
            preloadIcon(icon);
        }
    }
}

bool canScrollUp() {
    // We can only scroll up if we've scrolled down at least 1 pixel
    return wm->pos_y > 0;
}

bool canScrollDown() {
    int totalWidgetHeight = wm->getWidgetVerticalSpacing();
    int availableHeight = SCREEN_HEIGHT - HDR_H - OUTER_PAD;
    // No point scrolling if widgets fit within available space
    if (totalWidgetHeight <= availableHeight) {
        return false;
    }
    // Check if we've scrolled to the point where the last row of widgets is just visible
    return wm->pos_y + availableHeight < totalWidgetHeight;
}

void updateTopScreen() {
    // Handle inputs
    auto keys = keysHeld();
    // Down - scroll down (move widgets up)
    if (keys & KEY_DOWN && canScrollDown()) {
        int totalWidgetHeight = wm->getWidgetVerticalSpacing();
        int availableHeight = SCREEN_HEIGHT - HDR_H - OUTER_PAD;

        wm->pos_y += 5;
        // Clamp to max scroll position where last row of widgets is just visible
        if (wm->pos_y + availableHeight > totalWidgetHeight) {
            wm->pos_y = totalWidgetHeight - availableHeight;
        }
    }
    // Up - scroll up (move widgets down)
    if (keys & KEY_UP && canScrollUp()) {
        wm->pos_y -= 5;
        // Clamp to minimum scroll position of 0
        if (wm->pos_y < 0) {
            wm->pos_y = 0;
        }
    }
}

void drawHeader(struct tm *tm) {
    char textBuf[64];

    // Get the day of the week
    const char *dayName = DAY_NAMES[tm->tm_wday];
    // Get the month and date in "MON 1" format
    snprintf(textBuf, sizeof(textBuf), "%s %d", MONTH_SHORT_NAMES[tm->tm_mon], tm->tm_mday);
    // Calculate length of day name for positioning date text
    int dayLen = ulGetStringWidth(dayName);

    // Redraw the background for the header area (in case of artifacts from widgets)
    ulDrawFillRect(0, 0, SCREEN_WIDTH, HDR_H + OUTER_PAD, C_BG);

    // Draw day name
    selectFont(FONT_PROGGY_10);
    ulSetTextColor(C_DAY_TXT);
    drawStringBaselineAligned(OUTER_PAD, HDR_TEXT_Y, dayName);
    // Draw month + date, positioned after day name + 1 space
    selectFont(FONT_PROGGY_12B);
    ulSetTextColor(C_DATETIME_TXT);
    drawStringBaselineAligned(OUTER_PAD + dayLen + 8, HDR_TEXT_Y, textBuf);

    // Clock right-aligned
    selectFont(FONT_PROGGY_16B);
    ulSetTextColor(C_WHITE);
    snprintf(textBuf, sizeof(textBuf), "%02d:%02d", tm->tm_hour, tm->tm_min);
    drawStringBaselineAlignedRightAligned(SCREEN_WIDTH - OUTER_PAD, HDR_TEXT_Y, textBuf);

    // Draw header separator line
    ulDrawLine(OUTER_PAD, HDR_H - 1, SCREEN_WIDTH - OUTER_PAD, HDR_H - 1, C_HEADER_SEP);
}

void drawTopScreen(struct tm *tm) {
    selectFont(FONT_PROGGY_10);
    // Set background colour
    ulDrawFillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, C_BG);

    // Draw widgets, positioned in rows with 8px padding, max 2 per row
    int draw_cursor_x = OUTER_PAD;
    int draw_cursor_y = HDR_H + OUTER_PAD - wm->pos_y; // Add scroll offset to Y position
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
