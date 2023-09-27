#pragma once
#include"Edge.h"
#include"Module_rule.h"
#include<iostream>

class Search_in_graph {
    vector<Module_rule> module_rules;
    vector<int> open_rules;
    vector<int> close_rules;
    vector<Node> open_nodes;
    vector<Node> close_nodes;
    vector<int> forbidden_rules;
    vector<int> forbidden_nodes;
    bool flag_solve = 1;//���� �� ������
    bool flag_not_solve = 1; // ���� ��� �������
    Node target_vert; //�� ��� ����
    int count_nodes;//����� �������� ���� - �������� ������

    //������ � ������� ������ ����
 /*   vector<Edge> edges;
    int start_node;*/
    


public:
    Search_in_graph(vector<Module_rule> module_rules_, Node target_node_, vector<Node> initial_nodes_, int count_nodes_);
    void search_width();
    int create_close_rules();
    bool proved_rule(Module_rule module_rule_);

};