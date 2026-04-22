#include <helpers.h>

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