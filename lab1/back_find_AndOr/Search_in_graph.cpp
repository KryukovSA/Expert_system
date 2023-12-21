#include "Search_in_graph.h"
#include <algorithm>

Search_in_graph::Search_in_graph(vector<Module_rule> module_rules_, Node target_node_, vector<Node> initial_nodes_, int count_nodes_) {
    this->module_rules = module_rules_;
    this->close_nodes = initial_nodes_; 
    for (int i = 0; i < close_nodes.size(); i++)
        close_nodes[i].flag = 1;
    target_vert = target_node_;
    count_nodes = count_nodes_;
    
    open_nodes.push(target_vert);// � ���� ������� ������
}


Node Search_in_graph::get_node(int num) {
    for (int i = 0; i < module_rules.size(); i++)
        for (int j = 0; j < module_rules[i].input_nodes.size(); j++)
            if (module_rules[i].input_nodes[j].vert_num == num) 
                { return module_rules[i].input_nodes[j]; }
    for (int i = 0; i < module_rules.size(); i++) {//���� ��� �� ��� �������� ����
        if (module_rules[i].target_vertex == num) {
            Node node(num);
            return node;
        }
    }
}



//����������� �������� ������� �������
int Search_in_graph::find_child() {
    int counter_rules = 0;//������� ������� ������������ ������� �������
    int i = 0;
    while (!module_rules.empty() && counter_rules == 0 && i < module_rules.size()) {//flag_solve == 1
        //cout << "���� ��������" << endl;
        if (module_rules[i].target_vertex == open_nodes.top().vert_num &&
            module_rules[i].mark == not_chosen && 
            !contain_in_forbiden_rule(module_rules[i])) {
            counter_rules++;
            if (open_rules.empty())
                open_rules.push_back(module_rules[i].rule_num);//� ������ �������� ������ ���
            if(open_rules.back() != module_rules[i].rule_num)
                open_rules.push_back(module_rules[i].rule_num);//� ������ �������� ������ ���
            int count_vert_in_close = 0;
            for (int m = 0; m < module_rules[i].input_nodes.size(); m++) { //�� ������� ���� ������� ���� 
                
                if (!contain_in_close_nodes(module_rules[i].input_nodes[m])) { //������� ��� � ������ ��������(����� ���� �� ����� ��)
                    open_nodes.push(module_rules[i].input_nodes[m]);
                }
                else {
                    count_vert_in_close++;
                }
                if (count_vert_in_close == module_rules[i].input_nodes.size()) {//����� ������� ������ ��� �� ���� � ������� � ����
                    cout << "����� ����� ���������� �������: " << module_rules[i].rule_num << endl;
                    count_vert_in_close = 0;
                    razmetka(module_rules[i]);
                    
                }
            }


        }

        i++;
    }
    return counter_rules;
}

//�������� ������
void Search_in_graph::razmetka(Module_rule module_rule) {
    int flag = 1;
    while (flag) {
        cout << "���� ��������" << endl;
        if (module_rule.target_vertex == target_vert.vert_num) {//������� ������� ������
            flag = 0;
            flag_solve = 0;//���������� �� �������� ��� ������� �����
            module_rule.mark = chosen;
            close_nodes.push_back(get_node(module_rule.target_vertex));
            for (int i = 0; i < close_nodes.size(); i++)
                close_nodes[i].flag = 1;//����������� ������� ���� � 1(��������)
            close_rules.push_back(module_rule.rule_num);
            auto it = find(open_rules.begin(), open_rules.end(), module_rule.rule_num);
            if (it != open_rules.end())
                open_rules.erase(it);//���� ������� �� ���� ������
            open_nodes.pop();//���� ���� �� ���� ������

            show_close_rules();
            show_close_nodes();
        }
        else {

            module_rule.mark = chosen;
            close_nodes.push_back(get_node(module_rule.target_vertex));
            for (int i = 0; i < close_nodes.size(); i++)
                close_nodes[i].flag = 1;//����������� ������� ���� � 1(��������)
            close_rules.push_back(module_rule.rule_num);
            auto it = find(open_rules.begin(), open_rules.end(), module_rule.rule_num);
            if (it != open_rules.end())
                open_rules.erase(it);//���� ������� �� ���� ������
            open_nodes.pop();//���� ���� �� ���� ������

            show_close_rules();
            show_close_nodes();

            cout << endl;
                if (open_rules.empty()) {
                    flag = 0;
                    break;
                }
                Module_rule cur_rule = get_rule(open_rules.back());
                for (int j = 0; j < cur_rule.input_nodes.size(); j++) {
                    if (module_rule.target_vertex == cur_rule.input_nodes[j].vert_num) { // �������� ����� �� ������� �������
                        cur_rule.input_nodes[j].flag = 1;
                        for (int k = 0; k < cur_rule.input_nodes.size(); k++) {//����������� ��� ��� ��������� ������� �������� ������ ������� �������
                            if (cur_rule.input_nodes[k].flag != 1) {
                                flag = 0;
                                break;
                            }
                        }

                    }

                //} 
                }
                module_rule = cur_rule;//???????????
               
           // }
        }
    }

}

