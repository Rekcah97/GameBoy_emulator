#include "../headers/cartridge.h"

#define maximum_rom_size 32768

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

bool cartridge::loadRom(cpu &cpu, const char *romfile) {
    ifstream rom(romfile, ios::binary | ios::ate);
    if (!rom) {
        cerr << "Rom not found" << endl;
        exit(1);
    }

    streamsize size = rom.tellg();

    if (size > maximum_rom_size || size <= 0) {
        cerr << "Invalid Rom, Rom size : " << size << endl;
        exit(1);
    }

    char *buffer = new char[size];

    rom.seekg(0, ios::beg);
    rom.read(buffer, size);
    rom.close();

    cpu.mem.install_rom(buffer, size);

    delete[] buffer;

    return true;
}