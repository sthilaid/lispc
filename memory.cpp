#include <memory.h>
#include <cstring>

Memory::Memory() {
    clear();
}

void Memory::clear() {
    memset(&m_buffer, 0, MEM_SIZE);
}
