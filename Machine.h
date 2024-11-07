#ifndef CLASSES_FOR_GH_MACHINE_H
#define CLASSES_FOR_GH_MACHINE_H
#include <bits/stdc++.h>
using namespace std;
class Machine {
protected:
    CPU processor;

public:
    void loadProgram(const string &fname, Memory &memory, int startAddress);
    string inputfile();
    void inputinc(Memory &memory, int startAddress);
    void outputMachineState(Register &reg, Memory &memory);
    void runProgram(int startAddress, Memory &memory, Register &reg, int &pc);
};


#endif //CLASSES_FOR_GH_MACHINE_H
