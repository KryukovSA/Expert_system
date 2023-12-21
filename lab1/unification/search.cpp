#include "search.h"


Search::Search(Atom target_, vector<Atom> facts_, vector<Variable> all_variables_, vector<Implication_rule> all_rule_) {
    all_variables = all_variables_;
    this->facts = facts_;
    for (int i = 0; i < facts.size(); i++)
        facts[i].flag = 1;
    target = target_;
    all_rule = all_rule_;
    open_atoms.push_back(target);//целевую в стек

}

int Search::find_child() {

    for (Atom& fact : facts) {
        if (fact.name_predicate == target.name_predicate) {
            std::cout << "Цель доказана изначально" << std::endl;
            flag_solve = 0;
            return 0;
        }
    }
    int counter_rules = 0;//счетчик модужей раскрывающих текущую подцель
    int i = 0;
    while (!all_rule.empty() && i < all_rule.size() && counter_rules == 0) {
        //если унифицирует стек заключением(подцелью)
        if (all_rule[i].chose != 1 && atoms_is_unificate(open_atoms.back(), all_rule[i].conclusion_rule)) {
            counter_rules++;
            if (open_rules.empty())
                open_rules.push_back(all_rule[i]);//в список открытых правил его
            if (!open_rules.empty())
                if (open_rules.back().num != all_rule[i].num)
                    open_rules.push_back(all_rule[i]);//в список открытых правил его
            all_rule[i].chose = 1;
            cout << "работаем над правилом  " << all_rule[i].num << endl;
            int count_atoms_in_close = 0;
            for (int j = 0; j < all_rule[i].input_atoms.size(); j++) {
                if (!contain_in_facts(all_rule[i].input_atoms[j])) {
                    open_atoms.push_back((all_rule[i].input_atoms[j]));
                }
                else {//унифицирается с фактом - делаем унификацию и распространение
                    all_rule[i].input_atoms[j].flag = 1;
                    //после унифик он по сути будет равен атому из фактов
                    distribution(all_rule[i].input_atoms[j]);//и унификация тут же
                    count_atoms_in_close++;
                }
                if (count_atoms_in_close == all_rule[i].input_atoms.size()) {//модул доказан удалим его из откр и добавим в закр
                    cout << "нашли новое доказанное правило: " << all_rule[i].num << endl;
                    count_atoms_in_close = 0;
                    razmetka(all_rule[i]);

                }


            }

        }
        i++;
    }
    return counter_rules;

}

void Search::distribution(Atom &old_atom) {
    for (const Atom& curr_atom : facts)
        if (atoms_is_unificate(curr_atom, old_atom)) {//нашли конкретный факт с которым унифицируется
            for (int i = 0; i < old_atom.variables.size(); i++) {//по переменным которые унифицируем
                for (int m = 0; m < open_rules.size(); m++) {//---------------------------чтобы во все правила//по откр правилам
                    for (int j = 0; j < open_rules[m].input_atoms.size(); j++) {//по атомам откр прав.
                        for (int k = 0; k < open_rules[m].input_atoms[j].variables.size(); k++) {//по переменным в атомах из стека
                            //распространели во все атомы правила
                            if (open_rules[m].input_atoms[j].variables[k].name == old_atom.variables[i].name && open_rules[m].input_atoms[j].variables[k].name != curr_atom.variables[i].name)
                                open_rules[m].input_atoms[j].variables[k].name = curr_atom.variables[i].name;

                        }

                    }
                    for (int v = 0; v < open_rules[m].conclusion_rule.len; v++) {//по атомам заключения распространим
                            //в заключение тоже распространим
                            if (open_rules[m].conclusion_rule.variables[v].name == old_atom.variables[i].name && open_rules[m].conclusion_rule.variables[v].name != curr_atom.variables[i].name)
                                open_rules[m].conclusion_rule.variables[v].name = curr_atom.variables[i].name;
                    }
                   


                }//-----------------
                if (old_atom.variables[i].name != curr_atom.variables[i].name) {//распространяем в самый верхний(уже нам не надо на его переменную смотреть)
                    Substitution substitution(old_atom.variables[i].name, curr_atom.variables[i].name);
                    substitutions.push_back(substitution);//формируем массив подстановок
                    old_atom.variables[i].name = curr_atom.variables[i].name;

                }
            }
        }
}





bool Search::contain_in_facts(Atom atom) {
    for (const Atom& curr_atom : facts)
        if (atoms_is_unificate(curr_atom, atom)) {
            return true;
        }

    return false;
}

bool Search::atoms_is_unificate(Atom atom1, Atom atom2) {
    int count_const = 0;
    if (atom1.name_predicate == atom2.name_predicate &&
        atom1.len == atom2.len) {
        for (int i = 0; i < atom1.len; i++) {
            if (atom1.variables[i].is_const && atom2.variables[i].is_const) {
                if (atom1.variables[i].name != atom2.variables[i].name)
                    count_const++;
                    //return false;//две константы не унифицируются
            }
        }
    
        if (count_const == atom1.len) {
            return false;//две константы не унифицируются
        }

        return true;
    }
    else {
        return false;
    }


}

void Search::razmetka(Implication_rule &rule) { //мы на правиле 3 и в пременных М1 вместо x2

    distribution(open_atoms.back());//y на M1 меняем(если бы в закл несколько атомов то может сломаться)
    if(rule.num == open_rules.back().num)
        facts.push_back(open_rules.back().conclusion_rule);//закл доказаненого правила - новый факт
    else
        facts.push_back(rule.conclusion_rule);//закл доказаненого правила - новый факт

    
    open_atoms.pop_back();
    close_rules.push_back(open_rules.back());
    open_rules.pop_back();
    cout << "добавили факт " << facts.back().name_predicate << " " << facts.back().get_var() << endl;
    cout << "все факты " << show_facts() << endl;
    cout << "открытые вершины" << show_open_atoms() << endl;

    if (open_atoms.size() == 1) {//в стеке 1 вершина и все ее атомы в фактах
        //унификац и распростр знач переменных в другие атомы правила этого
        //доказанную подцель убир из стека
        if (all_in_facts(open_atoms.back()))
            flag_solve = 0;//нашли решение

    }
}

void Search::back_search() {
    int iteration = 0;
    int k = 0;
    while (flag_solve && flag_not_solve) {

      /*  if (contain_in_facts(open_atoms.back()) {
            razmetka()
        }*/

        k = find_child();//метод потомков
        if (flag_solve == 0) {
            cout << "решение найдено" << endl;//вывод списка закр правил
            return;
        }

        //так ли???
        //if (k == 0 && (open_atoms.empty() || open_atoms.back().name_predicate == target.name_predicate)) {
        //    flag_not_solve = 0;
        //    cout << "нет решения" << endl;
        //}


        iteration++;

    }

}

void Search::backtraking() {}

bool Search::all_in_facts(Atom atom) {
    int collision = 0;
    for (int i = 0; i < all_rule.size(); i++) {
        if (atoms_is_unificate(atom, all_rule[i].conclusion_rule)) {
            for (int j = 0; j < all_rule[i].input_atoms.size(); j++) {
                if (contain_in_facts(all_rule[i].input_atoms[j])) {
                    collision++;
                }
            }
            if (collision == all_rule[i].input_atoms.size()) {
                return true;
            }
        }
    }
    return false;
}