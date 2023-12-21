#pragma once
#include <string>

using namespace std;

class Variable {
public:
    Variable() {}
    string name = "";
    bool is_const = false;
    int value;
    int flag = 0; //0 - нет значения, 1 - есть значение
    Variable(string name_) :name(name_) {}

};