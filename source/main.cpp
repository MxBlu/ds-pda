#include <nds.h>
#include <ulib/ulib.h>

#include <topdash.h>
#include <bottomdash.h>
#include <fonts.h>
#include <icons.h>

// ---------------------------------------------------------------------------
// Main
// ---------------------------------------------------------------------------
int main(void) {
    // ulib inits
    ulInit(UL_INIT_ALL);
    ulInitGfx();
    // Dual screen mode, we'll be running 30fps
    ulInitDualScreenMode();

    // App inits
    initFonts();
    initTopScreen();
    initBottomScreen();

    while (1) {
        scanKeys();

        updateTopScreen();
        updateBottomScreen();

        ulStartDrawing2D();

        // Run draws
        if (!ulGetMainLcd()) {
            drawTopScreen();
        } else {
            drawBottomScreen();
        }

        ulEndDrawing();
        ulSyncFrame();
    }

    return 0;
}