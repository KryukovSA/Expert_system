
#include <iostream>
#include"Search_in_graph.h"

int main()
{

    setlocale(LC_ALL, "Russian");
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node7(7);
    Node node20(20);
    Node node33(33);
    Node node15(15);
    Node node8(8); 
    Node node31(31);
    Node node4(4);
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
    Node node19(19);
    Node node21(21);
    Node node34(34);




    Module_rule module_rule101(101, 3, { node1, node2 }, 2);
    Module_rule module_rule103(103, 4, { node5, node6 }, 2);
    Module_rule module_rule104(104, 3, { node8, node31 }, 2);

    Module_rule module_rule111(111, 9, { node11, node18 }, 2);
    Module_rule module_rule108(108, 33, { node21, node15 }, 2);
    Module_rule module_rule113(113, 18, { node12, node20 }, 2);
    Module_rule module_rule109(109, 19, { node13, node20, node34 }, 3);
    Module_rule module_rule115(115, 21, { node19, node34 }, 2);


    Module_rule module_rule114(114, 12, { node22, node23 }, 2);
    Module_rule module_rule102(102, 7, { node3, node2, node4 }, 3);
    Module_rule module_rule107(107, 11, { node13, node12 }, 3);
    Module_rule module_rule106(106, 9, { node11, node18, node4 }, 3);
    Module_rule module_rule105(105, 14, { node7, node9 }, 2);
    Module_rule module_rule112(112, 21, { node18, node19 }, 2);
    Module_rule module_rule110(110, 14, {node9, node21}, 2);


    Search_in_graph search_in_graph({ module_rule101, module_rule102, module_rule103,
        module_rule104, module_rule105, module_rule106, module_rule107, module_rule108, module_rule109,
        module_rule111, module_rule113, module_rule114, module_rule112, module_rule110, module_rule115 },
        node14, 
        {  node8, node31, node1, node2, node4, node18, node11}, 8); 

    search_in_graph.search_width();


}

