#pragma once
#include <vector>
#include"Node.h"

using namespace std;

enum mark_rules {not_chosen, chosen  };//метки соответственно 0(еще не выбиралось) и  1 

class Module_rule {
public:

    int rule_num;
    int target_vertex;//целевая(та что на выходе правила)
    vector<Node> input_nodes;
    int input_nodes_count;
    mark_rules mark = not_chosen;

    Module_rule(int rule_num_, int target_vertex_, vector<Node> input_nodes_, int input_nodes_count_) :rule_num(rule_num_), target_vertex(target_vertex_), input_nodes(input_nodes_), input_nodes_count(input_nodes_count_) {}
};