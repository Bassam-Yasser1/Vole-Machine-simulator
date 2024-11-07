#ifndef CLASSES_FOR_GH_REGISTER_H
#define CLASSES_FOR_GH_REGISTER_H
#include <bits/stdc++.h>
using namespace std;

class Register {
public:
    vector<string> registers;
    Register(int size = 16);

    string get(int index) const;
    void set(int index, const string& value);
};


#endif //CLASSES_FOR_GH_REGISTER_H
