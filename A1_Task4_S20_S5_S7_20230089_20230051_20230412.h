#ifndef VOLEMACHINECODE_A1_TASK4_S20_S5_S7_20230089_20230051_20230412_H
#define VOLEMACHINECODE_A1_TASK4_S20_S5_S7_20230089_20230051_20230412_H

#include <bits/stdc++.h>
using namespace std;

// Memory class to handle memory operations
class Memory {
public:
    vector<string> memory;
    Memory(int size = 256);

    string getCell(int address);
    void setCell(int address, const string &value);
};

// Register class to handle registers
class Register {
public:
    vector<string> registers;
    Register(int size = 16);

    string get(int index) const;
    void set(int index, const string& value);
};

// ALU class to perform arithmetic and logical operations
class ALU {
public:
    int hexToDec(const string &hexStr);
    string decToHex(int decimalValue);

    void addTwosComplement(int idxReg1, int idxReg2, int idxReg3, Register &reg);
    double binaryaryToFloat(string s);
    string decimalTobinaryary1(int n);
    double HexaToFloat(string number);
    string DecimalTobinaryaryFloat(double number);
    string binaryToHex(string binary);
    string Ans(string binary);
    void addFloatingPoint(int idxReg1, int idxReg2, int idxReg3, Register &reg);
};

// CU class to manage control unit functions
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

// CPU class to manage program execution
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

// Machine class to manage memory and CPU
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

// mainUI class to handle user interaction
class mainUI {
private:
    Machine machine;
    string counter;

public:
    mainUI();
    void inputchoice(Register &reg, Memory &memory, int &pc);
    void displaymenu();
    void setCounter();
    void start(Register &reg, Memory &memory, int &pc);
};


#endif //VOLEMACHINECODE_A1_TASK4_S20_S5_S7_20230089_20230051_20230412_H
