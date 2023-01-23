#pragma once
#include <cstdint>

static constexpr uint32_t MEM_SIZE = 0x10000;

static constexpr uint16_t SCREEN_WIDTH = 128;
static constexpr uint16_t SCREEN_HEIGHT = 128;
static constexpr uint16_t PIXEL_COUNT = SCREEN_WIDTH * SCREEN_HEIGHT;
static constexpr uint16_t PIXEL_WORDCOUNT = 1; // RGBA4444
static constexpr uint16_t VIDEO_MEM_SIZE = PIXEL_COUNT * PIXEL_WORDCOUNT;

#define defcolor(r,g,b,a) ((0xF & r) << 12 | (0xF & g) << 8 | (0xF & b) << 4 | (0xF & a))

enum MemMap {
    MemMap_Video = 0x0,
};

