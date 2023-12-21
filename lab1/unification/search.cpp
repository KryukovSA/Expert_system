#include "search.h"


Search::Search(Atom target_, vector<Atom> facts_, vector<Variable> all_variables_, vector<Implication_rule> all_rule_) {
    all_variables = all_variables_;
    this->facts = facts_;
    for (int i = 0; i < facts.size(); i++)
        facts[i].flag = 1;
    target = target_;
    all_rule = all_rule_;
    open_atoms.push_back(target);//������� � ����

}

int Search::find_child() {

    for (Atom& fact : facts) {
        if (fact.name_predicate == target.name_predicate) {
            std::cout << "���� �������� ����������" << std::endl;
            flag_solve = 0;
            return 0;
        }
    }
    int counter_rules = 0;//������� ������� ������������ ������� �������
    int i = 0;
    while (!all_rule.empty() && i < all_rule.size() && counter_rules == 0) {
        //���� ����������� ���� �����������(��������)
        if (all_rule[i].chose != 1 && atoms_is_unificate(open_atoms.back(), all_rule[i].conclusion_rule)) {
            counter_rules++;
            if (open_rules.empty())
                open_rules.push_back(all_rule[i]);//� ������ �������� ������ ���
            if (!open_rules.empty())
                if (open_rules.back().num != all_rule[i].num)
                    open_rules.push_back(all_rule[i]);//� ������ �������� ������ ���
            all_rule[i].chose = 1;
            cout << "�������� ��� ��������  " << all_rule[i].num << endl;
            int count_atoms_in_close = 0;
            for (int j = 0; j < all_rule[i].input_atoms.size(); j++) {
                if (!contain_in_facts(all_rule[i].input_atoms[j])) {
                    open_atoms.push_back((all_rule[i].input_atoms[j]));
                }
                else {//������������� � ������ - ������ ���������� � ���������������
                    all_rule[i].input_atoms[j].flag = 1;
                    //����� ������ �� �� ���� ����� ����� ����� �� ������
                    distribution(all_rule[i].input_atoms[j]);//� ���������� ��� ��
                    count_atoms_in_close++;
                }
                if (count_atoms_in_close == all_rule[i].input_atoms.size()) {//����� ������� ������ ��� �� ���� � ������� � ����
                    cout << "����� ����� ���������� �������: " << all_rule[i].num << endl;
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
        if (atoms_is_unificate(curr_atom, old_atom)) {//����� ���������� ���� � ������� �������������
            for (int i = 0; i < old_atom.variables.size(); i++) {//�� ���������� ������� �����������
                for (int m = 0; m < open_rules.size(); m++) {//---------------------------����� �� ��� �������//�� ���� ��������
                    for (int j = 0; j < open_rules[m].input_atoms.size(); j++) {//�� ������ ���� ����.
                        for (int k = 0; k < open_rules[m].input_atoms[j].variables.size(); k++) {//�� ���������� � ������ �� �����
                            //�������������� �� ��� ����� �������
                            if (open_rules[m].input_atoms[j].variables[k].name == old_atom.variables[i].name && open_rules[m].input_atoms[j].variables[k].name != curr_atom.variables[i].name)
                                open_rules[m].input_atoms[j].variables[k].name = curr_atom.variables[i].name;

                        }

                    }
                    for (int v = 0; v < open_rules[m].conclusion_rule.len; v++) {//�� ������ ���������� �������������
                            //� ���������� ���� �������������
                            if (open_rules[m].conclusion_rule.variables[v].name == old_atom.variables[i].name && open_rules[m].conclusion_rule.variables[v].name != curr_atom.variables[i].name)
                                open_rules[m].conclusion_rule.variables[v].name = curr_atom.variables[i].name;
                    }
                   


                }//-----------------
                if (old_atom.variables[i].name != curr_atom.variables[i].name) {//�������������� � ����� �������(��� ��� �� ���� �� ��� ���������� ��������)
                    Substitution substitution(old_atom.variables[i].name, curr_atom.variables[i].name);
                    substitutions.push_back(substitution);//��������� ������ �����������
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
                    //return false;//��� ��������� �� �������������
            }
        }
    
        if (count_const == atom1.len) {
            return false;//��� ��������� �� �������������
        }

        return true;
    }
    else {
        return false;
    }


}

void Search::razmetka(Implication_rule &rule) { //�� �� ������� 3 � � ��������� �1 ������ x2

    distribution(open_atoms.back());//y �� M1 ������(���� �� � ���� ��������� ������ �� ����� ���������)
    if(rule.num == open_rules.back().num)
        facts.push_back(open_rules.back().conclusion_rule);//���� ������������ ������� - ����� ����
    else
        facts.push_back(rule.conclusion_rule);//���� ������������ ������� - ����� ����

    
    open_atoms.pop_back();
    close_rules.push_back(open_rules.back());
    open_rules.pop_back();
    cout << "�������� ���� " << facts.back().name_predicate << " " << facts.back().get_var() << endl;
    cout << "��� ����� " << show_facts() << endl;
    cout << "�������� �������" << show_open_atoms() << endl;

    if (open_atoms.size() == 1) {//� ����� 1 ������� � ��� �� ����� � ������
        //�������� � ��������� ���� ���������� � ������ ����� ������� �����
        //���������� ������� ���� �� �����
        if (all_in_facts(open_atoms.back()))
            flag_solve = 0;//����� �������

    }
}

void Search::back_search() {
    int iteration = 0;
    int k = 0;
    while (flag_solve && flag_not_solve) {

      /*  if (contain_in_facts(open_atoms.back()) {
            razmetka()
        }*/

        k = find_child();//����� ��������
        if (flag_solve == 0) {
            cout << "������� �������" << endl;//����� ������ ���� ������
            return;
        }

        //��� ��???
        //if (k == 0 && (open_atoms.empty() || open_atoms.back().name_predicate == target.name_predicate)) {
        //    flag_not_solve = 0;
        //    cout << "��� �������" << endl;
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