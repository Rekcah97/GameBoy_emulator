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

void Instruction::DEC_r16(cpu &cpu){
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
    uint16_t operand = 0;
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
    cpu.set_flags(cpu.c_flag, sum > 0xFFFF);

    bool half_carry = (((hl & 0x0FFF) + (operand & 0x0FFF))) > 0x0FFF;
    cpu.set_flags(cpu.h_flag, half_carry);
}

void Instruction::INC_r8(cpu &cpu){
    int oprnd = (cpu.opcode & 0x38) >> 3;
    uint8_t operand = 0;
    uint8_t result;



    switch (oprnd) {
        case 0: operand = cpu.B; break;
        case 1: operand = cpu.C; break;
        case 2: operand = cpu.D; break;
        case 3: operand = cpu.E; break;
        case 4: operand = cpu.H; break;
        case 5: operand = cpu.L; break;
        case 6: operand = cpu.mem.read(cpu.get_HL()); break;
        case 7: operand = cpu.A; break;
        default: break;
    }

    result = operand + 1;
    
    loadRegister(cpu, oprnd, result);
    
    cpu.set_flags(cpu.n_flag, false);
    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.h_flag, ((operand & 0x0F) + 0x01) > 0x0F);
}

void Instruction::DEC_r8(cpu &cpu){
    int oprnd = (cpu.opcode & 0x38) >> 3;
    uint8_t operand = 0;
    uint8_t result;



    switch (oprnd) {
        case 0: operand = cpu.B; break;
        case 1: operand = cpu.C; break;
        case 2: operand = cpu.D; break;
        case 3: operand = cpu.E; break;
        case 4: operand = cpu.H; break;
        case 5: operand = cpu.L; break;
        case 6: operand = cpu.mem.read(cpu.get_HL());break;
        case 7: operand = cpu.A; break;
        default: break;
    }

    result = operand - 1;

    loadRegisterPair(cpu, oprnd, result);

    cpu.set_flags(cpu.n_flag, true);
    cpu.set_flags(cpu.z_flag, result == 0x00);
    cpu.set_flags(cpu.h_flag, (operand & 0x0F) == 0);

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

void Instruction::RLCA(cpu &cpu){
    uint8_t shift = cpu.A << 1;
    bool needed =  (cpu.A << 1) & 0x100;

    cpu.A = shift | needed;

    cpu.set_flags(cpu.z_flag, false);
    cpu.set_flags(cpu.n_flag, false);
    cpu.set_flags(cpu.h_flag,false);
    cpu.set_flags(cpu.c_flag, needed);

}

void Instruction::RRCA(cpu &cpu){
    uint8_t shift = cpu.A >> 1;
    bool needed = cpu.A & 0x01;

    cpu.A = shift | (needed << 7);

    cpu.set_flags(cpu.z_flag, false);
    cpu.set_flags(cpu.n_flag, false);
    cpu.set_flags(cpu.h_flag,false);
    cpu.set_flags(cpu.c_flag, needed);
}

void Instruction::RLA(cpu &cpu){
    uint8_t shift = cpu.A << 1;
    bool oldCarry = cpu.get_flags(cpu.c_flag);
    bool oldMSB = (cpu.A & 0x80) != 0;


    cpu.A = shift | (oldCarry);

    cpu.set_flags(cpu.z_flag, 0);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, 0);
    cpu.set_flags(cpu.c_flag, oldMSB);

}

void Instruction::RRA(cpu &cpu){
    uint8_t shift = cpu.A >> 1;
    bool oldCarry = cpu.get_flags(cpu.c_flag);
    bool oldLSB = (cpu.A & 0x01);

    cpu.A = shift | (oldCarry << 7);

    cpu.set_flags(cpu.z_flag, 0);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, 0);
    cpu.set_flags(cpu.c_flag, oldLSB);
}

void Instruction::DAA(cpu &cpu){
    uint8_t adjustment = 0x00;
    uint8_t result = cpu.A;

    bool half_flag = cpu.get_flags(cpu.h_flag);
    bool carry_flag = cpu.get_flags(cpu.c_flag);

    if(cpu.get_flags(cpu.n_flag)){
        if(half_flag){
            adjustment += 0x06;
        }
        if(carry_flag){
            adjustment += 0x60;
        }
        result -= adjustment;
    }else{
        if(half_flag || ((cpu.A & 0x0F) > 0x09)){
            adjustment += 0x06;
        }
        if(carry_flag || (cpu.A > 0x99)){
            adjustment += 0x60;
            cpu.set_flags(cpu.c_flag, 1);
        }
        result += adjustment;
    }

    cpu.A = result;

    cpu.set_flags(cpu.z_flag, (result == 0));
    cpu.set_flags(cpu.h_flag, 0);
}

