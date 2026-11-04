#include <cstdint>

#define RAM_SIZE 0xFFFF
#define JOYP 0xFF00

class GB{
    private:

    uint8_t RAM[RAM_SIZE];


    uint8_t A; //Accumulator
    uint8_t F; // flag
    uint8_t B, C , D, E, H , L;   //GPR

    uint16_t SP; //Stack pointer
    uint16_t PC; //Program Counter

    uint8_t opcode;



    public:
    bool drawScreen;
    uint8_t screen[160 * 144];

    bool loadRom(const char* romfile);

    
    public:
};