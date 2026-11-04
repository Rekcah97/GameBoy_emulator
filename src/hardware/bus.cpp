#include "../headers/bus.h"

uint8_t bus::read(uint16_t addr){
    return RAM[addr];
}

void bus::write( uint16_t addr, uint8_t value){
    RAM[addr] = value;
}