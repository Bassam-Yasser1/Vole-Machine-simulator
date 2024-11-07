#include "A1_Task4_S20_S5_S7_20230089_20230051_20230412.h"


// Memory Class Implementation
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

// Register Class Implementation
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

// ALU Class Implementation
int ALU::hexToDec(const string &hexStr) {
    int decimalValue;
    stringstream ss;
    ss << hex << hexStr;
    ss >> decimalValue;
    return decimalValue;
}

string ALU::decToHex(int decimalValue) {
    stringstream ss;
    ss << hex << setw(2) << setfill('0') << decimalValue;
    return ss.str();
}

void ALU::addTwosComplement(int idxReg1, int idxReg2, int idxReg3, Register &reg) {
    int val1 = hexToDec(reg.get(idxReg2));
    int val2 = hexToDec(reg.get(idxReg3));
    int result = val1 + val2;

    if (result > 255) {
        result -= 256;
    }
    reg.set(idxReg1, decToHex(result));
}

double ALU::binaryaryToFloat (string s){
    double decimal=0;
    int sign=1;
    if(s[0]=='-'){
        s.erase(s.begin());
        sign=-1;
    }
    int Position=find(s.begin(),s.end(),'.')-s.begin();

    for ( int i = 0; i < Position; i++)   {
        decimal += (s[i] - '0') * pow(2, Position-i-1);
    }int power=-1;
    for(int i=Position+1; i < s.size(); i++){
        decimal+=(s[i]-'0')*pow(2,power);
        power--;
    }
    if(sign==-1){
        decimal*=-1;
    }

    return decimal;
}

string ALU::decimalTobinaryary1(int n){
    string binary = "";
    while (n > 0) {
        binary = to_string(n % 2) + binary;
        n /= 2;
    }
    for(int i=0;binary.size()<4;i++){
        binary="0"+binary;
    }
    return binary;
}

double ALU::HexaToFloat(string number) {
    string hx="0123456789ABCDEF";
    string binary;
    string stringnumber1=decimalTobinaryary1((find(hx.begin(), hx.end(),number[0])-hx.begin()));
    string stringnumber2=decimalTobinaryary1((find(hx.begin(), hx.end(),number[1])-hx.begin()));

    int sign=stringnumber1[0]=='1'?-1:1;

    int moves= binaryaryToFloat(stringnumber1.substr(1,3));

    moves-=4;

    if(moves>0) {
        stringnumber2.insert(moves, ".");
    }
    if(moves<0){
        for(int i=0; i>moves; i--){
            stringnumber2.insert(0, "0");
        }
    }
    if(sign==-1) {
        stringnumber2 = "-" + stringnumber2;
    }
    if(moves<=0) {
        stringnumber2 = "0." + stringnumber2;
    }
    double ans=binaryaryToFloat(stringnumber2);
    return ans;

}

string ALU::DecimalTobinaryaryFloat(double number){
    string binary;
    string stringnumber1=to_string(number);
    int sign=1;
    if(stringnumber1[0]=='-')
    {
        sign=-1;
        stringnumber1.erase(stringnumber1.begin());

    }
    for(int i=stringnumber1.size()-1; i>=0,stringnumber1[i]=='0';i--){
        stringnumber1.pop_back();
    }

    int stringnumber2=stod(stringnumber1);
    string remainder5;
    for(int i=0; i<stringnumber1.length(); i++){
        if(stringnumber1[i]=='.'){
            i++;
            for(;i<stringnumber1.length();i++){remainder5+=stringnumber1[i];

            };
        }
    }
    remainder5="0."+remainder5;
    double remainder=stod(remainder5);

    while(stringnumber2>0){
        binary=to_string(stringnumber2%2)+binary;
        stringnumber2/=2;
    }
    binary+='.';

    while(remainder>0){
        remainder*=2;
        if(remainder>=1){
            binary+="1";
            remainder-=1;
        }
        else binary+="0";
    }
    if(sign==-1){
        binary="-"+binary;}

    return binary;
}

string ALU::binaryToHex(string binary){
    string hex;
    int middle=0;
    if(binary[0]=='-'){
        hex+="1";
        binary.erase(binary.begin());
    }
    else hex+="0";
    for(int i=0;i<binary.size();i++){
        if(binary[i]=='.')break;
        middle++;
    }
    middle+=4;
    string first=decimalTobinaryary1(middle);
    for(int i=0;first.size()>3;i++){
        first.erase(first.begin());}
    hex+=first;

    string last;
    for(int i=0;i<binary.size();i++){
        if(binary[i]=='.')continue;
        last+=binary[i];

    }
    hex+=last;
    for(int i=0;8>hex.size();i++){
        hex+="0";
    }

    return hex;
}

string ALU::Ans(string binary){
    string hex1=binary.substr(0,4);
    string hex2=binary.substr(4,8);
    double hex10=binaryaryToFloat(hex1);
    double hex20=binaryaryToFloat(hex2);
    string hexastr="0123456789ABCDEF";
    string ans;
    ans+=hexastr[(int)hex10];
    ans+=hexastr[(int)hex20];

    return ans;

}

