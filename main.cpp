#include <cstdint>
#include <iostream>

#include "src/headers/cpu.h"
#include "src/headers/bus.h"

using namespace std;

int main (){
    cout << "gameboy emulator" << endl;

    cpu emu;
    bus b;

    b.write(0xFFFF,0x78);

    uint8_t test = b.read(0xFFFF);
    cout << "this is test 0x" << hex<< static_cast<int>(test)<< endl;

    return 0;
    
}