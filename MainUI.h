#ifndef CLASSES_FOR_GH_MAINUI_H
#define CLASSES_FOR_GH_MAINUI_H
#include <bits/stdc++.h>
using namespace std;

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



#endif //CLASSES_FOR_GH_MAINUI_H
