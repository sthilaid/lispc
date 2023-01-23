#pragma once

#include <SDL.h>

struct Inputs {
    void update();

    bool m_quit = false;
};
