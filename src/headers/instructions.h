
#include <cstdint>
class cpu;

class Instruction{
    public:
    void loadRegister(cpu& cpu,int dst, uint8_t value);
    void LD_nn_n(cpu& cpu);
    void LD_r1_r2(cpu& cpu);
};