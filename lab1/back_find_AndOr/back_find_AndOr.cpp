// back_find_AndOr.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Search_in_graph.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node4(4);
    Node node5(5);
    Node node6(6);
    Node node7(7);
    Node node8(8);
    Node node9(9);
    Node node10(10);
    Node node11(11);
    Node node12(12);
    Node node13(13);
    Node node14(14);
    Node node15(15);
    Node node16(16);
    Node node17(17);
    Node node18(18);
    Node node19(19);
    Node node20(20);
    Node node21(21);




    Module_rule module_rule100(100, 1, { node2, node3 }, 2);
    Module_rule module_rule101(101, 2, { node4, node5, node6 }, 3);
    Module_rule module_rule102(102, 4, { node7, node8 }, 2);

    Module_rule module_rule103(103, 6, { node9, node10 }, 2);
    Module_rule module_rule104(104, 4, { node11, node12 }, 2);
    Module_rule module_rule105(105, 1, { node13, node14 }, 2);
    Module_rule module_rule106(106, 13, { node18, node19, node15 }, 3);
    Module_rule module_rule107(107, 19, { node20, node21 }, 2);


    Module_rule module_rule108(108, 18, { node16, node17 }, 2);



    Search_in_graph search_in_graph({ module_rule100 ,module_rule101 ,module_rule102 ,module_rule103 ,module_rule104 ,module_rule105, module_rule106, module_rule107, module_rule108 },
        node1,
        { node16, node17, node20, node21, node15, node14}, 8);
     
    //{node13, node14, node5,node9, node10,   node8,node11, node12}
    //node14,node3, node10,   node8,node11, node12
    search_in_graph.back_search();
}
