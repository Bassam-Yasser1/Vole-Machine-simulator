#include "Register.h"

Register::Register(int size) : registers(size, "00") {}

string Register::get(int index) const {
    if (index < 0 || index >= registers.size()) {
        cerr << "Error: Invalid register access at index " << index << endl;
        return "00";
    }
    return registers[index];
}

void Register::set(int index, const string &value) {
    if (index < 0 || index >= registers.size()) {
        cerr << "Error: Invalid register access at index " << index << endl;
        return;
    }
    registers[index] = value;
}