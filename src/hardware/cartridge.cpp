#include "../headers/cartridge.h"
#include <cstdint>

#define MAXIMUM_ROM_SIZE 32768
#define CART_TYPE_LOCATION 0x0147
#define LIC_CODE_LOCATION 0x0144
#define CGB_FLAG_LOCATION 0x0143
#define TITLE_STARTING_LOCATION 0x0134
#define DESTINATION_LOCATION 0x014A

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool cartridge::loadRom(cpu &cpu, const char *romfile) {
    ifstream rom(romfile, ios::binary | ios::ate);
    if (!rom) {
        cerr << "Rom not found" << endl;
        exit(1);
    }

    streamsize size = rom.tellg();

    if (size > MAXIMUM_ROM_SIZE || size <= 0) {
        cerr << "Invalid Rom, Rom size : " << size << endl;
        exit(1);
    }

    char *buffer = new char[size];

    rom.seekg(0, ios::beg);
    rom.read(buffer, size);
    rom.close();

    cpu.mem.install_rom(buffer, size);

    delete[] buffer;

    print_info(cpu);
    return true;
}

const char *cartridge::cartridge_type(uint8_t code) {
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

constexpr uint16_t code2(char a, char b) { return (static_cast<uint8_t>(a) << 8) | static_cast<uint8_t>(b); }

const char *cartridge::new_lic(uint16_t code) {
    switch (code) {
    case code2('0', '0'): return "None";
    case code2('0', '1'): return "Nintendo Research & Development 1";
    case code2('0', '8'): return "Capcom";
    case code2('1', '3'): return "EA (Electronic Arts)";
    case code2('1', '8'): return "Hudson Soft";
    case code2('1', '9'): return "B-AI";
    case code2('2', '0'): return "KSS";
    case code2('2', '2'): return "Planning Office WADA";
    case code2('2', '4'): return "PCM Complete";
    case code2('2', '5'): return "San-X";
    case code2('2', '8'): return "Kemco";
    case code2('2', '9'): return "SETA Corporation";
    case code2('3', '0'): return "Viacom";
    case code2('3', '1'): return "Nintendo";
    case code2('3', '2'): return "Bandai";
    case code2('3', '3'): return "Ocean Software/Acclaim Entertainment";
    case code2('3', '4'): return "Konami";
    case code2('3', '5'): return "HectorSoft";
    case code2('3', '7'): return "Taito";
    case code2('3', '8'): return "Hudson Soft";
    case code2('3', '9'): return "Banpresto";
    case code2('4', '1'): return "Ubi Soft";
    case code2('4', '2'): return "Atlus";
    case code2('4', '4'): return "Malibu Interactive";
    case code2('4', '6'): return "Angel";
    case code2('4', '7'): return "Bullet-Proof Software";
    case code2('4', '9'): return "Irem";
    case code2('5', '0'): return "Absolute";
    case code2('5', '1'): return "Acclaim Entertainment";
    case code2('5', '2'): return "Activision";
    case code2('5', '3'): return "Sammy USA Corporation";
    case code2('5', '4'): return "Konami";
    case code2('5', '5'): return "Hi Tech Expressions";
    case code2('5', '6'): return "LJN";
    case code2('5', '7'): return "Matchbox";
    case code2('5', '8'): return "Mattel";
    case code2('5', '9'): return "Milton Bradley Company";
    case code2('6', '0'): return "Titus Interactive";
    case code2('6', '1'): return "Virgin Games Ltd.";
    case code2('6', '4'): return "Lucasfilm Games";
    case code2('6', '7'): return "Ocean Software";
    case code2('6', '9'): return "EA (Electronic Arts)";
    case code2('7', '0'): return "Infogrames";
    case code2('7', '1'): return "Interplay Entertainment";
    case code2('7', '2'): return "Broderbund";
    case code2('7', '3'): return "Sculptured Software";
    case code2('7', '5'): return "The Sales Curve Limited";
    case code2('7', '8'): return "THQ";
    case code2('7', '9'): return "Accolade";
    case code2('8', '0'): return "Misawa Entertainment";
    case code2('8', '3'): return "LOZC G.";
    case code2('8', '6'): return "Tokuma Shoten";
    case code2('8', '7'): return "Tsukuda Original";
    case code2('9', '1'): return "Chunsoft Co.";
    case code2('9', '2'): return "Video System";
    case code2('9', '3'): return "Ocean Software/Acclaim Entertainment";
    case code2('9', '5'): return "Varie";
    case code2('9', '6'): return "Yonezawa/S'Pal";
    case code2('9', '7'): return "Kaneko";
    case code2('9', '9'): return "Pack-In-Video";
    case code2('9', 'H'): return "Bottom Up";
    case code2('A', '4'): return "Konami (Yu-Gi-Oh!)";
    default: return "Unknown";
    }
}

void cartridge::print_info(cpu &cpu) {
    string title;
    string CGB;
    string dest;

    for (int i = 0; i < 16; i++) {
        uint8_t ch = cpu.mem.read(TITLE_STARTING_LOCATION + i);
        if (ch == 0x00) {
            break;
        }
        title += static_cast<char>(ch);
    }

    switch (cpu.mem.read(CGB_FLAG_LOCATION)) {
    case 0x80: CGB = "CGB Mode"; break;
    case 0xC0: CGB = "NON-CGB Mode"; break;
    default: CGB = "Unknown"; break;
    }

    switch (cpu.mem.read(DESTINATION_LOCATION)) {
    case 0x00: dest = "Japan (and possibly overseas)"; break;
    case 0x01: dest = "Overseas only"; break;
    default: dest = "Unknown"; break;
    }

    uint8_t type_code = cpu.mem.read(CART_TYPE_LOCATION);
    uint16_t lic_code = (cpu.mem.read(LIC_CODE_LOCATION) << 8) | cpu.mem.read(LIC_CODE_LOCATION + 1);
    cout << "Title : " << title << endl;
    cout << "New licensee code : " << new_lic(lic_code) << endl;
    cout << "Cartride Type : " << cartridge_type(type_code) << endl;
    cout << "CGB flag : " << CGB << endl;
    cout << "Destination : " << dest << endl;
}
