#pragma once

#include <nds.h>

// ---------------------------------------------------------------------------
// Colour palette  (RGB15 = 5-bit per channel, 0-31)
// ---------------------------------------------------------------------------

#define C_WEATHER   RGB15(10, 6,  4)   // Warm brown
#define C_TRAIN     RGB15(4,  6,  11)  // Cool blue
#define C_TASKS     RGB15(4,  8,  5)   // Green
#define C_BUDGET    RGB15(8,  4,  9)   // Purple

#define C_WHITE             RGB15(31, 31, 31)
#define C_LTGREY            RGB15(20, 20, 22)
#define C_GREY_STEEL_MIST   RGB15(18, 20, 23)
#define C_GREY              RGB15(12, 12, 14)
#define C_SLTGREY           RGB15(3,  4,  8)
#define C_GREY_DEEP_NIGHT   RGB15(3,  3,  3)

#define C_DKNAVY            RGB15(2,  3,  5)
#define C_BLUE_MIDNIGHT_NAVY RGB15(6, 8, 11)

#define C_TEAL      RGB15(0,  24, 20)
#define C_GREEN     RGB15(0,  28, 12)
#define C_GREEN_TXT RGB15(0,  31, 16)

#define C_ORANGE    RGB15(31, 18, 0)
#define C_YELLOW    RGB15(31, 28, 0)
#define C_RED       RGB15(28, 6,  4)
#define C_BADGE_NSW RGB15(8,  4,  14) // purple-ish badge