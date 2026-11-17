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

const char *cartridge::cartridge_type(uint16_t code) {
    const char *name = nullptr;
    switch (code) {
    case 0x00: name = "ROM ONLY"; break;
    case 0x01: name = "MBC1"; break;
    case 0x02: name = "MBC1+RAM"; break;
    case 0x03: name = "MBC1+RAM+BATTERY"; break;
    case 0x05: name = "MBC2"; break;
    case 0x06: name = "MBC2+BATTERY"; break;
    case 0x08: name = "ROM+RAM"; break;
    case 0x09: name = "ROM+RAM+BATTERY"; break;
    case 0x0B: name = "MMM01"; break;
    case 0x0C: name = "MMM01+RAM"; break;
    case 0x0D: name = "MMM01+RAM+BATTERY"; break;
    case 0x0F: name = "MBC3+TIMER+BATTERY"; break;
    case 0x10: name = "MBC3+TIMER+RAM+BATTERY"; break;
    case 0x11: name = "MBC3"; break;
    case 0x12: name = "MBC3+RAM"; break;
    case 0x13: name = "MBC3+RAM+BATTERY"; break;
    case 0x19: name = "MBC5"; break;
    case 0x1A: name = "MBC5+RAM"; break;
    case 0x1B: name = "MBC5+RAM+BATTERY"; break;
    case 0x1C: name = "MBC5+RUMBLE"; break;
    case 0x1D: name = "MBC5+RUMBLE+RAM"; break;
    case 0x1E: name = "MBC5+RUMBLE+RAM+BATTERY"; break;
    case 0x20: name = "MBC6"; break;
    case 0x22: name = "MBC7+SENSOR+RUMBLE+RAM+BATTERY"; break;
    case 0xFC: name = "POCKET CAMERA"; break;
    case 0xFD: name = "BANDAI TAMA5"; break;
    case 0xFE: name = "HuC3"; break;
    case 0xFF: name = "HuC1+RAM+BATTERY"; break;
    default: name = "UNKNOWN"; break;
    };

    return name;
}