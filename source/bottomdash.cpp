#include <vector>
#include <memory>
#include <nds.h>
#include <ulib/ulib.h>

#include <bottomdash.h>

#include <spritesheet/spritesheet_16.h>
#include <helpers.h>
#include <colours.h>
#include <fonts.h>
#include <icons.h>

#include <tabs/tab.h>
#include <tabs/mail.h>
#include <tabs/calendar.h>
#include <tabs/train.h>
#include <tabs/tasks.h>
#include <tabs/budget.h>

class TabManager {
public:
    std::vector<std::unique_ptr<Tab>> tabs;
    int activeTab = 0;

    template<typename T>
    void addTab() {
        this->tabs.push_back(std::make_unique<T>());
    };
};

TabManager *tm;

void initBottomScreen() {
    tm = new TabManager();

    tm->addTab<MailTab>();
    tm->addTab<CalendarTab>();
    tm->addTab<TrainTab>();
    tm->addTab<TasksTab>();
    tm->addTab<BudgetTab>();
}

void updateBottomScreen() {
    // Handle tab switching
    if (ul_keys.touch.click) {
        int touchX = ul_keys.touch.x;
        int touchY = ul_keys.touch.y;

        if (touchY < TAB_BAR_HEIGHT) {
            uint tabIndex = touchX / TAB_WIDTH;
            if (tabIndex < tm->tabs.size()) {
                tm->activeTab = tabIndex;
            }
        }
    }
}

void drawTabBar() {
    // Draw tab-bar background (inactive tab colour)
    ulDrawFillRect(0, 0, SCREEN_WIDTH, TAB_BAR_HEIGHT, C_TAB_INACTIVE_BG);

    // Draw tabs (and dividers)
    for (int i = 0; i <= TAB_COUNT - 1; i++) {
        int centreLine = TAB_WIDTH * i;
        auto &tab = tm->tabs[i];

        int iconOffset = i < TAB_COUNT - 1 ? TAB_ICON_OFFSET : TAB_LAST_ICON_OFFSET;
        bool isActive = tm->activeTab == i;

        u16 iconColour = C_TAB_ICON_INACTIVE;
        if (isActive) {
            ulDrawFillRect(centreLine + 1, 0, centreLine + TAB_WIDTH, TAB_BAR_HEIGHT, C_TAB_ACTIVE_BG);
            iconColour = C_TAB_ICON_ACTIVE;
        }

        drawIcon(tab->icon, centreLine + iconOffset, TAB_ICON_Y, iconColour);

        if (i > 0) {
            ulDrawFillRect(centreLine - 1, 0, centreLine + 1, TAB_BAR_HEIGHT, C_BLACK);
        }
    }

    // Tab bar separator line
    ulDrawLine(0, TAB_BAR_HEIGHT, SCREEN_WIDTH, TAB_BAR_HEIGHT, C_BLACK);
}

void drawFooter() {
    ulDrawFillRect(0, SCREEN_HEIGHT - FOOTER_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, C_FOOTER_BG);

    selectFont(FONT_PROGGY_10);
    ulSetTextColor(C_FOOTER_STATUS);
    drawStringBaselineAligned(FOOTER_TEXT_X, SCREEN_HEIGHT - FOOTER_TEXT_Y_OFFSET, "ONLINE");
}

void drawBottomScreen() {
    // Set background colour   
    ulDrawFillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, C_BG);

    // Tab bar
    drawTabBar();

    // Work area

    // Footer
    drawFooter();
}