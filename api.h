#pragma once

#include <external/s7.h>

class Memory;
class Screen;
class Inputs;

//-----------------------------------------------------------------------------
// lispc_api

namespace lispc_api {
    void randomize_video_mem(Memory& mem, const Screen& screen);
    uint16_t memget(Memory& mem, uint16_t addr);
    void memset(Memory& mem, uint16_t addr, uint16_t value);
    void rect(Screen& screen, float x1, float y1, float x2, float y2, uint16_t color);
    void cls(Memory& mem, uint16_t color);
}

//-----------------------------------------------------------------------------
// singleton (inspired by https://codereview.stackexchange.com/questions/173929/modern-c-singleton-template)

template<typename T>
class singleton {
public:
    singleton(const singleton&) = delete;
    singleton& operator=(singleton&) = delete;
    
    static T& get() {
        static T instance{};
        return instance;
    }

protected:
    singleton() {};
};

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

class lispc_s7_api : public lispc_external_api, public singleton<lispc_s7_api>{
public:
    void init(Memory& mem, Screen& screen, Inputs& inputs) override;
    bool load(const char* filename) override;
    void update(float dt) override;
    void uninit() override;

private:    
    static s7_pointer randomize_video_mem(s7_scheme *sc, s7_pointer args);
    static s7_pointer rect(s7_scheme *sc, s7_pointer args);
    static s7_pointer cls(s7_scheme *sc, s7_pointer args);

    void register_functions(s7_scheme* sc, Memory& mem, Screen& screen);

    bool m_IsInitialized { false };
    s7_pointer m_MemoryType;
    s7_pointer m_ScreenType;

    s7_scheme* m_sc { nullptr };
    Memory* m_mem { nullptr };
    Screen* m_screen { nullptr };
    Inputs* m_inputs { nullptr };
};
