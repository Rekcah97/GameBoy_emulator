#include "../headers/bus.h"

#define rom_starting 0x0000

uint8_t bus::read(uint16_t addr) { return RAM[addr]; }

void bus::write(uint16_t addr, uint8_t value) { RAM[addr] = value; }

void bus::install_rom(char *buffer, int size) {
    for (int i = 0; i < size; i++) {
        RAM[rom_starting + i] = buffer[i];
    }
}