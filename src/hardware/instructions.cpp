#pragma once

#include "../headers/instructions.h"
#include "../headers/cpu.h"


void Instruction::LD_nn_n(cpu& cpu){
    uint8_t op = cpu.opcode;
    uint8_t n = cpu.fetch();

    switch (op) {
        case 0x06: cpu.B = n; break;
        case 0x0E: cpu.C = n; break;
        case 0x16: cpu.D = n; break;
        case 0x1E: cpu.E = n; break;
        case 0x26: cpu.H = n; break;
        case 0x2E: cpu.L = n; break;
        default: break;
    
    }
}