
#include <iostream>
#include "zajimavosti.h"
#include "17_dedeni.h"

//
// PØÍKLAD 17.1: GRAFICKÉ OBJEKTY – SPOLEÈNÝ PØEDEK, PRVNÍ POKUS
//

graficky_objekt::~graficky_objekt()
{
    Tabs::printLine("~go()");

    smaz();

    Tabs::decTab();
}

graficky_objekt::graficky_objekt(int _barva)
{
    set_barva(_barva);

    Tabs::printLine("go(int _barva)");
    Tabs::addTab();
}

void graficky_objekt::set_barva(int _barva)
{
    this->barva = _barva;
}

int graficky_objekt::get_barva()
{
    return this->barva;
}

void graficky_objekt::nakresli()
{
    cout << Tabs::getTabChars() << "go::nakresli(): [" << this->barva << "]" << endl;
}

void graficky_objekt::smaz()
{
    cout << Tabs::getTabChars() << "go::mazání objektu: " << endl;;
    //nakresli();
}

//
// PØÍKLAD 17.4: OSTATNÍ METODY TØÍDY bod_potomek
//
void bod_potomek::nakresli()
{
    cout << Tabs::getTabChars() << "bod_potomek::nakresli(): ( " << x << ", " << y << " )" << endl;
    graficky_objekt::nakresli();
    // cout << Tabs::getTabChars() << "[" << get_barva() << "]" << endl;
}

void bod_potomek::smaz()
{
    cout << Tabs::getTabChars() << "bod_potomek::mazání objektu: " << endl;
    //nakresli();
}

//
// PØÍKLAD 17.3: KONSTRUKTOR A DESTRUKTOR TØÍDY bod_potomek
//
bod_potomek::bod_potomek(int _x, int _y, int _barva)
    :graficky_objekt(_barva)
{
    set_barva(_barva); // volá metodu pøedka
    set_x(_x);
    set_y(_y);

    Tabs::printLine("bod_potomek(int _x, int _y, int _barva)");
    Tabs::addTab();
}

bod_potomek::~bod_potomek()
{


    Tabs::printLine("~bod_potomek()");


    smaz(); // opakování volání je zde zámìr


    Tabs::decTab();
}

void bod_potomek::set_x(int _x)
{
    x = _x;
}
void bod_potomek::set_y(int _y)
{
    y = _y;
}


auto vypis_vytvoreni_grafickeho_objektu() -> void
{
     graficky_objekt g(8);
     g.nakresli();

     bod_potomek b{1, 9, 22};
     b.nakresli();
}


//
// PØÍKLAD 17.5: OØÍZNUTÍ OBJEKTU
//

auto vypis_oriznuti_objektu() -> void
{
    graficky_objekt g(241);
    bod_potomek b(201, 335, 123);

    // oøez instance - slicing
    g = b; // pøenese se pouze zdìdìný podobjekt

    g.nakresli();
}

//
// PØÍKLAD 17.6: PØIØAZOVÁNÍ UKAZATELÙ
//

auto vypis_prirazovani_ukazatelu() -> void
{

    graficky_objekt g(241);
    bod_potomek b(201, 335, 123);

    // ukazatel na go
    graficky_objekt *pgo = &g;

    // ukazatel na bod_potomek
    bod_potomek *pb_potomek = &b;

    // promìnné pøedstavující ukazatel na pøedka
    // lze pøiøadit hodnotu ukazatele na potomka
    pgo = pb_potomek;

    // pøiøazení potomka ukazatel na pøedka
    pb_potomek = (bod_potomek*)pgo;

    // pgo->nakresli(); // [123]
    pb_potomek->nakresli(); // (201, 335) [123]
}

//
// PØÍKLAD 17.7: JE TO BOD, ALE KRESLÍ SE OBECNÝ GRAFICKÝ OBJEKT
//

auto vypis_virtualni_metody() -> void
{
    graficky_objekt g(241);
    bod_potomek b(201, 335, 123);

    graficky_objekt *pg;
    pg = &b; // èasná vazba, early binding. - stále je to bod

    // potøebujeme, aby program za bìhu zjistil, jakého typu je instance,
    // na kterou tento ukazatel ukazuje a podle toho zavolal
    // odpovídající metodu
    pg->nakresli();

    // jinými slovy, potøebujeme, aby použil pozdní vazbu
    // tzv. late binding

    // Implementace pozdní vazby: virtuální metody
    // Metodu, pro kterou má pøekladaè použít pozdní vazbu, deklarujeme jako virtuální.




}





































