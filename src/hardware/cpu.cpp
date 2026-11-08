#include "../headers/cpu.h"
#include <cstdint>
#include <iostream>

using namespace std;

uint16_t cpu::get_AF(){
    return (A << 8) | (F & 0xF0);
}

uint16_t cpu::get_BC(){
    return (B << 8) | C;
}

uint16_t cpu::get_DE(){
    return (D << 8) | E;
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
    set_AF(0x01B0);
    set_BC(0x0013);
    set_DE(0x00D8);
    set_HL(0x014D);

    PC = 0x0100;
    SP = 0xFFFE;
    IME = 0;
    set_IF(0xE1);
    set_IE(0x00);
}

void cpu::Register_status(){
    cout << "AF : 0x" << hex << get_AF() << endl;
    cout << "BC : 0x" << hex << get_BC() << endl; 
    cout << "DE : 0x" << hex << get_DE() << endl;
    cout << "HL : 0x" << hex << get_HL() << endl;
    cout << "SP : 0x" << hex << SP << endl;
    cout << "PC : 0x" << hex << PC << endl;

    cout << "Zero flag (z) : " << ((F & 0x80) >> 7) << endl;
    cout << "Subtraction Flag (n) : " << ((F & 0x40) >> 6) << endl;
    cout << "Half carry Flag (h) : " << ((F & 0x20) >> 5) << endl;
    cout << "Carry Flag (c) : " << ((F & 0x10) >> 4) << endl;
}

uint8_t cpu::fetch(){
    uint8_t data = mem.read(PC);
    PC++;
    return data;
}

uint16_t cpu::fetch16(){
    uint8_t lo = fetch();
    uint8_t hi = fetch();
    uint16_t data = (hi << 8) | lo;
    return data;
}

void cpu::set_flags(uint8_t mask, bool set){
    if(set){
        F = F | mask;
    }else{
        F = F & ~mask;
    }
}

bool cpu::get_flags(uint8_t mask){
    return (F & mask) != 0;
}

uint8_t cpu::get_IE(){
   return mem.read(0xFFFF);
}

uint8_t cpu::get_IF(){
    return mem.read(0xFF0F);
}

void cpu::set_IE(uint8_t value){
    mem.write(0xFFFF, value);
}

void cpu::set_IF(uint8_t value){
    mem.write(0xFF0F, value);  
}