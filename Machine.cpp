#include "Machine.h"

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