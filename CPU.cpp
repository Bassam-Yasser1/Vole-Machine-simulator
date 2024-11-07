#include "CPU.h"

bool CPU::isHalted() const {
    return halted;
}

void CPU::runNextStep(Memory &mem, Register &reg, int &pc) {
    fetch(mem, pc);
    if (!halted) {
        execute(reg, mem, pc);
    }
}

void CPU::fetch(Memory &mem, int &programCounter) {
    if (programCounter >= 256 || programCounter + 1 >= 256) {
        cerr << "Error: Program counter out of bounds" << endl;
        halted = true; // Halt execution if out of bounds
        return;
    }

    instructionRegister = mem.getCell(programCounter) + mem.getCell(programCounter + 1);
    cout << "Fetched instruction: " << instructionRegister << " at address: " << programCounter << endl;

    if (instructionRegister == "C000" || programCounter>=254) halted = true;
    else programCounter += 2;
}

void CPU::execute(Register &reg, Memory &mem, int &pc) {
    char opcode = instructionRegister[0];
    int operand1 = instructionRegister[1] - '0';
    string operand2 = instructionRegister.substr(2, 2);

    if(opcode == '1') {
        cu.load(operand1, alu.hexToDec(operand2), reg, mem);
    } else if(opcode == '2') {
        cu.load(operand1, alu.hexToDec(operand2), reg);
    } else if(opcode == '3') {
        cu.store(operand1, alu.hexToDec(operand2), reg, mem);
    } else if(opcode == '4') {
        cu.move(operand2[0] - '0', operand2[1] - '0', reg);
    } else if(opcode == '5') {
        alu.addTwosComplement(operand1, operand2[0] - '0', operand2[1] - '0', reg);
    } else if(opcode == '6') {
        alu.addFloatingPoint(operand1, operand2[0] - '0', operand2[1] - '0', reg);
    } else if(opcode == 'B') {
        cu.jump(operand1, alu.hexToDec(operand2), reg, pc);
    } else if(opcode == 'C') {
        cu.halt();
    }
}

void CPU::setProgramCounter(int value, int &programCounter) {
    programCounter = value;
}

int CPU::getProgramCounter(int &programCounter) const {
    return programCounter;
}
