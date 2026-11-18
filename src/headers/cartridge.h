#pragma once

#include "../headers/cpu.h"
#include <cstdint>

class cpu;

class cartridge {

  public:
    bool loadRom(cpu &cpu, const char *romfile);

    void print_info(cpu &cpu);

    const char *cartridge_type(uint8_t code);
    const char *new_lic(uint16_t code);
};