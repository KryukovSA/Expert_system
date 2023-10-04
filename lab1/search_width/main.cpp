#include <iostream>
#include "search_widtn.h"



int main() {
    setlocale(LC_ALL, "Russian");

    Node node0(0);
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node4(4);
    Node node5(5);
    Node node6(6);
    Node node7(7);
    Node node8(8);
    Node node9(9);

    Edge edge01(0, 1);
    Edge edge02(0, 2);
    Edge edge03(0, 3);
    Edge edge14(1, 4);
    Edge edge24(2, 4);
    Edge edge25(2, 5);
    Edge edge35(3, 5);
    Edge edge36(3, 6);
    Edge edge67(6, 7);

    Edge edge54(5, 4);
    Edge edge57(5, 7);
    Edge edge48(4, 8);
    Edge edge59(5, 9);
    Edge edge98(9, 8);
    Edge edge79(7, 9);

    search_width search({ edge01, edge02 ,edge03 ,edge14 ,edge24 ,edge25 ,edge35 ,edge36, edge67 ,edge54 ,edge57 ,edge48 ,edge59 ,edge98, edge79 },
        node0, node8, { node1, node2, node3, node4, node5, node6, node7, node8,node9 });
    search.organization_search();

    return 0;
}
