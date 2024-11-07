#ifndef CLASSES_FOR_GH_CPU_H
#define CLASSES_FOR_GH_CPU_H
#include <bits/stdc++.h>
using namespace std;
class CPU {
private:
    string instructionRegister;
    ALU alu;
    CU cu;
    bool halted = false;

public:
    bool isHalted() const;
    void runNextStep(Memory &mem, Register &reg, int &pc);
    void fetch(Memory &mem, int &programCounter);
    void execute(Register &reg, Memory &mem, int &pc);
    void setProgramCounter(int value, int &programCounter);
    int getProgramCounter(int &programCounter) const;
};

#endif //CLASSES_FOR_GH_CPU_H
