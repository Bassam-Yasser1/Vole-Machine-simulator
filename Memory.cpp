#include "Memory.h"

Memory::Memory(int size) : memory(size, "00") {}

string Memory::getCell(int address) {
    if (address < 0 || address >= 256) {
        cerr << "Error: Invalid memory access at address " << address << endl;
        return "00"; // Return a default value to prevent crashes
    }
    return memory[address];
}

void Memory::setCell(int address, const string &value) {
    if (address < 0 || address >= 256) {
        cerr << "Error: Invalid memory access at address " << address << endl;
        return;
    }
    memory[address] = value;
}