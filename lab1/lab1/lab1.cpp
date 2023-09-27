
#include <iostream>
#include"Search_in_graph.h"

int main()
{

    setlocale(LC_ALL, "Russian");
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node8(8); 
    Node node31(31);
    Node node4(4);
    Node node7(7);
    Node node9(9);
    Node node5(5); 
    Node node6(6);
    Node node18(18);
    Node node11(11); 
    Node node12(12);
    Node node13(13);
    Node node22(22);
    Node node23(23);
    Node node14(14);

    Module_rule module_rule101(101, 3, { node1, node2 }, 2);
    Module_rule module_rule103(103, 4, { node5, node6 }, 2);
    Module_rule module_rule114(114, 12, { node22, node23 }, 2);
    Module_rule module_rule102(102, 7, { node3, node2, node4 }, 3);
    Module_rule module_rule107(107, 11, { node12, node13 }, 2);
    Module_rule module_rule106(106, 9, { node11, node18, node4 }, 3);
    Module_rule module_rule105(105, 14, { node7, node9 }, 2);

    Search_in_graph search_in_graph({ module_rule101, module_rule102, module_rule103,
        module_rule105, module_rule106, module_rule107, module_rule114 }, node7, { node1, node2, node5, node6, node22,
        node23, node13,node18 }, 8);

    search_in_graph.search_width();

    std::cout << "Hello World!\n";
}

