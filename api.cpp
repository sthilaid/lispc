#include <api.h>
#include <memory.h>
#include <screen.h>

#include <random>

//-----------------------------------------------------------------------------
// lispc_api

void lispc_api::randomize_video_mem(Memory& mem, const Screen& screen) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 15);

    for (uint16_t i=0; i<PIXEL_COUNT; ++i) {
        mem[i] = defcolor(distrib(gen), distrib(gen), distrib(gen), 0xF);
    }
}

//-----------------------------------------------------------------------------
// lispc_s7_api

bool lispc_s7_api::s_IsInitialized { false };
s7_pointer lispc_s7_api::s_MemoryType { nullptr };
s7_pointer lispc_s7_api::s_ScreenType { nullptr };

#define get_ptr(sc, val, valType, ctx, argn) static_cast<valType*>(s7_c_pointer_with_type(sc, val, s_##valType##Type, ctx, argn))

s7_pointer lispc_s7_api::randomize_video_mem(s7_scheme *sc, s7_pointer args){
    if (!s_IsInitialized) {
        printf("[randomize_video_mem] unitialized api\n");
        return s7_nil(sc);
    }
    
    s7_pointer first = s7_car(args);
    s7_pointer second = s7_cadr(args);
    lispc_api::randomize_video_mem(*get_ptr(sc, first, Memory, "randomize_video_mem", 1),
                                   *get_ptr(sc, second, Screen, "randomize_video_mem", 2));
    return s7_nil(sc);
}

void lispc_s7_api::register_functions(s7_scheme* sc, Memory& mem, Screen& screen){
    s_IsInitialized = true;
    s_MemoryType = s7_gensym(sc, "Memory");
    s_ScreenType = s7_gensym(sc, "Screen");

    s7_define_constant(sc, "lispc::Memory", s7_make_c_pointer_with_type(sc, &mem, s_MemoryType, s7_nil(sc)));
    s7_define_constant(sc, "lispc::Screen", s7_make_c_pointer_with_type(sc, &screen, s_ScreenType, s7_nil(sc)));
    
    s7_define_function(sc, "randomize_video_mem", randomize_video_mem, 2, 0, false,
                       "(randomize_video_mem mem screen) randomizes all pixels on the screen");
}