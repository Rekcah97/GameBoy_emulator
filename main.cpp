
#include <iostream>

#include "src/headers/cartridge.h"
#include "src/headers/cpu.h"

using namespace std;

int main(int argc, char **argv) {
    cout << "***Gameboy emulator***" << endl;

    if (argc < 2) {
        cerr << "gameboy rom not found " << endl;
        return 1;
    }
    cpu emu;

    cartridge file;
    if (!file.loadRom(emu, argv[1])) {
        cerr << "failed to load gameboy rom" << endl;
        return 1;
    }

    return 0;
}