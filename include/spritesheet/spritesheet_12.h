#ifndef LUCIDE_SPRITESHEET_12_H
#define LUCIDE_SPRITESHEET_12_H

#include "common.h"

#define LUCIDE_12_SHEET_0_WIDTH 64
#define LUCIDE_12_SHEET_0_HEIGHT 64

#define LUCIDE_12_ICON_SIZE 12
#define LUCIDE_12_ICON_COUNT 13

typedef enum lucide_12_icon_id {
  LUCIDE_12_ICON_CLOUD = 0,
  LUCIDE_12_ICON_CLOUD_DRIZZLE = 1,
  LUCIDE_12_ICON_CLOUD_FOG = 2,
  LUCIDE_12_ICON_CLOUD_LIGHTNING = 3,
  LUCIDE_12_ICON_CLOUD_RAIN = 4,
  LUCIDE_12_ICON_CLOUD_SUN = 5,
  LUCIDE_12_ICON_CLOUDY = 6,
  LUCIDE_12_ICON_INFO = 7,
  LUCIDE_12_ICON_MOON = 8,
  LUCIDE_12_ICON_OCTAGON_ALERT = 9,
  LUCIDE_12_ICON_SNOWFLAKE = 10,
  LUCIDE_12_ICON_SUN = 11,
  LUCIDE_12_ICON_TRIANGLE_ALERT = 12,
} lucide_12_icon_id_t;

static const lucide_icon_entry_t LUCIDE_12_TABLE[13] = {
  {0, 0, 0, 12},
  {0, 12, 0, 12},
  {0, 24, 0, 12},
  {0, 36, 0, 12},
  {0, 0, 12, 12},
  {0, 12, 12, 12},
  {0, 24, 12, 12},
  {0, 36, 12, 12},
  {0, 0, 24, 12},
  {0, 12, 24, 12},
  {0, 24, 24, 12},
  {0, 36, 24, 12},
  {0, 0, 36, 12},
};

#define LUCIDE_12_ICON_SHEET(icon_id) (LUCIDE_12_ICON_TABLE[(icon_id)].sheet)
#define LUCIDE_12_ICON_U(icon_id) (LUCIDE_12_ICON_TABLE[(icon_id)].u)
#define LUCIDE_12_ICON_V(icon_id) (LUCIDE_12_ICON_TABLE[(icon_id)].v)
#define LUCIDE_12_ICON_ENTRY_SIZE(icon_id) (LUCIDE_12_ICON_TABLE[(icon_id)].size)

#endif /* LUCIDE_SPRITESHEET_12_H */
