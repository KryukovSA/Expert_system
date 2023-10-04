#pragma once

enum mark_edge { forbid, passed, not_passed };//изначально 0, если вкл в дерево то 1 (passed)
class Edge {
public:
    int start_node;
    int end_node;
    mark_edge mark = not_passed;
    Edge(int start_node_, int end_node_) :start_node(start_node_), end_node(end_node_) {}
};
