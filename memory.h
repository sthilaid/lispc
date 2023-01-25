#pragma once
#include <types.h>
#include <cstdint>

class Memory {
public:
    Memory();
    
    uint16_t* operator+(uint16_t addr) { return m_buffer+addr; }
    uint16_t operator[](uint16_t addr) const { return m_buffer[addr]; }
    uint16_t& operator[](uint16_t addr) { return m_buffer[addr]; }
    
private:
    void clear();
    uint16_t m_buffer[MEM_SIZE];
};
