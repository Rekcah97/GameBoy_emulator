
#include <cstdint>
class cpu;

class Instruction{
    public:
    void loadRegister(cpu& cpu,int dst, uint8_t value);
    void LD_r8_i8(cpu& cpu);
    void LD_r8_r8(cpu& cpu);
};