Module_rule Search_in_graph::get_rule(int num_rule) {
    for (int i = 0; i < module_rules.size(); i++) {
        if (module_rules[i].rule_num == num_rule)
            return module_rules[i];
    }
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

bool Search_in_graph::contain_in_forbiden_rule(Module_rule module_rule) {
    for (const int& rule_num : forbidden_rules) {
        if (rule_num == module_rule.rule_num)
            return true;
    }
    return false;
}

bool Search_in_graph::contain_in_close_nodes(Node node) {
    for (const Node& nodes : close_nodes) {
        if (nodes.vert_num == node.vert_num)
            return true;
    }
    return false;
}





//�������� ����� ������
void Search_in_graph::back_search() {
    int iteration = 0;
    int old_count_close_rul = 0;
    int k = 0;
    while (flag_solve && flag_not_solve) {
        //cout << "���� �������� ���� ������" << endl;
        
        k = find_child();//����� ��������

        if (flag_solve == 0) {
            cout << "������� �������" << endl;//����� ������ ���� ������
            return;
        }

        
        if (k == 0 && (open_nodes.empty() || open_nodes.top().vert_num == target_vert.vert_num)) {
            flag_not_solve = 0;
            cout << "��� �������" << endl;
        }
        if (k == 0 && !open_nodes.empty() && open_nodes.top().vert_num != target_vert.vert_num) // !=????
        {
            //����� ��������(����������)
            backtraking();

        }

        iteration++;

    }

}

void Search_in_graph::backtraking() {
    forbidden_rules.push_back( open_rules.back());
    Module_rule curr_rule = get_rule(open_rules.back());
    int flag = 1;
    for (int m = 0; m < curr_rule.input_nodes.size(); m++) {
        if (flag == 0)
            break;

        if (open_nodes.top().vert_num == curr_rule.input_nodes[m].vert_num) {//��� ����� ������� ���������� � ����
            forbidden_nodes.push_back(curr_rule.input_nodes[m].vert_num);
            //open_nodes.pop();
        }
        for (int n = 0; n < curr_rule.input_nodes.size(); n++)
            if(!forbidden_nodes.empty())
            if (forbidden_nodes.back() == curr_rule.input_nodes[n].vert_num) {
                flag = 0;
                break;
            }
    }
        while (open_nodes.top().vert_num != curr_rule.target_vertex) {
            open_nodes.pop();
        }

    
    open_rules.pop_back();
    
    cout << "���������� ���������� ������ ����������� ������" << endl;
    for (int i = 0; i < forbidden_nodes.size(); i++) {
        cout << forbidden_nodes[i] << " ";
    }
   
    cout<< endl << "������ ����������� ������" << endl;
    for (int i = 0; i < forbidden_rules.size(); i++)
    {
        cout << forbidden_rules[i] << " ";
    }
    

    cout << endl;
}


bool Search_in_graph::check_close_node(int node_num) {
    for (int i = 0; i < close_nodes.size(); i++)
    {
        if (close_nodes[i].vert_num == node_num)
            return true;
    }
    return false;
}

void  Search_in_graph::show_close_rules() {
    cout << "������ �������� ������" << endl;
    for (int i = 0; i < close_rules.size(); i++)
    {
        cout << close_rules[i] << " ";
    }
    cout << endl;
}


void  Search_in_graph::show_close_nodes() {
    cout << "������ �������� ������" << endl;
    for (int i = 0; i < close_nodes.size(); i++)
    {
        cout << close_nodes[i].vert_num << " ";
    }
    cout << endl;
}