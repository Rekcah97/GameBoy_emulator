#pragma once

#include "../headers/cpu.h"

class cpu;

class cartridge {

  public:
    bool loadRom(cpu &cpu, const char *romfile);
};