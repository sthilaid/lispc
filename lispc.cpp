#include <types.h>
#include <inputs.h>
#include <memory.h>
#include <screen.h>
#include <api.h>

#include <cstdio>
#include <thread>

using timept = std::chrono::time_point<std::chrono::high_resolution_clock>;

int main(int argn, const char** argv) {
    Memory mem;
    Inputs inputs;
    Screen screen;
    screen.initialize();

    lispc_external_api* api = new lispc_s7_api();
    api->init(mem, screen, inputs);

    if (argn > 1) {
        if (!api->load(argv[1])) {
            return(2);
        }
	}

    const timept start = std::chrono::high_resolution_clock::now();
    timept last = std::chrono::high_resolution_clock::now();
    while (true) {
        inputs.update();
        if (inputs.m_quit)
            break;

        const timept now = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<float, std::milli> elapsed = now-last;
        const float dt = elapsed.count() * 0.001f;

        api->update(dt);

        last = now;
        screen.render(mem);

        using namespace std::chrono_literals;
        const timept frameend = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<float, std::milli> this_fame_elapsed = frameend - last;
        const std::chrono::duration<float, std::milli> sleep_duration = 30ms - this_fame_elapsed;
        //printf("sleep for: %.2f\n", sleep_duration.count());
        std::this_thread::sleep_for(sleep_duration);
    }
    
    screen.uninitialize();
    api->uninit();
    delete api;
    
    return 0;
}
