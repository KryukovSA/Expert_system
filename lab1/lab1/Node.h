#pragma once

class Node {
public:
    Node() {}
    int vert_num;
    int flag = 0; //������� �������� ���������, ����� 1 �� ��������
    Node(int vert_num_) :vert_num(vert_num_) {}
};