#pragma once

#include <external/s7.h>

class Memory;
class Screen;

//-----------------------------------------------------------------------------
// lispc_api

namespace lispc_api {
    void randomize_video_mem(Memory& mem, const Screen& screen);
}

//-----------------------------------------------------------------------------
// lispc_s7_api

class lispc_s7_api {
public:
    static s7_pointer s_MemoryType;
    static s7_pointer s_ScreenType;
    
    static void register_functions(s7_scheme* sc, Memory& mem, Screen& screen);

private:    
    static s7_pointer randomize_video_mem(s7_scheme *sc, s7_pointer args);

    static bool s_IsInitialized;
    
};
