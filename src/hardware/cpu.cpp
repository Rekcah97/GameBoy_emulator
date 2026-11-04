#include "../headers/cpu.h"
#include <cstdint>

uint16_t cpu::get_AF(){
    return (A << 8) | (F & 0xF0);
}

uint16_t cpu::get_BC(){
    return (B << 8) | C;
}

uint16_t cpu::get_DE(){
    return (D <<8 ) | E;
}

uint16_t cpu::get_HL(){
    return (H << 8) | L;
}

void cpu::set_AF(uint16_t value){
    A = (value & 0xFF00) >> 8;
    F = (value & 0x00F0);
}

void cpu::set_BC(uint16_t value){
    B = (value & 0xFF00) >>8;
    C = (value & 0x00FF);
}

void cpu:: set_DE(uint16_t value){
    D = (value & 0xFF00) >> 8;
    E = (value & 0x00FF);
}

void cpu::set_HL(uint16_t value){
    H = (value & 0xFF00) >>8;
    L = (value & 0x00FF);
}

void cpu::reset(){
    set_AF(0x0180);
    set_BC(0x0013);
    set_DE(0x00D8);
    set_HL(0x014D);

    PC = 0x0100;
    SP = 0xFFFE;
}