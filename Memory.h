#ifndef CLASSES_FOR_GH_MEMORY_H
#define CLASSES_FOR_GH_MEMORY_H
#include <bits/stdc++.h>
using namespace std;
    class Memory {
    public:
        vector<string> memory;
        Memory(int size = 256);

        string getCell(int address);
        void setCell(int address, const string &value);
    };
};


#endif //CLASSES_FOR_GH_MEMORY_H
