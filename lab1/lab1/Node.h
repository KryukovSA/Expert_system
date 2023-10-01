#pragma once

class Node {
public:
    Node() {}
    int vert_num;
    int flag = 0; //выбрана доказана запрещена, когда 1 то доказана
    Node(int vert_num_) :vert_num(vert_num_) {}
};