#ifndef LUCIDE_SPRITESHEET_16_H
#define LUCIDE_SPRITESHEET_16_H

#include "common.h"

#define LUCIDE_16_SHEET_0_WIDTH 64
#define LUCIDE_16_SHEET_0_HEIGHT 64

#define LUCIDE_16_ICON_SIZE 16
#define LUCIDE_16_ICON_COUNT 13

typedef enum lucide_16_icon_id {
  LUCIDE_16_ICON_CLOUD = 0,
  LUCIDE_16_ICON_CLOUD_DRIZZLE = 1,
  LUCIDE_16_ICON_CLOUD_FOG = 2,
  LUCIDE_16_ICON_CLOUD_LIGHTNING = 3,
  LUCIDE_16_ICON_CLOUD_RAIN = 4,
  LUCIDE_16_ICON_CLOUD_SUN = 5,
  LUCIDE_16_ICON_CLOUDY = 6,
  LUCIDE_16_ICON_INFO = 7,
  LUCIDE_16_ICON_MOON = 8,
  LUCIDE_16_ICON_OCTAGON_ALERT = 9,
  LUCIDE_16_ICON_SNOWFLAKE = 10,
  LUCIDE_16_ICON_SUN = 11,
  LUCIDE_16_ICON_TRIANGLE_ALERT = 12,
} lucide_16_icon_id_t;

static const lucide_icon_entry_t LUCIDE_16_TABLE[13] = {
  {0, 0, 0, 16},
  {0, 16, 0, 16},
  {0, 32, 0, 16},
  {0, 48, 0, 16},
  {0, 0, 16, 16},
  {0, 16, 16, 16},
  {0, 32, 16, 16},
  {0, 48, 16, 16},
  {0, 0, 32, 16},
  {0, 16, 32, 16},
  {0, 32, 32, 16},
  {0, 48, 32, 16},
  {0, 0, 48, 16},
};

#define LUCIDE_16_ICON_SHEET(icon_id) (LUCIDE_16_ICON_TABLE[(icon_id)].sheet)
#define LUCIDE_16_ICON_U(icon_id) (LUCIDE_16_ICON_TABLE[(icon_id)].u)
#define LUCIDE_16_ICON_V(icon_id) (LUCIDE_16_ICON_TABLE[(icon_id)].v)
#define LUCIDE_16_ICON_ENTRY_SIZE(icon_id) (LUCIDE_16_ICON_TABLE[(icon_id)].size)

#endif /* LUCIDE_SPRITESHEET_16_H */
