#ifndef CLASSES_FOR_GH_ALU_H
#define CLASSES_FOR_GH_ALU_H
#include <bits/stdc++.h>
using namespace std;


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


#endif //CLASSES_FOR_GH_ALU_H
