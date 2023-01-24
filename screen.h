#pragma once
#include <SDL.h>
#include <cstdint>
#include <types.h>

class Memory;

class Screen {
public:
    void initialize();
    void render(const Memory& mem);
    void uninitialize();

    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, uint16_t color = color_white);
    void drawRect(float x1, float y1, float x2, float y2, uint16_t color = color_white);
    
private:
    static constexpr uint8_t PIXEL_ZOOM = 5;
    
    SDL_Window* m_window { nullptr };
    SDL_Renderer* m_renderer { nullptr };
    SDL_Texture* m_screenTexture { nullptr };
};
    
