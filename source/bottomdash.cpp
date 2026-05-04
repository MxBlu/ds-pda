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

}

void drawTabBar() {
   // Draw tab-bar background (inactive tab colour)
   ulDrawFillRect(0, 0, SCREEN_WIDTH, 24, C_GREY_CHARCOAL);

   // Draw tabs (and dividers)
   for (int i = 0; i <= 4; i++) {
      int centreLine = 51 * i;
      auto &tab = tm->tabs[i];

      int iconOffset = i < 4 ? 17 : 18;
      bool isActive = tm->activeTab == i;

      drawIcon(tab->icon, centreLine + iconOffset, 4, isActive ? C_WHITE : C_GREY);

      if (i > 0) {
         ulDrawFillRect(centreLine - 1, 0, centreLine + 1, 24, C_BLACK);
      }
   }

   // Tab bar separator line
   ulDrawLine(0, 24, SCREEN_WIDTH, 24, C_BLACK);
}

void drawFooter() {
   ulDrawFillRect(0, SCREEN_HEIGHT - 20, SCREEN_WIDTH, SCREEN_HEIGHT, C_GREY_CHARCOAL);

   selectFont(FONT_PROGGY_10);
   ulSetTextColor(C_GREEN);
   drawStringBaselineAligned(4, SCREEN_HEIGHT - 14, "ONLINE");
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