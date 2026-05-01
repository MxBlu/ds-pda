#pragma once

#include <ulib/ulib.h>

void drawBox(int x, int y, int w, int h, u16 bg, u16 border, int borderThickness);

// Small filled rectangle badge with text centred inside
void drawBadge(int x, int y, int w, int h, u16 bg, u16 fg, const char *txt);

void drawCircle(int cx, int cy, int r, u16 colour);
void drawFilledCircle(int cx, int cy, int r, u16 colour);