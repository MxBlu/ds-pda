#include <nds.h>
#include <ulib/ulib.h>
#include <stdio.h>

#include <topdash.h>

#include "proggy_square_13_bin.h"

// ---------------------------------------------------------------------------
// Main
// ---------------------------------------------------------------------------
int main(void) {
    // 1. VRAM for 3D hardware
    // vramSetBankA(VRAM_A_TEXTURE);
    // vramSetBankB(VRAM_B_TEXTURE);
    // vramSetBankE(VRAM_E_TEX_PALETTE);

    // 2. Bottom screen debug console
    videoSetModeSub(MODE_0_2D);
    vramSetBankC(VRAM_C_SUB_BG);
    consoleInit(NULL, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
    printf("\n  PDA OS Initialized.\n  Bottom screen ready.");

    // 3. µLibrary init
    ulInit(UL_INIT_ALL);
    ulInitGfx();

    UL_FONT *font = ulLoadFontFile((const char *)proggy_square_13_bin, (int)proggy_square_13_bin_size);
    if (!font) printf("\n Failed to load font!");
    ulSetFont(font);

    initTopScreenWidgets();

    while (1) {
        // Get current time
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);

        ulStartDrawing2D();

        drawTopScreen(tm);

        // ---- End frame ----
        ulEndDrawing();
        ulSyncFrame();
    }

    return 0;
}