#pragma once


class Node {
public:
    Node() {}
    int vert_num;
    int flag = 0; //когда 0 то еще не добавляли в очередь, когда 1 то добавляли
    Node(int vert_num_) :vert_num(vert_num_) {}
};