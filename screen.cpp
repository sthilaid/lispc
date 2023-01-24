#include <screen.h>
#include <memory.h>
#include <types.h>

#include <random>

void Screen::initialize() {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    } else {
        m_window = SDL_CreateWindow( "LEM1802 - Low Energy Monitor",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SCREEN_WIDTH * PIXEL_ZOOM,
                                     SCREEN_HEIGHT * PIXEL_ZOOM,
                                     SDL_WINDOW_SHOWN );
        if( m_window == nullptr ) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        } else {
            m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );
            if( m_renderer == nullptr ) {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            } else {
                SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                m_screenTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA4444, SDL_TEXTUREACCESS_STREAMING,
                                                    SCREEN_WIDTH, SCREEN_HEIGHT);
                if (m_screenTexture == nullptr) {
                    printf( "texture could not be created! SDL_Error: %s\n", SDL_GetError() );
                } 
            }
        }
    }
}

void Screen::uninitialize() {
    SDL_DestroyTexture( m_screenTexture );
    SDL_DestroyRenderer( m_renderer );
    SDL_DestroyWindow( m_window );
    SDL_Quit();        
}

void Screen::render(const Memory& mem) {
    uint16_t* pixels = nullptr;
    int pitch = 0;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);
        
    SDL_LockTexture(m_screenTexture, nullptr, (void**)&pixels, &pitch);

    for (uint32_t i=0; i<PIXEL_COUNT; ++i) {
        pixels[i] = mem[MemMap_Video + i];
    }

    SDL_UnlockTexture(m_screenTexture);
        
    SDL_RenderClear( m_renderer );
    SDL_RenderCopy( m_renderer, m_screenTexture, nullptr, nullptr );
    SDL_RenderPresent( m_renderer );
}

void Screen::drawRect(float x1, float y1, float x2, float y2, uint16_t color) {
    SDL_SetRenderTarget(m_renderer, m_screenTexture);

    SDL_Rect fillRect = { static_cast<uint16_t>(x1*SCREEN_WIDTH),
                          static_cast<uint16_t>(y1 * SCREEN_HEIGHT),
                          static_cast<uint16_t>((x2-x1) * SCREEN_WIDTH),
                          static_cast<uint16_t>((y2-y1) * SCREEN_HEIGHT) };
    uint8_t r,g,b,a;
    color_to_rgba(color, r, g, b, a);
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);;
    SDL_RenderFillRect(m_renderer, &fillRect);

    SDL_SetRenderTarget(m_renderer, nullptr);
}
