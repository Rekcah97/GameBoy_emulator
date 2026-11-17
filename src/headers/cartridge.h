#pragma once

#include "../headers/cpu.h"

class cpu;

class cartridge {

  public:
    bool loadRom(cpu &cpu, const char *romfile);

    void print_info(cpu &cpu);

    const char *cartridge_type(uint16_t code);
};