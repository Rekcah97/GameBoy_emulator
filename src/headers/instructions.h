
#include <cstdint>
class cpu;

class Instruction{
    public:

    void NOP(){};

    void loadRegisterPair(cpu& cpu,int dst, uint16_t value);
    void LD_r16_i16(cpu& cpu);

    void LD_r16m_a(cpu& cpu);

    void loadRegister(cpu& cpu,int dst, uint8_t value);
    void LD_r8_i8(cpu& cpu);
    void LD_r8_r8(cpu& cpu);
};