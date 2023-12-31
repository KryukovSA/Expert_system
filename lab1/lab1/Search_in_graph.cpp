#include "Search_in_graph.h"
#include <algorithm>

Search_in_graph::Search_in_graph(vector<Module_rule> module_rules_, Node target_node_, vector<Node> initial_nodes_, int count_nodes_) {
    this->module_rules = module_rules_;
    this->close_nodes = initial_nodes_; //�� � ����� �� �������
    for (int i = 0; i < close_nodes.size(); i++)
        close_nodes[i].flag = 1;
    target_vert = target_node_;
    count_nodes = count_nodes_;
}

void Search_in_graph::back_search() {
    int iteration = 0;
    int old_count_close_rul = 0;
    while (flag_solve && flag_not_solve) {
        int j = create_close_rules();
 
        if (iteration > 0 && j == old_count_close_rul) {
            cout << "�� ����� �������� ������� �� �������" << endl;
            break;
        }
              cout << "������� ������ ������ ������" << endl;
        for (int i = 0; i < close_rules.size(); i++)
            cout << close_rules[i] << " ";
        cout << endl;
        old_count_close_rul = j;
        if (flag_solve == 0) {
            cout << "������� �������" << endl;
            return;
        }
        if (j == 0) {
            flag_not_solve = 0;
            cout << "��� �������" << endl;
        }


        iteration++;

    }

}

//����� ������ � ������ ������ ������ ���������� ����� �������
int Search_in_graph::create_close_rules() {

    vector<Module_rule> tmp_module_rules = module_rules;//� �� �� ������ �� ��������� ������ �������
    int counter_rules = 0;
    while (!tmp_module_rules.empty() && flag_solve == 1) {

        //Module_rule curreny_module_rule;
        if (tmp_module_rules.front().mark == open) {
            //curreny_module_rule = module_rules.front();
            if (first_module_revealing_subgoal(tmp_module_rules.front()) == true) {

                tmp_module_rules.front().mark = close;//����� ������ 
                module_rules[counter_rules].mark = close;

                close_rules.push_back(tmp_module_rules.front().rule_num);
                if(check_close_node(tmp_module_rules.front().target_vertex) == false)//������� ���� ��� � ������ ����.
                    close_nodes.push_back(tmp_module_rules.front().target_vertex);
               
                if (tmp_module_rules.front().target_vertex == target_vert.vert_num) //�������� ������� - ����� �������
                    flag_solve = 0; 
            } 
          

        }
        for (int i = 0; i < close_nodes.size(); i++)
            close_nodes[i].flag = 1;
        tmp_module_rules.erase(tmp_module_rules.begin());
        counter_rules++;

    }

    cout << endl;
    if (flag_solve == 0) {
        //cout << "����� �������" << endl;
        return close_rules.size();
    }

    return close_rules.size();


}

bool Search_in_graph::find_provide_rule(Module_rule module_rule_) {
    int coincidences = 0;
    for (int i = 0; i < module_rule_.input_nodes.size(); i++)
    {
        for (int j = 0; j < close_nodes.size(); j++) {
            if (module_rule_.input_nodes[i].vert_num == close_nodes[j].vert_num)
                coincidences++;
        }
    }
    if (coincidences == module_rule_.input_nodes.size())
        return true; //������� ����� ��������� ����������
    return false;
}


bool Search_in_graph::check_close_node(int node_num) {
    for (int i = 0; i < close_nodes.size(); i++)
    {
        if (close_nodes[i].vert_num == node_num)
            return true;
    }
    return false;
}