void Instruction::CPL(cpu &cpu){
    cpu.A = ~cpu.A;

    cpu.set_flags( cpu.n_flag, 1);
    cpu.set_flags(cpu.h_flag, 1);
}

void Instruction::SCF(cpu &cpu){

    cpu.set_flags(cpu.c_flag, 1);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, 0);
}

void Instruction::CCF(cpu &cpu){
    bool oldCarry = cpu.get_flags(cpu.c_flag);

    cpu.set_flags(cpu.c_flag, !oldCarry);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, 0);
}

void Instruction::JR_i8(cpu &cpu){
    int8_t offset = cpu.fetch();

    cpu.PC += offset;

}

bool Instruction::checkCond(cpu &cpu, int cond){

    bool result = 0; 
        switch (cond) {
        case 0:  if(!cpu.get_flags(cpu.z_flag)) result = 1 ; break;
        case 1:  if(cpu.get_flags(cpu.z_flag)) result = 1; break;
        case 2: if(!cpu.get_flags(cpu.c_flag))  result = 1; break;
        case 3: if(cpu.get_flags(cpu.c_flag)) result = 1; break;
        default: break;
    }

    return result;
}

void Instruction::JR_cond_i8(cpu &cpu){
    uint8_t cond = (cpu.opcode & 0x18) >> 3;
    int8_t offset = cpu.fetch();

    if(checkCond(cpu, cond)){
        cpu.PC += offset;
    }

}

void Instruction::STOP(cpu &cpu){
    cpu.fetch();
    NOP();
}

//for this HALT must be CAlled before this instruction
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

uint8_t Instruction::get_r8(cpu &cpu, int dst){
    uint8_t result = 0;
    switch(dst){
        case 0: result = cpu.B; break;
        case 1: result = cpu.C; break;
        case 2: result = cpu.D; break;
        case 3: result = cpu.E; break;
        case 4: result = cpu.H; break;
        case 5: result = cpu.L; break;
        case 6: result = cpu.mem.read(cpu.get_HL()); break;
        case 7: result = cpu.A ; break;
        default: break;
    }

    return result;
}

void Instruction::ADD_A_r8(cpu &cpu){
    int oprnd = (cpu.opcode & 0x07) ;
    uint8_t r8 = get_r8(cpu, oprnd);
    uint8_t oldA = cpu.A;
    uint8_t result ;

    result = r8 + oldA;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, ((oldA & 0x0F) + (r8 & 0x0F)) > 0x0F);
    cpu.set_flags(cpu.c_flag, ((oldA + r8)) > 0xFF);
}

void Instruction::ADC_A_r8(cpu &cpu){
    int oprnd = (cpu.opcode & 0x07) ;
    uint8_t r8 = get_r8(cpu, oprnd);
    uint8_t oldA = cpu.A;
    uint8_t carry = cpu.get_flags(cpu.c_flag);
    uint8_t result;

    result = r8 + oldA + carry;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, ((oldA & 0x0F) + (r8 & 0x0F) + carry) > 0x0F);
    cpu.set_flags(cpu.c_flag, ((oldA + r8 + carry)) > 0xFF);
}

void Instruction::SUB_A_r8(cpu &cpu){
    int oprnd = (cpu.opcode & 0x07) ;
    uint8_t r8 = get_r8(cpu, oprnd);
    uint8_t oldA = cpu.A;
    uint8_t result ;

    result = oldA - r8;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 1);
    cpu.set_flags(cpu.h_flag, ((r8 & 0x0F) > (oldA & 0x0F) ));
    cpu.set_flags(cpu.c_flag, (r8 > oldA));
}

void Instruction::SBC_A_r8(cpu &cpu){
    int oprnd = (cpu.opcode & 0x07) ;
    uint8_t r8 = get_r8(cpu, oprnd);
    uint8_t oldA = cpu.A;
    uint8_t carry = cpu.get_flags(cpu.c_flag);
    uint8_t result ;

    result = oldA - r8 - carry;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 1);
    cpu.set_flags(cpu.h_flag, (((r8 & 0x0F) + carry) > (oldA & 0x0F) ));
    cpu.set_flags(cpu.c_flag, ((r8 + carry) > oldA));
}

