#pragma once

#include <cstdint>
#include "bus.h"

class cpu{
    private:
    uint8_t A; //Accumulator
    uint8_t F; // flag
    uint8_t B, C , D, E, H , L;   //GPR

    uint16_t SP; //Stack pointer
    uint16_t PC; //Program Counter

    bus mem; //RAM and bus

    uint8_t opcode;

    uint8_t fetch();
    uint16_t fetch16();

    const uint8_t z_flag = 0x80;
    const uint8_t n_flag = 0x40;
    const uint8_t h_flag = 0x20;
    const uint8_t c_flag = 0x10;
    
    void set_flags(uint8_t mask,bool set);
    bool get_flags(uint8_t mask);


    public:

    uint16_t get_AF();
    uint16_t get_BC();
    uint16_t get_DE();
    uint16_t get_HL();

    void set_AF(uint16_t value);
    void set_BC(uint16_t value);
    void set_DE(uint16_t value);
    void set_HL(uint16_t value);

    void reset();

    void Register_status();

    cpu(){
        reset();


    }

    friend class Instruction;
    //TO_DO instructions and interuppt1

};