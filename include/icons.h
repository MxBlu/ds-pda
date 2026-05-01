#pragma once

#include <nds.h>

#include <spritesheet/common.h>

bool preloadIcon(lucide_icon_entry_t icon);
void drawIcon(lucide_icon_entry_t icon, int x, int y, u16 colour);