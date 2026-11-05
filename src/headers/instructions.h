
#include <cstdint>
class cpu;

class Instruction{
    private:
        uint8_t opcode;
    public:
    void LD_nn_n(cpu& cpu);
};