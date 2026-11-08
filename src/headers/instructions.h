
#include <cstdint>
class cpu;

class Instruction{
    public:



    //helper
    void loadRegisterPair(cpu& cpu,int dst, uint16_t value);
    void loadRegister(cpu& cpu,int dst, uint8_t value);
    bool checkCond(cpu& cpu, int cond);
    uint8_t get_r8(cpu& cpu, int dst);
    uint16_t pop16(cpu& cpu);
    void push16(cpu& cpu, uint16_t value);

    void NOP(){};
    void LD_r16_i16(cpu& cpu);

    void LD_r16m_a(cpu& cpu);
    void LD_a_r16m(cpu& cpu);

    void LD_i16_SP(cpu& cpu);

    void INC_r16(cpu& cpu);
    void DEC_r16(cpu& cpu);

    void ADD_hl_r16(cpu& cpu);

    void INC_r8(cpu& cpu);
    void DEC_r8(cpu& cpu);


    void LD_r8_i8(cpu& cpu);

    void RLCA(cpu& cpu);
    void RRCA(cpu& cpu);
    void RLA(cpu& cpu);
    void RRA(cpu& cpu);
    void DAA(cpu& cpu);
    void CPL(cpu& cpu);
    void SCF(cpu& cpu);
    void CCF(cpu& cpu);

    void JR_i8(cpu& cpu);
    void JR_cond_i8(cpu& cpu);

    void STOP(cpu& cpu);

    void LD_r8_r8(cpu& cpu);
    // TO DO HLT

    void ADD_A_r8(cpu& cpu);
    void ADC_A_r8(cpu& cpu);
    void SUB_A_r8(cpu& cpu);
    void SBC_A_r8(cpu& cpu);
    void AND_A_r8(cpu& cpu);
    void XOR_A_r8(cpu& cpu);
    void OR_A_r8(cpu& cpu);
    void CP_A_r8(cpu& cpu);

    void ADD_A_i8(cpu& cpu);
    void ADC_A_i8(cpu& cpu);
    void SUB_A_i8(cpu& cpu);
    void SBC_A_i8(cpu& cpu);
    void AND_A_i8(cpu& cpu);
    void XOR_A_i8(cpu& cpu);
    void OR_A_i8(cpu& cpu);
    void CP_A_i8(cpu& cpu);

    void RET_COND(cpu& cpu);
    void RET(cpu& cpu);
    // TO-DO RETI

    void JP_COND_i16(cpu& cpu);
    void JP_i16(cpu& cpu);
    void JP_hl(cpu& cpu);

    void CALL_COND_i16(cpu& cpu);


};