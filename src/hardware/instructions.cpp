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

void Instruction::LD_nn_n(cpu& cpu){
    int dest = (cpu.opcode & 0x38) >> 3;
    uint8_t n = cpu.fetch();

    loadRegister(cpu,dest,n);
}

void Instruction::LD_r1_r2(cpu &cpu){
    uint8_t op = cpu.opcode;
    uint8_t* r1;


    switch (op & 0xF0) {
        case 0x70 :
            uint16_t hl;
            if(op >= 0x70 && op <= 0x75){
                hl = cpu.get_HL();
            }else if(op >= 0x78 && op<= 0x7F){
                r1 = &cpu.A;
            }else{
                break;
            }
            
            switch (op & 0x0F) {
                case 0x0: cpu.mem.write(hl, cpu.B); break;
                case 0x1: cpu.mem.write(hl, cpu.C); break;
                case 0x2: cpu.mem.write(hl, cpu.D); break;
                case 0x3: cpu.mem.write(hl, cpu.E); break;
                case 0x4: cpu.mem.write(hl, cpu.H); break;
                case 0x5: cpu.mem.write(hl, cpu.L); break;
                case 0xF: *r1 = cpu.A; break;
                case 0x8: *r1 = cpu.B; break;
                case 0x9: *r1 = cpu.C; break;
                case 0xA: *r1 = cpu.D; break;
                case 0xB: *r1 = cpu.E; break;
                case 0xC: *r1 = cpu.H; break;
                case 0xD: *r1 = cpu.L; break;
                case 0xE: {
                    uint16_t hl = cpu.get_HL();
                    uint8_t data = cpu.mem.read(hl);
                    *r1 = data;
                    break;
                }
                default:break;   
            };
            break;

        case 0x30:
            switch (op & 0x0F) {
                case 0x6: {
                    uint8_t n = cpu.fetch();
                    uint16_t hl = cpu.get_HL();
                    cpu.mem.write(hl, n);
                }
                default: break;
            }
            break;

        default:
            if(op >= 0x40 && op <= 0x46 ){
                r1 = &cpu.B;
            } else if(op >= 0x48 && op <= 0x4E){
                r1 = &cpu.C;
            } else if(op >= 0x50 && op <= 0x56){
                r1 = &cpu.D;
            }
            else if(op >= 0x58 && op <= 0x5E){
                r1 = &cpu.E;
            }
            else if(op >= 0x60 && op <= 0x66){
                r1 = &cpu.H;
            }
            else if(op >= 0x58 && op <= 0x6E){
                r1 = &cpu.L;
            }else{
                break;
            }
            switch (op & 0x0F) {
                case 0x0: *r1 = cpu.B; break;
                case 0x1: *r1 = cpu.C; break;
                case 0x2: *r1 = cpu.D; break;
                case 0x3: *r1 = cpu.E; break;
                case 0x4: *r1 = cpu.H; break;
                case 0x5: *r1 = cpu.L; break;
                case 0x6:
                { uint16_t hl = cpu.get_HL();
                    uint8_t data = cpu.mem.read(hl);
                    *r1 = data;
                    break;} 
                case 0x8: *r1 = cpu.B; break;
                case 0x9: *r1 = cpu.C; break;
                case 0xA: *r1 = cpu.D; break;
                case 0xB: *r1 = cpu.E; break;
                case 0xC: *r1 = cpu.H; break;
                case 0xD: *r1 = cpu.L; break;
                case 0xE:{
                    uint16_t hl = cpu.get_HL();
                    uint8_t data = cpu.mem.read(hl);
                    *r1 = data;
                    break;
                }
                default: break;
            }; break;
    }
}