void ALU::addFloatingPoint(int idxReg1, int idxReg2, int idxReg3, Register &reg) {
    string hexaStringA = reg.get(idxReg2);
    string hexaStringB = reg.get(idxReg3);
    string hexaNew="";
    string hexaNew2="";

    for(char ch : hexaStringA){
        if(ch == 'a'|| ch=='b' || ch=='c'|| ch=='d' || ch=='e' || ch=='f' ){
            hexaNew += toupper(ch);
        }
        else{
            hexaNew += ch;
        }
    }
    for (char ch : hexaStringB) {
        if (ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f') {
            hexaNew2 += toupper(ch);
        } else {
            hexaNew2 += ch;
        }
    }
    double floatA = HexaToFloat(hexaNew);
    double floatB = HexaToFloat(hexaNew2);
    double sum = floatA + floatB;
    string sumHex = Ans(binaryToHex(DecimalTobinaryaryFloat(sum)));
    cout << sumHex << endl;
    reg.set(idxReg1, sumHex);
}

// CU Class Implementation
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

// CPU Class Implementation
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

// Machine Class Implementation
void Machine::loadProgram(const string &fname, Memory &memory, int startAddress) {
    ifstream file(fname);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fname << endl;
        return;
    }

    string instruction;
    int index = startAddress; // Use startAddress instead of 0

    while (file >> instruction) {
        for (size_t i = 0; i < instruction.length(); i += 2) {
            string hexByte = instruction.substr(i, 2);
            memory.setCell(index, hexByte);
            index++;
        }
    }
    file.close();
    cout << "Program loaded successfully from: " << fname << " starting at address " << hex << startAddress << endl;
}

string Machine::inputfile() {
    string filename;
    cout << "Enter file name: ";
    cin >> filename;
    cin.ignore();
    return filename;
}

void Machine::inputinc(Memory &memory, int startAddress) {
    string instruction;
    int index = startAddress; // Start storing from the specified address
    cout << "Enter instruction (type 'C000' to finish): " << endl;

    while (true) {
        getline(cin, instruction);
        if (instruction == "C000")
            break;

        // Validate and clean input
        instruction.erase(remove_if(instruction.begin(), instruction.end(), ::isspace), instruction.end());
        if (instruction.length() % 2 != 0) {
            cout << "Invalid instruction length. Please enter an even number of hex digits." << endl;
            continue;
        }

        // Store instruction in memory
        for (size_t i = 0; i < instruction.length(); i += 2) {
            string hexByte = instruction.substr(i, 2);
            memory.setCell(index++, hexByte);
        }
    }
}

void Machine::outputMachineState(Register &reg, Memory &memory) {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            cout << memory.getCell(i*16 + j) << " ";
        }
        cout << endl;
    }

    cout << "\nRegister State:" << endl;

    for (int i = 0; i < 16; i++)
    {
        string temp = "";
        for(char ch : reg.get(i)){
            if(ch == 'a'|| ch=='b' || ch=='c'|| ch=='d' || ch=='e' || ch=='f' ){
                temp += toupper(ch);
            }
            else{
                temp += ch;
            }
        }
        cout << "R[" << i << "]: " << temp << "  ";
    }
    cout << endl;
}

void Machine::runProgram(int startAddress, Memory &memory, Register &reg, int &pc) {
    processor.setProgramCounter(startAddress,pc);
    while (!processor.isHalted() && processor.getProgramCounter(pc) < 256) { // Added bounds check
        processor.runNextStep(memory,reg,pc);
    }
    if (processor.getProgramCounter(pc) >= 256) {
        cerr << "Program ended due to out-of-bounds memory access." << endl;
    }
}

// mainUI Class Implementation
mainUI::mainUI() : counter("0") {}

void mainUI::inputchoice(Register &reg, Memory &memory, int &pc) {
    int ch;
    cout << "Enter your choice [0 to 4]: ";
    cin >> ch;
    cin.ignore();
    int startAddress = stoi(counter, nullptr, 16);

    if (ch == 0) exit(0);
    else if (ch == 1) machine.loadProgram(machine.inputfile(), memory, startAddress);
    else if (ch == 2) machine.inputinc(memory, startAddress);
    else if (ch == 3) machine.runProgram(startAddress, memory, reg, pc);
    else if (ch == 4) machine.outputMachineState(reg, memory);
    else cout << "Invalid choice" << endl;
}

void mainUI::displaymenu() {
    cout << "Vole Machine Menu" << endl;
    cout << "Counter (start execution from address): " << counter << endl;
    cout << "1- Load Program from File" << endl;
    cout << "2- Input Instructions Manually" << endl;
    cout << "3- Run Program" << endl;
    cout << "4- Display Memory and Registers" << endl;
    cout << "0- Exit" << endl;
}

void mainUI::setCounter() {
    cout << "Enter starting memory address (counter) for execution: ";
    cin >> counter;
    cin.ignore();
}

void mainUI::start(Register &reg, Memory &memory, int &pc) {
    setCounter();
    do
    {
        displaymenu();
        inputchoice(reg,memory,pc);
    } while (true);
}
//(The main)
//#include <bits/stdc++.h>
//#include "A1_Task4_S20_S5_S7_20230089_20230051_20230412.h"
//using namespace std;
//int main()
//{
//    mainUI ui;
//    Register reg; // Initialize register object for use in the program
//    Memory memory; // Initialize memory object for use in the program
//    int pc=0;
//    ui.start(reg,memory,pc);
//    return 0;
//}