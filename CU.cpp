#include "CU.h"

void CU::load(int idxReg, int intMem, Register &reg, Memory &mem) {
    string value = mem.getCell(intMem);
    reg.set(idxReg, value);
}

void CU::load(int idxReg, int val, Register &reg) {
    reg.set(idxReg, alu.decToHex(val));
}

void CU::store(int idxReg, int idxMem, Register &reg, Memory &mem) {

    string hexaString = reg.get(idxReg);
    string hexaNew="";

    for(char ch : hexaString){
        if(ch == 'a'|| ch=='b' || ch=='c'|| ch=='d' || ch=='e' || ch=='f' ){
            hexaNew += toupper(ch);
        }
        else{
            hexaNew += ch;
        }
    }

    string value = hexaNew;
    mem.setCell(idxMem, value);
}

void CU::move(int idxReg1, int idxReg2, Register &reg) {
    string value = reg.get(idxReg1);
    reg.set(idxReg2, value);
}

void CU::jump(int idxReg, int idxMem, Register &reg, int &PC) {
    if (reg.get(idxReg) == reg.get(0)) {
        PC = idxMem;
    }
}

void CU::halt() {
    cout << "Machine halted." << endl;
    exit(0);
}
