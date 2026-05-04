#include <ulib/ulib.h>

#include <icons.h>
#include <spritesheet/spritesheet_12.h>
#include <spritesheet/spritesheet_16.h>

#include "spritesheet_registry.h"

struct sprite_sheet_t {
    UL_IMAGE *image;
    int tileSize;
    int index;
};

static const int SHEET_CACHE_SIZE = 4;
sprite_sheet_t lru_sheets[SHEET_CACHE_SIZE] = {0};
bool lru_sheets_initialized = false;

static void initSheetCache() {
    if (lru_sheets_initialized) {
        return;
    }

    for (int i = 0; i < SHEET_CACHE_SIZE; i++) {
        lru_sheets[i].image = NULL;
        lru_sheets[i].tileSize = 0;
        lru_sheets[i].index = -1;
    }

    lru_sheets_initialized = true;
}

static UL_IMAGE *loadSheetImage(int iconSize, int sheetIndex) {
    for (unsigned int i = 0; i < SPRITESHEET_REGISTRY_COUNT; i++) {
        const spritesheet_registry_entry_t &entry = SPRITESHEET_REGISTRY[i];

        if (entry.size != iconSize || entry.sheet != sheetIndex) {
            continue;
        }

        return ulLoadImageFilePNG((const char *)entry.data, entry.data_size,
                                          UL_IN_VRAM, UL_PF_PAL3_A5);
    }

    return NULL;
}

bool preloadIcon(lucide_icon_entry_t icon) {
    initSheetCache();

    for (int i = 0; i < SHEET_CACHE_SIZE; i++) {
        if (lru_sheets[i].image != NULL &&
             lru_sheets[i].index == icon.sheet &&
             lru_sheets[i].tileSize == icon.size) {
            sprite_sheet_t temp = lru_sheets[i];
            for (int j = i; j < SHEET_CACHE_SIZE - 1; j++) {
                lru_sheets[j] = lru_sheets[j + 1];
            }
            lru_sheets[SHEET_CACHE_SIZE - 1] = temp;
            return false;
        }
    }

    UL_IMAGE *sheetImage = loadSheetImage(icon.size, icon.sheet);
    if (!sheetImage) {
        return false;
    }

    if (lru_sheets[0].image != NULL) {
        ulDeleteImage(lru_sheets[0].image);
    }

    for (int i = 0; i < SHEET_CACHE_SIZE - 1; i++) {
        lru_sheets[i] = lru_sheets[i + 1];
    }

    lru_sheets[SHEET_CACHE_SIZE - 1].image = sheetImage;
    lru_sheets[SHEET_CACHE_SIZE - 1].tileSize = icon.size;
    lru_sheets[SHEET_CACHE_SIZE - 1].index = icon.sheet;

    return true;
}

void drawIcon(lucide_icon_entry_t icon, int x, int y, u16 colour) {
    initSheetCache();
    bool loaded = preloadIcon(icon);
    if (loaded) {
        printf("WARN: Icon sheet %d-%d was not preloaded, loaded on demand\n", icon.size, icon.sheet);
    }

    UL_IMAGE *sheet = NULL;
    for (int i = 0; i < SHEET_CACHE_SIZE; i++) {
        if (lru_sheets[i].image != NULL &&
             lru_sheets[i].index == icon.sheet &&
             lru_sheets[i].tileSize == icon.size) {
            sheet = lru_sheets[i].image;
            break;
        }
    }
    
    if (!sheet) {
        printf("ERR: Sheet %d size %d not in cache, cannot draw icon\n", icon.sheet, icon.size);
        return;
    }

    ulSetImageTint(sheet, colour);
    ulSetImageTileSize(sheet, icon.u, icon.v, icon.size, icon.size);
    ulDrawImageXY(sheet, x, y);
}
