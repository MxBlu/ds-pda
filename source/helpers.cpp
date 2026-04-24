#include <helpers.h>

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

/// @brief Draw a filled rectangle with a border around it. The border is draw within the rectangle dimensions, so the total size of the box is exactly w x h.
/// @param x Top-left corner X coordinate
/// @param y Top-left corner Y coordinate
/// @param w Width of the rectangle (including border)
/// @param h Height of the rectangle (including border)
/// @param bg Background color
/// @param border Border color
/// @param borderThickness Thickness of the border
void drawBox(int x, int y, int w, int h, u16 bg, u16 border, int borderThickness) {
    // Draw border box
    ulDrawFillRect(x, y, x + w, y + h, border);
    // Draw background
    ulDrawFillRect(x + 2, y + 2, x + w - 2, y + h - 2, bg);
}

// Small filled rectangle badge with text centred inside
void drawBadge(int x, int y, int w, int h, u16 bg, u16 fg, const char *txt) {
    // Draw background  
    ulDrawFillRect(x, y, x + w, y + h, bg);
    ulSetTextColor(fg);

    ulDrawString(x + 2, y + 1, txt);
}