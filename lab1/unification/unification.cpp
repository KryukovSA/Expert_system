
#include "search.h"
#include <iostream>

int main()
{
    
    setlocale(LC_ALL, "Russian");
    Variable x("x");
    Variable y("Y");
    Variable z("z");
    Variable x1("x1");
    Variable x2("x2");
    Variable x3("x3");
    Variable x4("x4");

    Variable N("N");
    N.is_const = true;
    Variable W("W");
    W.is_const = true;
    Variable A1("A1");
    A1.is_const = true;
    Variable M1("M1");
    M1.is_const = true;


    //Atom A("A", { x }, 1);
    //Atom W("W", { y }, 1);
    //Atom S("S", { x,y,z }, 3);
    //Atom H("H", { z }, 1);
    //Atom С("С", { x }, 1);
    //Atom O("O", { N, x1 }, 2);
    //Atom M("M", { x1 }, 1);
    //Atom S_("S_", { W, x1, N }, 3);//иначе как ее отобразить 
    //Atom M_("M_", { x2 }, 1);
    //Atom W_("W_", { x2 }, 1);
    //Atom E("E", { x3, A1 }, 2);
    //Atom H("H_", { x3 }, 1);
    ////атомы факты
    Atom O("O", { N, M1 }, 2);
    Atom A("A", { W }, 1);
    Atom E("E", { N, A1 }, 2);
    Atom M("M", { M1 }, 1);

    Implication_rule rule1(Atom{ "C", {x}, 1 },
        { Atom("A", { x }, 1),
            Atom("W", { y }, 1),
        Atom("S", { x, y, z }, 3),
          Atom("H", { z }, 1) },
        1
    );
    Implication_rule rule2(Atom{ "S", {W, x1, N}, 3 },
        { Atom("M", { x1 }, 1),
            Atom("O", { N, x1 }, 2) },
        2
    );
    Implication_rule rule3(Atom{ "W", {x2}, 1 },
        { Atom("M", { x2 }, 1) },
        3
    );
    Implication_rule rule4(Atom{ "H", {x3}, 1 },
        { Atom("E", { x3, A1 }, 2) },
        4
    );



    Atom target{ "C", { W }, 1};
    Search search(target, {O, A, E, M}, { x,y,z,x1,x2,x3,N,W,A1,M1 }, {rule1, rule2, rule3, rule4});
    search.back_search();






}

