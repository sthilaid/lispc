#include <memory.h>
#include <cstring>

Memory::Memory() {
    clear();
}

void Memory::clearVideoMemory(uint16_t val){
    // for (uint16_t i=0; i<VIDEO_MEM_SIZE; ++i) {
    //     m_buffer[MemMap_Video+i] = val;
    // }
    std::fill(&m_buffer[MemMap_Video], &m_buffer[MemMap_Video+VIDEO_MEM_SIZE], val);
}

void Memory::clear() {
    memset(&m_buffer, 0, MEM_SIZE);
}
