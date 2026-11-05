#pragma once

#include "../headers/instructions.h"
#include "../headers/cpu.h"
#include <cstdint>



void Instruction::loadRegister(cpu &cpu, int dst, uint8_t value){
    switch (dst) {
        case 0: cpu.B = value; break;
        case 1: cpu.C = value; break;
        case 2: cpu.D = value; break;
        case 3: cpu.E = value; break;
        case 4: cpu.H = value; break;
        case 5: cpu.L = value; break;
        case 6: {
            cpu.mem.write(cpu.get_HL(), value);
            break;
        }
        case 7: cpu.A = value; break;
        default: break;
    }
}

void Instruction::LD_r8_i8(cpu& cpu){
    int dest = (cpu.opcode & 0x38) >> 3;
    uint8_t n = cpu.fetch();

    loadRegister(cpu,dest,n);
}


void Instruction::LD_r8_r8(cpu &cpu){
    int dest = (cpu.opcode & 0x38) >> 3;
    int src = (cpu.opcode & 0x07);
    uint8_t value = 0x00;

    switch (src) {
        case 0: value = cpu.B; break;
        case 1: value = cpu.C; break;
        case 2: value = cpu.D; break;
        case 3: value = cpu.E; break;
        case 4: value = cpu.H; break;
        case 5: value = cpu.L; break;
        case 6:{ 
            value = cpu.mem.read(cpu.get_HL());
            break;
        }
        case 7: value = cpu.A; break;
        default: break;
    }

    loadRegister(cpu,dest, value);
}