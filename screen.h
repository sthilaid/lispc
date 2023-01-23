#pragma once
#include <SDL.h>
#include <cstdint>

class Memory;

class Screen {
public:
    void initialize();
    void render(const Memory& mem);
    void uninitialize();

private:
    static constexpr uint8_t PIXEL_ZOOM = 5;
    
    SDL_Window* m_window { nullptr };
    SDL_Renderer* m_renderer { nullptr };
    SDL_Texture* m_screenTexture { nullptr };
};
    
