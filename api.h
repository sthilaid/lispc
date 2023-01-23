#pragma once

#include <external/s7.h>

class Memory;
class Screen;
class Inputs;

//-----------------------------------------------------------------------------
// lispc_api

namespace lispc_api {
    void randomize_video_mem(Memory& mem, const Screen& screen);
}

//-----------------------------------------------------------------------------
// lispc_external_api

class lispc_external_api {
public:
    virtual void init(Memory& mem, Screen& screen, Inputs& inputs) = 0;
    virtual bool load(const char* filename) = 0;
    virtual void update(float dt) = 0;
    virtual void uninit() = 0;
};

//-----------------------------------------------------------------------------
// lispc_s7_api

class lispc_s7_api : public lispc_external_api{
public:
    static s7_pointer s_MemoryType;
    static s7_pointer s_ScreenType;
    static void register_functions(s7_scheme* sc, Memory& mem, Screen& screen);

    void init(Memory& mem, Screen& screen, Inputs& inputs) override;
    bool load(const char* filename) override;
    void update(float dt) override;
    void uninit() override;

private:    
    static s7_pointer randomize_video_mem(s7_scheme *sc, s7_pointer args);
    static bool s_IsInitialized;

    s7_scheme* m_sc { nullptr };
};