void Instruction::AND_A_r8(cpu &cpu){
    int oprnd = (cpu.opcode & 0x07) ;
    uint8_t r8 = get_r8(cpu, oprnd);
    uint8_t oldA = cpu.A;
    uint8_t result;

    result = r8 & oldA;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, 1);
    cpu.set_flags(cpu.c_flag, 0);
}

void Instruction::XOR_A_r8(cpu &cpu){
    int oprnd = (cpu.opcode & 0x07) ;
    uint8_t r8 = get_r8(cpu, oprnd);
    uint8_t oldA = cpu.A;
    uint8_t result;

    result = r8 ^ oldA;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, 0);
    cpu.set_flags(cpu.c_flag, 0);
}

void Instruction::OR_A_r8(cpu &cpu){
    int oprnd = (cpu.opcode & 0x07) ;
    uint8_t r8 = get_r8(cpu, oprnd);
    uint8_t oldA = cpu.A;
    uint8_t result;

    result = r8 | oldA;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, 0);
    cpu.set_flags(cpu.c_flag, 0);
}

void Instruction::CP_A_r8(cpu &cpu){
    int oprnd = (cpu.opcode & 0x07) ;
    uint8_t r8 = get_r8(cpu, oprnd);
    uint8_t oldA = cpu.A;
    uint8_t result ;

    result = oldA - r8;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 1);
    cpu.set_flags(cpu.h_flag, ((r8 & 0x0F) > (oldA & 0x0F) ));
    cpu.set_flags(cpu.c_flag, (r8 > oldA));
}

void Instruction::ADD_A_i8(cpu &cpu){
    uint8_t i8 = cpu.fetch();
    uint8_t oldA = cpu.A;
    uint8_t result ;

    result = i8 + oldA;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, ((oldA & 0x0F) + (i8 & 0x0F)) > 0x0F);
    cpu.set_flags(cpu.c_flag, ((oldA + i8)) > 0xFF);
}

void Instruction::ADC_A_i8(cpu &cpu){
    uint8_t i8 = cpu.fetch();   
    uint8_t oldA = cpu.A;
    uint8_t carry = cpu.get_flags(cpu.c_flag);
    uint8_t result;

    result = i8 + oldA + carry;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, ((oldA & 0x0F) + (i8 & 0x0F) + carry) > 0x0F);
    cpu.set_flags(cpu.c_flag, ((oldA + i8 + carry)) > 0xFF);
}

void Instruction::SUB_A_i8(cpu &cpu){
    uint8_t i8 = cpu.fetch();
    uint8_t oldA = cpu.A;
    uint8_t result ;

    result = oldA - i8;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 1);
    cpu.set_flags(cpu.h_flag, ((i8 & 0x0F) > (oldA & 0x0F) ));
    cpu.set_flags(cpu.c_flag, (i8 > oldA));   
}

void Instruction::SBC_A_i8(cpu &cpu){
    uint8_t i8 = cpu.fetch();
    uint8_t oldA = cpu.A;
    uint8_t carry = cpu.get_flags(cpu.c_flag);
    uint8_t result ;

    result = oldA - i8 - carry;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 1);
    cpu.set_flags(cpu.h_flag, (((i8 & 0x0F) + carry) > (oldA & 0x0F) ));
    cpu.set_flags(cpu.c_flag, ((i8 + carry) > oldA));   
}

void Instruction::AND_A_i8(cpu &cpu){
    uint8_t i8= cpu.fetch();
    uint8_t oldA = cpu.A;
    uint8_t result;

    result = i8 & oldA;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, 1);
    cpu.set_flags(cpu.c_flag, 0);
}

void Instruction::XOR_A_i8(cpu &cpu){
    uint8_t i8 = cpu.fetch();
    uint8_t oldA = cpu.A;
    uint8_t result;

    result = i8 ^ oldA;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, 0);
    cpu.set_flags(cpu.c_flag, 0);
}

void Instruction::OR_A_i8(cpu &cpu){
    uint8_t i8 = cpu.fetch();
    uint8_t oldA = cpu.A;
    uint8_t result;

    result = i8 | oldA;
    cpu.A = result;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 0);
    cpu.set_flags(cpu.h_flag, 0);
    cpu.set_flags(cpu.c_flag, 0);   
}

