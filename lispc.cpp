#include <types.h>
#include <inputs.h>
#include <memory.h>
#include <screen.h>

#include <cstdio>
#include <thread>
#include <random>
#include <external/s7.h>

using timept = std::chrono::time_point<std::chrono::high_resolution_clock>;

void randomize_video_mem(Memory& mem, const Screen& screen) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 15);

    for (uint16_t i=0; i<PIXEL_COUNT; ++i) {
        mem[i] = defcolor(distrib(gen), distrib(gen), distrib(gen), 0xF);
    }
}

int main(int argn, const char** argv) {
    s7_scheme* sc = s7_init();

    if (argn > 1) {
        if (!s7_load(sc, argv[1])) {
            fprintf(stderr, "%s: %s\n", strerror(errno), argv[1]);
            return(2);
        }
	}
    
    Memory mem;
    Inputs inputs;
    Screen screen;
    screen.initialize();

    const timept start = std::chrono::high_resolution_clock::now();
    timept last = std::chrono::high_resolution_clock::now();
    while (true) {
        inputs.update();
        if (inputs.m_quit)
            break;

        const timept now = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<float, std::milli> elapsed = now-last;
        const float dt = elapsed.count() * 0.001f;
        s7_call(sc, s7_name_to_value(sc, "update"), s7_cons(sc, s7_make_real(sc, dt), s7_nil(sc)));
        s7_flush_output_port(sc, s7_current_output_port(sc));
        last = now;
        //randomize_video_mem(mem, screen);
        screen.render(mem);

        using namespace std::chrono_literals;
        const timept frameend = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<float, std::milli> this_fame_elapsed = frameend - last;
        const std::chrono::duration<float, std::milli> sleep_duration = 30ms - this_fame_elapsed;
        //printf("sleep for: %.2f\n", sleep_duration.count());
        std::this_thread::sleep_for(sleep_duration);

        // timept now = std::chrono::high_resolution_clock::now();
        // std::chrono::duration<float, std::milli> elapsed = now-start;
        // if (elapsed.count() > 10000.0f)
        //     break;
    }
    
    screen.uninitialize();
    s7_free(sc);
    return 0;
}
