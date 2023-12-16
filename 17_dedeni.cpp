
#include <iostream>
#include "zajimavosti.h"
#include "17_dedeni.h"

//
// P��KLAD 17.1: GRAFICK� OBJEKTY � SPOLE�N� P�EDEK, PRVN� POKUS
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
    cout << Tabs::getTabChars() << "go::maz�n� objektu: " << endl;;
    //nakresli();
}

//
// P��KLAD 17.4: OSTATN� METODY T��DY bod_potomek
//
void bod_potomek::nakresli()
{
    cout << Tabs::getTabChars() << "bod_potomek::nakresli(): ( " << x << ", " << y << " )" << endl;
    graficky_objekt::nakresli();
    // cout << Tabs::getTabChars() << "[" << get_barva() << "]" << endl;
}

void bod_potomek::smaz()
{
    cout << Tabs::getTabChars() << "bod_potomek::maz�n� objektu: " << endl;
    //nakresli();
}

//
// P��KLAD 17.3: KONSTRUKTOR A DESTRUKTOR T��DY bod_potomek
//
bod_potomek::bod_potomek(int _x, int _y, int _barva)
    :graficky_objekt(_barva)
{
    set_barva(_barva); // vol� metodu p�edka
    set_x(_x);
    set_y(_y);

    Tabs::printLine("bod_potomek(int _x, int _y, int _barva)");
    Tabs::addTab();
}

bod_potomek::~bod_potomek()
{


    Tabs::printLine("~bod_potomek()");


    smaz(); // opakov�n� vol�n� je zde z�m�r


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
// P��KLAD 17.5: O��ZNUT� OBJEKTU
//

auto vypis_oriznuti_objektu() -> void
{
    graficky_objekt g(241);
    bod_potomek b(201, 335, 123);

    // o�ez instance - slicing
    g = b; // p�enese se pouze zd�d�n� podobjekt

    g.nakresli();
}

//
// P��KLAD 17.6: P�I�AZOV�N� UKAZATEL�
//

auto vypis_prirazovani_ukazatelu() -> void
{

    graficky_objekt g(241);
    bod_potomek b(201, 335, 123);

    // ukazatel na go
    graficky_objekt *pgo = &g;

    // ukazatel na bod_potomek
    bod_potomek *pb_potomek = &b;

    // prom�nn� p�edstavuj�c� ukazatel na p�edka
    // lze p�i�adit hodnotu ukazatele na potomka
    pgo = pb_potomek;

    // p�i�azen� potomka ukazatel na p�edka
    pb_potomek = (bod_potomek*)pgo;

    // pgo->nakresli(); // [123]
    pb_potomek->nakresli(); // (201, 335) [123]
}

//
// P��KLAD 17.7: JE TO BOD, ALE KRESL� SE OBECN� GRAFICK� OBJEKT
//

auto vypis_virtualni_metody() -> void
{
    graficky_objekt g(241);
    bod_potomek b(201, 335, 123);

    graficky_objekt *pg;
    pg = &b; // �asn� vazba, early binding. - st�le je to bod

    // pot�ebujeme, aby program za b�hu zjistil, jak�ho typu je instance,
    // na kterou tento ukazatel ukazuje a podle toho zavolal
    // odpov�daj�c� metodu
    pg->nakresli();

    // jin�mi slovy, pot�ebujeme, aby pou�il pozdn� vazbu
    // tzv. late binding

    // Implementace pozdn� vazby: virtu�ln� metody
    // Metodu, pro kterou m� p�eklada� pou��t pozdn� vazbu, deklarujeme jako virtu�ln�.




}





































