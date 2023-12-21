#pragma once
#include <string>
#include "variable.h"
#include <vector>

using namespace std;

class Substitution {
public:
    Substitution() {}
    string old_name;
    string new_name;

    Substitution(string old_name_, string new_name_) :old_name(old_name_),
        new_name(new_name_) {}

};