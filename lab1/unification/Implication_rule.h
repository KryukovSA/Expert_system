#pragma once

#include "Atom.h"
#include <vector>

using namespace std;

enum mark_rules { close, open };
class Implication_rule {
public:
    Implication_rule() {}
    Atom conclusion_rule;
    vector<Atom> input_atoms;//������ ������ �� ������� �������
    int num;//����� �������
    mark_rules metka = open;
    bool chose = 0; //���������� ��� ������� ��� �� ����������

    Implication_rule(Atom conclusion_rule_, vector<Atom> input_atoms_, int num_) :conclusion_rule(conclusion_rule_),
        input_atoms(input_atoms_), num(num_) {}

};