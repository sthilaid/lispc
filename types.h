#pragma once
#include <cstdint>
#include <algorithm>

static constexpr uint32_t MEM_SIZE = 0x10000;

static constexpr uint16_t SCREEN_WIDTH = 128;
static constexpr uint16_t SCREEN_HEIGHT = 128;
static constexpr uint16_t PIXEL_COUNT = SCREEN_WIDTH * SCREEN_HEIGHT;
static constexpr uint16_t PIXEL_BYTECOUNT = 2; // RGBA4444
static constexpr uint16_t PIXEL_WORDCOUNT = 1;
static constexpr uint16_t VIDEO_MEM_SIZE = PIXEL_COUNT * PIXEL_BYTECOUNT;

enum MemMap {
    MemMap_Video = 0x0,
};

constexpr uint16_t defcolor_el(float x, uint8_t shl) {
    return (static_cast<uint8_t>(std::min(0.999f, x) / (1.0f / 16.0f)) & 0xf) << shl;
}
constexpr uint16_t defcolor(float r, float g, float b, float a)  {
    return defcolor_el(r, 12) | defcolor_el(g, 8) | defcolor_el(b, 4) | defcolor_el(a, 0);
}

inline void color_to_rgba(uint16_t color, uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a) {
    r = (color >> 12) << 4;
    g = ((color >> 8) & 0xF) << 4;
    b = ((color >> 4) & 0xF) << 4;
    a = ((color >> 0) & 0xF) << 4;
}

static constexpr uint16_t color_white = defcolor(1.0f, 1.0f, 1.0f, 1.0f);
static constexpr uint16_t color_black = defcolor(0.0f, 0.0f, 0.0f, 1.0f);
static constexpr uint16_t color_red = defcolor(1.0f, 0.0f, 0.0f, 1.0f);
static constexpr uint16_t color_green = defcolor(0.0f, 1.0f, 0.0f, 1.0f);
static constexpr uint16_t color_blue = defcolor(0.0f, 0.0f, 1.0f, 1.0f);
static constexpr uint16_t color_cyan = defcolor(0.0f, 1.0f, 1.0f, 1.0f);
static constexpr uint16_t color_yellow = defcolor(1.0f, 1.0f, 0.0f, 1.0f);
static constexpr uint16_t color_purple = defcolor(1.0f, 0.0f, 1.0f, 1.0f);
