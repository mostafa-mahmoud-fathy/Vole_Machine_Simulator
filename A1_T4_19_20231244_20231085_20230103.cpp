#include "Simulator.h"

// Memory class implementation
Memory::Memory(size_t size) {
    memory.resize(size, "00");
}

string Memory::load(int address) {
    if (address >= 0 && address < memory.size()) {
        return memory[address];
    }
    return "00";
}

void Memory::store(int address, const string &hexValue) {
    if (address >= 0 && address < memory.size()) {
        memory[address] = hexValue;
    }
}

void Memory::printMemory() {
    cout << "Memory :" << endl;
    cout << "     ";
    for (int col = 0; col < 16; ++col) {
        if (col < 10) cout << col << "  ";
        else cout << static_cast<char>('A' + col - 10) << "  ";
    }
    cout << endl;

    for (int row = 0; row < 16; ++row) {
        if (row < 10) cout << " " << row << " | ";
        else cout << " " << static_cast<char>('A' + row - 10) << " | ";

        for (int col = 0; col < 16; ++col) {
            int address = row * 16 + col;
            cout << memory[address] << " ";
        }
        cout << endl;
    }
}

// Registers class implementation
Registers::Registers(size_t count) {
    registers.resize(count, "00");
}

string Registers::load(int reg) {
    if (reg >= 0 && reg < registers.size()) {
        return registers[reg];
    }
    return "00";
}

void Registers::store(int reg, const string &hexValue) {
    if (reg >= 0 && reg < registers.size()) {
        registers[reg] = hexValue;
    }
}

void Registers::printRegisters() {
    cout << "Registers : ";
    for (int i = 0; i < registers.size(); ++i) {
        cout << "R" << i << ": " << registers[i] << " ";
    }
    cout << endl;
}
