#pragma once
#include <cstdint>
#include <cstring>
#define RAM_SIZE 65536 //64 kb

class bus{
    private:
    uint8_t RAM[RAM_SIZE];

    public:
    bus(){
        memset(RAM, 0, RAM_SIZE);
    }

    uint8_t read(uint16_t addr);
    void write( uint16_t addr, uint8_t value);
};