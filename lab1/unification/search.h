#pragma once
#include <vector>
#include"Implication_rule.h"
#include "Substitution.h"
#include <iostream>
#include <stack>
using namespace std;

class Search {
public:
    Search() {}
    Atom target;
    vector<Variable> all_variables;

    bool flag_solve = 1;//пока не решили
    bool flag_not_solve = 1; // флаг нет решения

    //база знаний
    vector<Implication_rule> all_rule;

    vector<Atom> open_atoms;//как откр верш - стек
    vector<Atom> facts; //как закр вер
    vector<Implication_rule> close_rules;
    vector<Implication_rule> open_rules;

    //массив подстановок
    vector<Substitution> substitutions;

    Search(Atom target_, vector<Atom> facts_, vector<Variable> all_variables_, vector<Implication_rule> all_rule_);
    bool atoms_is_unificate(Atom atom1, Atom atom2);
    bool contain_in_facts(Atom atom);
    void distribution(Atom &old_atom);
    int find_child();
    bool all_in_facts(Atom atom);
    void razmetka(Implication_rule &rule);
    string show_facts() {
        string facti = " ";
        for (int i = 0; i < facts.size(); i++) {
            facti += facts[i].name_predicate;
            facti += " ";
        }
        return facti;
    }
    string show_open_atoms() {
        string o_a = " ";
        for (int i = 0; i < open_atoms.size(); i++) {
            o_a += open_atoms[i].name_predicate;
            o_a += " ";
        }
        return o_a;
    }



    void back_search();

    void backtraking();
};