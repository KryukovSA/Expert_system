#pragma once

#include"Module_rule.h"
#include<iostream>
#include <stack>

//в ширину от данных к цели
class Search_in_graph {
    vector<Module_rule> module_rules;

    vector<int> open_rules;//
    vector<int> close_rules;//

    stack<Node> open_nodes;
    vector<Node> close_nodes;

    vector<int> forbidden_rules;
    vector<int> forbidden_nodes;//

    bool flag_solve = 1;//пока не решили
    bool flag_not_solve = 1; // флаг нет решения
    int flag_poisk;


    Node target_vert; //ту что ищем
    int count_nodes;//число заданных верш - исходные данные

    //только в простом поиске было
 /*   vector<Edge> edges;
    int start_node;*/



public:
    Search_in_graph(vector<Module_rule> module_rules_, Node target_node_, vector<Node> initial_nodes_, int count_nodes_);
    int find_child();
    void back_search();
    bool contain_in_forbiden_rule(Module_rule module_rule);
    bool contain_in_close_nodes(Node node);
    Node get_node(int num);
    void razmetka(Module_rule module_rule); 
    Module_rule get_rule(int num_rule);
    bool find_provide_rule(Module_rule module_rule_);
    bool check_close_node(int node_num);
    void backtraking();
    void  show_close_rules();
    void  show_close_nodes();

    int create_close_rules();
    
   

};