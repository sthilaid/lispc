#include <api.h>
#include <memory.h>
#include <screen.h>
#include <inputs.h>

#include <random>

//-----------------------------------------------------------------------------
// lispc_api

void lispc_api::randomize_video_mem(Memory& mem, const Screen& screen) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib;

    for (uint16_t i=0; i<PIXEL_COUNT; ++i) {
        mem[i] = defcolor(distrib(gen), distrib(gen), distrib(gen), 1.0f);
    }
}

uint16_t lispc_api::memget(Memory& mem, uint16_t addr) {
    return mem[addr];
}

void lispc_api::memset(Memory& mem, uint16_t addr, uint16_t value) {
    mem[addr] = value;
}

void lispc_api::rect(Screen& screen, float x1, float y1, float x2, float y2, uint16_t color) {
    screen.drawRect(x1, y1, x2, y2, color);
}

void lispc_api::cls(Memory& mem, uint16_t color) {
    mem.clearVideoMemory(color);
}

//-----------------------------------------------------------------------------
// lispc_s7_api

#define get_ptr(sc, val, valType, ctx, argn) static_cast<valType*>(s7_c_pointer_with_type(sc, val, get().m_##valType##Type, ctx, argn))
#define check_init() if(!get().m_IsInitialized) { printf("[randomize_video_mem] unitialized api\n"); return s7_nil(sc); }

s7_pointer lispc_s7_api::randomize_video_mem(s7_scheme *sc, s7_pointer args){
    check_init();

    lispc_api::randomize_video_mem(*lispc_s7_api::get().m_mem, *lispc_s7_api::get().m_screen);
    return s7_nil(sc);
}

s7_pointer lispc_s7_api::rect(s7_scheme *sc, s7_pointer args){
    check_init();

    uint16_t x1 = s7_integer(s7_car(args));
    uint16_t y1 = s7_integer(s7_cadr(args));
    uint16_t x2 = s7_integer(s7_caddr(args));
    uint16_t y2 = s7_integer(s7_cadddr(args));
    uint16_t c = s7_integer(s7_list_ref(sc, args, 5));
    lispc_api::rect(*lispc_s7_api::get().m_screen, x1, y1, x2, y2, c);
    return s7_nil(sc);
}

s7_pointer lispc_s7_api::cls(s7_scheme *sc, s7_pointer args){
    check_init();

    uint16_t color = s7_integer(s7_car(args));
    lispc_api::cls(*lispc_s7_api::get().m_mem, color);
    return s7_nil(sc);
}

void lispc_s7_api::register_functions(s7_scheme* sc, Memory& mem, Screen& screen){
    m_IsInitialized = true;
    m_MemoryType = s7_gensym(sc, "Memory");
    m_ScreenType = s7_gensym(sc, "Screen");

    s7_define_constant(sc, "lispc::Memory", s7_make_c_pointer_with_type(sc, &mem, m_MemoryType, s7_nil(sc)));
    s7_define_constant(sc, "lispc::Screen", s7_make_c_pointer_with_type(sc, &screen, m_ScreenType, s7_nil(sc)));
    s7_define_constant(sc, "color::white", s7_make_integer(sc, color_white));
    s7_define_constant(sc, "color::black", s7_make_integer(sc, color_black));
    s7_define_constant(sc, "color::red", s7_make_integer(sc, color_red));
    s7_define_constant(sc, "color::green", s7_make_integer(sc, color_green));
    s7_define_constant(sc, "color::blue", s7_make_integer(sc, color_blue));
    s7_define_constant(sc, "color::cyan", s7_make_integer(sc, color_cyan));
    s7_define_constant(sc, "color::yellow", s7_make_integer(sc, color_yellow));
    s7_define_constant(sc, "color::purple", s7_make_integer(sc, color_purple));
    
    s7_define_function(sc, "randomize_video_mem", randomize_video_mem, 0, 0, false,
                       "(randomize_video_mem) randomizes all pixels on the screen");

    s7_define_function(sc, "rect", rect, 5, 0, false,
                       "(rect x1 y1 x2 y2 color) draw a rectangle from screen relative coord (x1,y1) to (x2,y2) of given color");

    s7_define_function(sc, "cls", cls, 1, 0, false,
                       "(cls color) clears screen with color");
}

void lispc_s7_api::init(Memory& mem, Screen& screen, Inputs& inputs) {
    m_sc = s7_init();
    m_mem = &mem;
    m_screen = &screen;
    m_inputs = &inputs;

    register_functions(m_sc, mem, screen);
}

bool lispc_s7_api::load(const char* filename) {
    if (!m_IsInitialized)
        return false;
    
    if (!s7_load(m_sc, filename)) {
        fprintf(stderr, "%s: %s\n", strerror(errno), filename);
        return false;
    }
    return true;
}

void lispc_s7_api::update(float dt) {
    if (!m_IsInitialized)
        return;
    
    s7_call(m_sc, s7_name_to_value(m_sc, "update"), s7_cons(m_sc,
                                                          s7_make_real(m_sc, dt),
                                                          s7_nil(m_sc)));
    s7_flush_output_port(m_sc, s7_current_output_port(m_sc));
}

void lispc_s7_api::uninit() {
    s7_free(m_sc);
    m_sc = nullptr;
    m_IsInitialized = false;
}
