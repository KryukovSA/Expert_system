#pragma once
#include <string>
#include "variable.h"
#include <vector>

using namespace std;

class Atom {
public:
    Atom() {}
    string name_predicate = "";
    vector<Variable> variables;
    int len; //количество переменных
    int flag = 0; //0 - нет доказан, 1 - атом доказан
    Atom(string name_predicate_, vector<Variable> variables_, int len_) :name_predicate(name_predicate_),
        variables(variables_), len(len_) {}
    string get_var() {
        string vars = "{ ";
        for (int i = 0; i < len; i++) {
            vars += variables[i].name;
            vars += ", ";
        }
        vars += "}";
        return vars;
    }
};