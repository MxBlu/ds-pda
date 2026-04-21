#include <nds.h>
#include <ulib/ulib.h>
#include <stdio.h>
#include <time.h>
#include "proggy_square_13_bin.h"

// ---------------------------------------------------------------------------
// Colour palette  (RGB15 = 5-bit per channel, 0-31)
// ---------------------------------------------------------------------------
#define C_BG        RGB15(2,  3,  5)   // Very dark navy
#define C_BORDER    RGB15(0,  18, 18)  // Teal outline
#define C_HEADER    RGB15(3,  4,  8)   // Slightly lighter header band

#define C_WEATHER   RGB15(10, 6,  4)   // Warm brown
#define C_TRAIN     RGB15(4,  6,  11)  // Cool blue
#define C_TASKS     RGB15(4,  8,  5)   // Green
#define C_BUDGET    RGB15(8,  4,  9)   // Purple

#define C_WHITE     RGB15(31, 31, 31)
#define C_GREY      RGB15(12, 12, 14)
#define C_LTGREY    RGB15(20, 20, 22)
#define C_ORANGE    RGB15(31, 18, 0)
#define C_GREEN     RGB15(0,  28, 12)
#define C_GREEN_TXT RGB15(0,  31, 16)
#define C_YELLOW    RGB15(31, 28, 0)
#define C_TEAL      RGB15(0,  24, 20)
#define C_RED       RGB15(28, 6,  4)
#define C_BADGE_NSW RGB15(8,  4,  14) // purple-ish badge

// Day-of-week and month name tables
static const char *DAY_NAMES[]   = {"SUNDAY","MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY","SATURDAY"};
static const char *MONTH_NAMES[] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------
void drawBox(int x, int y, int w, int h, u16 bg, u16 border) {
    ulDrawFillRect(x, y, x + w, y + h, bg);
    ulDrawLine(x,     y,     x + w, y,     border);
    ulDrawLine(x,     y + h, x + w, y + h, border);
    ulDrawLine(x,     y,     x,     y + h, border);
    ulDrawLine(x + w, y,     x + w, y + h, border);
}

// Small filled rectangle badge with text centred inside
void drawBadge(int x, int y, int w, int h, u16 bg, u16 fg, const char *txt) {
    ulDrawFillRect(x, y, x + w, y + h, bg);
    ulSetTextColor(fg);
    ulDrawString(x + 2, y + 1, txt);
}

// ---------------------------------------------------------------------------
// Main
// ---------------------------------------------------------------------------
int main(void) {
    // 1. VRAM for 3D hardware
    vramSetBankA(VRAM_A_TEXTURE);
    vramSetBankB(VRAM_B_TEXTURE);
    vramSetBankE(VRAM_E_TEX_PALETTE);

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

    char textBuf[64];

    // Layout constants -- DS top screen is 256 x 192
    const int PAD     = 3;
    const int HDR_H   = 20;           // header band height
    const int BOX_TOP = HDR_H + PAD;  // y where widget rows start
    const int COL_W   = 124;          // width of each column
    const int COL2_X  = PAD + COL_W + PAD; // x of right column
    const int ROW1_H  = 100;          // height of top widget row
    const int ROW2_Y  = BOX_TOP + ROW1_H + PAD;
    const int ROW2_H  = 192 - ROW2_Y - PAD; // fill to bottom

    while (1) {
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);

        ulStartDrawing2D();

        // ---- Background ----
        ulDrawFillRect(0, 0, 256, 192, C_BG);

        // ---- Header band ----
        ulDrawFillRect(0, 0, 256, HDR_H, C_HEADER);
        ulDrawLine(0, HDR_H, 256, HDR_H, C_BORDER);

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

        // ---- Widget boxes ----
        drawBox(PAD,     BOX_TOP, COL_W, ROW1_H, C_WEATHER, C_BORDER); // Weather TL
        drawBox(COL2_X,  BOX_TOP, COL_W, ROW1_H, C_TRAIN,   C_BORDER); // Train TR
        drawBox(PAD,     ROW2_Y,  COL_W, ROW2_H, C_TASKS,   C_BORDER); // Tasks BL
        drawBox(COL2_X,  ROW2_Y,  COL_W, ROW2_H, C_BUDGET,  C_BORDER); // Budget BR

        // ================================================================
        // WEATHER widget (top-left)
        // ================================================================
        int wx = PAD + 4;
        int wy = BOX_TOP + 4;

        ulSetTextColor(C_ORANGE);
        ulDrawString(wx, wy, "WEATHER");

        // "NSW" badge top-right of weather box
        drawBadge(PAD + COL_W - 26, BOX_TOP + 4, 24, 11, C_BADGE_NSW, C_WHITE, "NSW");

        // Large temperature
        ulSetTextColor(C_WHITE);
        ulDrawString(wx, wy + 18, "22 C");

        // 3 forecast columns  (spaced evenly in COL_W)
        // Each column is ~38px wide; labels + temps
        ulSetTextColor(C_LTGREY);
        ulDrawString(wx,      wy + 50, "5P");
        ulDrawString(wx + 38, wy + 50, "9P");
        ulDrawString(wx + 76, wy + 50, "9P");

        ulSetTextColor(C_GREY);
        ulDrawString(wx,      wy + 64, "24");
        ulDrawString(wx + 38, wy + 64, "19");
        ulDrawString(wx + 76, wy + 64, "14");

        // ================================================================
        // NEXT TRAIN widget (top-right)
        // ================================================================
        int tx = COL2_X + 4;
        int ty = BOX_TOP + 4;

        ulSetTextColor(C_WHITE);
        ulDrawString(tx, ty, "NEXT TRAIN");

        // Large time
        ulSetTextColor(C_WHITE);
        ulDrawString(tx, ty + 16, "08:10");

        // LIVE badge
        ulSetTextColor(C_GREEN);
        ulDrawString(tx + 60, ty + 16, "LIVE");

        // Station
        ulSetTextColor(C_TEAL);
        ulDrawString(tx + 4, ty + 34, "OLYMPIC PK");

        // Status
        ulSetTextColor(C_LTGREY);
        ulDrawString(tx + 4, ty + 50, "T1: ON TIME");

        // ================================================================
        // TASKS widget (bottom-left)
        // ================================================================
        int qx = PAD + 4;
        int qy = ROW2_Y + 4;

        ulSetTextColor(C_WHITE);
        ulDrawString(qx, qy, "TASKS");

        ulSetTextColor(C_GREY);
        ulDrawString(qx, qy + 14, "EXPIRED");

        // ================================================================
        // BUDGET widget (bottom-right)
        // ================================================================
        int bx = COL2_X + 4;
        int by = ROW2_Y + 4;

        ulSetTextColor(C_WHITE);
        ulDrawString(bx, by, "BUDGET");
        ulDrawString(bx, by + 14, "$450 / $800");

        // Progress bar
        int barW = COL_W - 8;
        int filledW = (barW * 56) / 100;
        int barY = by + 30;
        ulDrawFillRect(bx, barY, bx + barW, barY + 8, C_GREY);
        ulDrawFillRect(bx, barY, bx + filledW, barY + 8, RGB15(18, 8, 22));

        // ---- End frame ----
        ulEndDrawing();
        ulSyncFrame();
    }

    return 0;
}