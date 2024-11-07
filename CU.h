#ifndef CLASSES_FOR_GH_CU_H
#define CLASSES_FOR_GH_CU_H
#include <bits/stdc++.h>
using namespace std;
class CU {
public:
    ALU alu;

    void load(int idxReg, int intMem, Register &reg, Memory &mem);
    void load(int idxReg, int val, Register &reg);
    void store(int idxReg, int idxMem, Register &reg, Memory &mem);
    void move(int idxReg1, int idxReg2, Register &reg);
    void jump(int idxReg, int idxMem, Register &reg, int &PC);
    void halt();
};



#endif //CLASSES_FOR_GH_CU_H
