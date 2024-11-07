#include "MainUI.h"

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