void Instruction::CP_A_i8(cpu &cpu){
    uint8_t i8 = cpu.fetch();
    uint8_t oldA = cpu.A;
    uint8_t result ;

    result = oldA - i8;

    cpu.set_flags(cpu.z_flag, result == 0);
    cpu.set_flags(cpu.n_flag, 1);
    cpu.set_flags(cpu.h_flag, ((i8 & 0x0F) > (oldA & 0x0F) ));
    cpu.set_flags(cpu.c_flag, (i8 > oldA));       
}

uint16_t Instruction::pop16(cpu &cpu){
    uint16_t location = 0;

    location = cpu.mem.read(cpu.SP);
    cpu.SP++;
    location = location | (cpu.mem.read(cpu.SP) << 8 );
    cpu.SP++;

    return location;
    
}

void Instruction::RET_COND(cpu &cpu){
    int cond = (cpu.opcode & 0x18) >> 3;

    if(checkCond(cpu, cond)){
        cpu.PC = pop16(cpu);
    }
}

void Instruction::RET(cpu &cpu){
    cpu.PC = pop16(cpu);
}

void Instruction::JP_COND_i16(cpu &cpu){
    int cond = (cpu.opcode & 0x18) >> 3;
    uint16_t i16 = cpu.fetch16();

    if(checkCond(cpu,cond)){
        cpu.PC = i16;
    }
}

void Instruction::JP_i16(cpu &cpu){
    cpu.PC =cpu.fetch16();
}

void Instruction::JP_hl(cpu &cpu){
    cpu.PC = cpu.get_HL();
}

void Instruction::push16(cpu &cpu, uint16_t value){
    uint8_t lo = value & 0x00FF;
    uint8_t hi = (value & 0xFF00) >> 8;
    cpu.SP--;
    cpu.mem.write(cpu.SP, hi);
    cpu.SP--;
    cpu.mem.write(cpu.SP, lo);    

}

void Instruction::CALL_COND_i16(cpu &cpu){
    int cond = (cpu.opcode & 0x18) >> 3;
    uint16_t i16 = cpu.fetch16();
    if(checkCond(cpu, cond)){
        push16(cpu, cpu.PC);
        cpu.PC = i16;
    }
}

void Instruction::CALL_i16(cpu &cpu){
    uint16_t i16 = cpu.fetch16();   
    push16(cpu, cpu.PC);
    cpu.PC = i16;
}

void Instruction::RST_TGT3(cpu &cpu){
    uint8_t target = (cpu.opcode & 0x38) >> 3;
    uint8_t location = 0;
    switch (target) {
        case 0: location = 0x00; break;
        case 1: location = 0x08; break;
        case 2: location = 0x10; break;
        case 3: location = 0x18; break;
        case 4: location = 0x20; break;
        case 5: location = 0x28; break;
        case 6: location = 0x30; break;
        case 7: location = 0x38; break;
        default: break;
    
    }
    push16(cpu, cpu.PC);
    cpu.PC = 0x000 + location;
}

void Instruction::POP_r16stk(cpu &cpu){
    int r16 = (cpu.opcode & 0x30) >> 4;
    uint16_t value = pop16(cpu);

    switch (r16) {
        case 0: cpu.set_BC(value); break;
        case 1: cpu.set_DE(value); break;
        case 2: cpu.set_HL(value); break;
        case 3: cpu.set_AF(value); break;
        default: break;
    }
}

void Instruction::PUSH_r16stk(cpu &cpu){
    int r16 = (cpu.opcode & 0x30) >> 4;
    uint16_t value = 0;

    switch (r16) {
        case 0: value = cpu.get_BC(); break;
        case 1: value = cpu.get_DE(); break;
        case 2: value = cpu.get_HL(); break;
        case 3: value = cpu.get_AF(); break;
        default: break;
    }
    push16(cpu, value);
}

void Instruction::LDH_C_A(cpu &cpu){
    cpu.mem.write((0xFF00 + cpu.C), cpu.A);
}

void Instruction::LDH_i8_A(cpu &cpu){
    uint8_t i8 = cpu.fetch();
    cpu.mem.write((0xFF00 + i8), cpu.A);
}

void Instruction::LD_i16_A(cpu &cpu){
    uint16_t i16 = cpu.fetch16();
    cpu.mem.write(i16,cpu.A);
}

void Instruction::LDH_A_C(cpu &cpu){
    cpu.A = cpu.mem.read((0xFF00 + cpu.C));
}