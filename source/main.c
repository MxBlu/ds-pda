#include <nds.h>
#include <ulib/ulib.h>
#include <stdio.h>
#include <time.h>
#include "proggy_square_13_bin.h"

// µLibrary uses standard 15-bit DS colors.
// No need for BIT(15) in 3D mode!
#define C_CHARCOAL  RGB15(4, 4, 4)
#define C_LINE      RGB15(0, 0, 0)
#define C_WEATHER   RGB15(10, 6, 4)
#define C_TRAIN     RGB15(4, 6, 10)
#define C_TASKS     RGB15(4, 8, 5)
#define C_BUDGET    RGB15(8, 4, 9)

#define C_WHITE     RGB15(31, 31, 31)
#define C_GREY      RGB15(15, 15, 15)
#define C_ORANGE    RGB15(31, 16, 0)
#define C_GREEN     RGB15(0, 31, 0)

// Helper to draw a filled box with an outline using ulib
void drawWidgetBox(int x, int y, int w, int h, u16 bgColor, u16 outlineColor) {
    // Draw the background fill (x1, y1, x2, y2)
    ulDrawFillRect(x, y, x + w, y + h, bgColor);
    
    // Draw the 4 outline borders using lines
    ulDrawLine(x, y, x + w, y, outlineColor);                 // Top
    ulDrawLine(x, y + h, x + w, y + h, outlineColor);         // Bottom
    ulDrawLine(x, y, x, y + h, outlineColor);                 // Left
    ulDrawLine(x + w, y, x + w, y + h, outlineColor);         // Right
}

int main(void) {
    // 1. ALLOCATE VRAM FOR 3D HARDWARE (Fixes the White Screen bug)
    vramSetBankA(VRAM_A_TEXTURE);        // Give 3D engine texture memory
    vramSetBankB(VRAM_B_TEXTURE);        // (Needed for uLibrary's internal font)
    vramSetBankE(VRAM_E_TEX_PALETTE);    // Give 3D engine palette memory

    // 2. Initialize the Bottom Screen so it isn't blinding white
    videoSetModeSub(MODE_0_2D);
    vramSetBankC(VRAM_C_SUB_BG);
    consoleInit(NULL, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
    printf("\n  PDA OS Initialized.\n  Bottom screen ready.");

    // 3. Initialize µLibrary (Sets up Top Screen 3D core automatically)
    ulInit(UL_INIT_ALL);

    // Initialize the graphical part
    ulInitGfx();
    
    UL_FONT *font = ulLoadFontFile((const char *)proggy_square_13_bin, (int)proggy_square_13_bin_size);
    if (!font) {
        printf("\n Failed to load font!");
    }
    ulSetFont(font);

    // Buffer for formatting dynamic strings
    char textBuf[32];

    // Main Game Loop
    while (1) {
        // Read the actual DS internal hardware clock
        time_t t = time(NULL);
        struct tm *timeinfo = localtime(&t);

        // Begin the 2D-in-3D rendering phase
        ulStartDrawing2D();
        
        // Clear background
        ulDrawFillRect(0, 0, 256, 192, C_CHARCOAL);

        // Header Separator Line
        ulDrawLine(0, 14, 256, 14, C_LINE);

        // --- DRAW WIDGET SHAPES ---
        int pad = 4;
        int boxW = 122; 
        int boxH = 82;  
        int rightColX = pad * 2 + boxW; 
        int bottomRowY = 20 + boxH + pad; 

        drawWidgetBox(pad, 20, boxW, boxH, C_WEATHER, C_LINE);       // Top-Left
        drawWidgetBox(rightColX, 20, boxW, boxH, C_TRAIN, C_LINE);   // Top-Right
        drawWidgetBox(pad, bottomRowY, boxW, boxH, C_TASKS, C_LINE); // Bottom-Left
        drawWidgetBox(rightColX, bottomRowY, boxW, boxH, C_BUDGET, C_LINE); // Bottom-Right

        // Budget Progress Bar (Fixed math: use integer instead of float for hardware safety)
        int barX = rightColX + 4;
        int barY = bottomRowY + 50;
        int barInnerW = boxW - 8;
        int filledPixels = (barInnerW * 56) / 100; // 56% filled
        
        ulDrawFillRect(barX, barY, barX + barInnerW, barY + 10, C_GREY); // BG
        ulDrawFillRect(barX, barY, barX + filledPixels, barY + 10, RGB15(20, 10, 25)); // Fill

        // --- DRAW TEXT ---
        // Header
        ulSetTextColor(C_GREY);
        ulDrawString(4, 2, "TODAY");
        ulSetTextColor(C_WHITE);
        
        // Dynamic Date & Clock
        snprintf(textBuf, sizeof(textBuf), "%02d/%02d", timeinfo->tm_mday, timeinfo->tm_mon + 1);
        ulDrawString(45, 2, textBuf);
        
        snprintf(textBuf, sizeof(textBuf), "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
        ulDrawString(190, 2, textBuf); // Shifted X slightly left to avoid off-screen overflow

        // Weather
        ulSetTextColor(C_ORANGE);
        ulDrawString(pad + 4, 24, "WEATHER");
        ulSetTextColor(C_WHITE);
        ulDrawString(pad + 4, 38, "22 C");

        // Transport
        ulSetTextColor(C_WHITE);
        ulDrawString(rightColX + 4, 24, "NEXT TRAIN");
        ulDrawString(rightColX + 4, 38, "08:10");
        ulSetTextColor(C_GREEN);
        ulDrawString(rightColX + 40, 38, "LIVE");

        // Tasks
        ulSetTextColor(C_WHITE);
        ulDrawString(pad + 4, bottomRowY + 4, "TASKS");
        ulSetTextColor(C_GREY);
        ulDrawString(pad + 4, bottomRowY + 18, "! Buy Milk");

        // Budget
        ulSetTextColor(C_WHITE);
        ulDrawString(rightColX + 4, bottomRowY + 4, "BUDGET");
        ulDrawString(rightColX + 4, bottomRowY + 18, "$450 / $800");

        // End rendering and wait for screen refresh
        ulEndDrawing();
        ulSyncFrame(); 
    }

    return 0;
}