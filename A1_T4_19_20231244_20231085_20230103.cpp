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

// Simulator class implementation
Simulator::Simulator() : pc(0), halted(false), cpu(memory, registers, pc, halted) {}

bool Simulator::isValidInstruction(const string &instruction) {
    if (instruction.length() != 4) return false;
    regex instructionFormat("[1-6BC][0-9A-F]{3}");
    return regex_match(instruction, instructionFormat);
}

void Simulator::loadProgram(const string &filename) {
    ifstream file(filename);
    string instruction;
    int address = 0;
    vector<string> instructions;

    while (file >> instruction) {
        if (isValidInstruction(instruction)) {
            instructions.push_back(instruction);
        } else {
            cout << "Skipping invalid instruction: " << instruction << endl;
        }
    }
    file.close();

    if (instructions.empty() || instructions.back() != "C000") {
        instructions.push_back("C000");
    }

    for (const auto &instr : instructions) {
        memory.store(address++, instr.substr(0, 2));
        memory.store(address++, instr.substr(2, 2));
    }
}

void Simulator::run_entire_program() {
    while (!halted && pc < 256) {
        cpu.fetchInstruction();
        cpu.executeInstruction();
        pc += 2;
    }
    displayState();
}

void Simulator::runStepByStep() {
    char choice;
    while (!halted && pc < 256) {
        cpu.fetchInstruction();
        cpu.executeInstruction();
        pc += 2;

        displayState();
        if (cpu.getInstructionRegister() != "C000") {
            cout << "Step completed. Continue to next step? (y/n): ";
            cin >> choice;
            if (choice != 'y' && choice != 'Y') break;
        }
    }
}

void Simulator::displayState() {
    registers.printRegisters();
    memory.printMemory();
    cout << "PC: " << setw(2) << setfill('0') << hex << uppercase << pc << "\n";
    cout << "IR: " << cpu.getInstructionRegister() << "\n";
    cout << "-----------------------------\n";
}

void Simulator::reset() {
    pc = 0;
    halted = false;
    memory = Memory();
    registers = Registers();
    cpu.setInstructionRegister();
    cout << "Simulator reset.\n";
}

// Simulator class implementation
Simulator::Simulator() : pc(0), halted(false), cpu(memory, registers, pc, halted) {}

bool Simulator::isValidInstruction(const string &instruction) {
    if (instruction.length() != 4) return false;
    regex instructionFormat("[1-6BC][0-9A-F]{3}");
    return regex_match(instruction, instructionFormat);
}

void Simulator::loadProgram(const string &filename) {
    ifstream file(filename);
    string instruction;
    int address = 0;
    vector<string> instructions;

    while (file >> instruction) {
        if (isValidInstruction(instruction)) {
            instructions.push_back(instruction);
        } else {
            cout << "Skipping invalid instruction: " << instruction << endl;
        }
    }
    file.close();

    if (instructions.empty() || instructions.back() != "C000") {
        instructions.push_back("C000");
    }

    for (const auto &instr : instructions) {
        memory.store(address++, instr.substr(0, 2));
        memory.store(address++, instr.substr(2, 2));
    }
}

void Simulator::run_entire_program() {
    while (!halted && pc < 256) {
        cpu.fetchInstruction();
        cpu.executeInstruction();
        pc += 2;
    }
    displayState();
}

void Simulator::runStepByStep() {
    char choice;
    while (!halted && pc < 256) {
        cpu.fetchInstruction();
        cpu.executeInstruction();
        pc += 2;

        displayState();
        if (cpu.getInstructionRegister() != "C000") {
            cout << "Step completed. Continue to next step? (y/n): ";
            cin >> choice;
            if (choice != 'y' && choice != 'Y') break;
        }
    }
}

void Simulator::displayState() {
    registers.printRegisters();
    memory.printMemory();
    cout << "PC: " << setw(2) << setfill('0') << hex << uppercase << pc << "\n";
    cout << "IR: " << cpu.getInstructionRegister() << "\n";
    cout << "-----------------------------\n";
}

void Simulator::reset() {
    pc = 0;
    halted = false;
    memory = Memory();
    registers = Registers();
    cpu.setInstructionRegister();
    cout << "Simulator reset.\n";
}

