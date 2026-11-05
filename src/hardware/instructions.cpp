#pragma once

#include "../headers/instructions.h"
#include "../headers/cpu.h"
#include <cstdint>


void Instruction::loadRegisterPair(cpu &cpu, int dst, uint16_t value){
    switch (dst) {
        case 0: cpu.set_BC(value); break;
        case 1: cpu.set_DE(value); break;
        case 2: cpu.set_HL(value); break;
        case 3: cpu.SP = value; break;
        default: break;
    }
}

void Instruction::LD_r16_i16(cpu &cpu){
    uint8_t dst = (cpu.opcode & 0x30) >> 4;
    uint8_t i_1 = cpu.fetch();
    uint8_t i_2 = cpu.fetch();

    uint16_t value = (i_2 << 8) | i_1 ;

    loadRegisterPair(cpu, dst, value);
}

void Instruction::LD_r16m_a(cpu &cpu){
    uint8_t dst = (cpu.opcode & 0x30) >> 4;

    switch (dst) {
        case 0: cpu.mem.write(cpu.get_BC(), cpu.A); break;
        case 1: cpu.mem.write(cpu.get_DE(), cpu.A); break;
        case 2: {
            uint16_t hl = cpu.get_HL();
            cpu.mem.write(hl, cpu.A); 
            cpu.set_HL(hl + 0x0001); 
            break;
        }
        case 3: {
            uint16_t hl = cpu.get_HL();
            cpu.mem.write(hl, cpu.A); 
            cpu.set_HL(hl - 0x0001); 
            break;}
        default: break;
    }
}

void Instruction::LD_a_r16m(cpu &cpu){
    uint8_t src = (cpu.opcode & 0x30) >> 4;

        switch (src) {
        case 0: cpu.A = cpu.mem.read(cpu.get_BC()) ; break;
        case 1: cpu.A = cpu.mem.read(cpu.get_DE()); break;
        case 2: {
            uint16_t hl = cpu.get_HL();
            cpu.A = cpu.mem.read(hl);
            cpu.set_HL(hl + 0x0001); 
            break;
        }
        case 3: {
            uint16_t hl = cpu.get_HL();
            cpu.A = cpu.mem.read(hl);
            cpu.set_HL(hl - 0x0001); 
            break;}
        default: break;
    }
}

void Instruction::LD_i16_SP(cpu &cpu){
    uint16_t addr = cpu.fetch16();
    uint16_t sp = cpu.SP;

    uint8_t lo = sp & 0x00FF ;
    uint16_t hi = ((sp & 0xFF00) >> 8);

    cpu.mem.write(addr, lo);
    cpu.mem.write(addr + 0x0001, hi);
}

void Instruction::INC_r16(cpu &cpu){
    int oprnd = (cpu.opcode & 0x30) >> 4;

    switch (oprnd) {
        case 0: cpu.set_BC(cpu.get_BC() + 0x0001); break;
        case 1: cpu.set_DE(cpu.get_DE() + 0x0001); break;
        case 2: cpu.set_HL(cpu.get_HL() + 0x0001); break;
        case 3: cpu.SP++; break;
        default: break;
    }
}

void Instruction::DRC_r16(cpu &cpu){
    int oprnd = (cpu.opcode & 0x30) >> 4;
        switch (oprnd) {
        case 0: cpu.set_BC(cpu.get_BC() - 0x0001); break;
        case 1: cpu.set_DE(cpu.get_DE() - 0x0001); break;
        case 2: cpu.set_HL(cpu.get_HL() - 0x0001); break;
        case 3: cpu.SP--; break;
        default: break;
    }
}

void Instruction::ADD_hl_r16(cpu &cpu){
    int oprnd = (cpu.opcode & 0x30) >> 4;

    uint16_t hl = cpu.get_HL();
    uint16_t operand;
    uint32_t sum;

    switch (oprnd) {
        case 0: operand = cpu.get_BC(); break;
        case 1: operand = cpu.get_DE(); break;
        case 2: operand = hl; break;
        case 3: operand = cpu.SP; break;
        default: break;
    }

    cpu.set_HL(hl + operand);




    cpu.set_flags(cpu.n_flag, false);

    sum = hl + operand;
    if(sum > 0xFFFF){
        cpu.set_flags(cpu.c_flag, true);
    } else {
        cpu.set_flags(cpu.c_flag, false);
    }

    bool half_carry = (((hl & 0x0F00) >> 8) + ((operand & 0x0F00) >> 8)) > 0x0F;
    if(half_carry){
        cpu.set_flags(cpu.h_flag, true);
    }else{
        cpu.set_flags(cpu.h_flag, false);
    }



}

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