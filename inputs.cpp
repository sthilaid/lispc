#include <inputs.h>
#include <cstring>

void Inputs::update() {
    memset(this, 0, sizeof(*this));
    
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
        case SDL_QUIT:
            m_quit = true;
            break;
        case SDL_KEYDOWN:
        keydown:
            if (e.key.keysym.sym == SDLK_q) {
                m_quit = true;
            }
            break;
        }
    }
}
