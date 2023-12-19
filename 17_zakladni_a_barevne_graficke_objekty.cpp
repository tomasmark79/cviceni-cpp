#include <iostream>
#include "17_zakladni_a_barevne_graficke_objekty.h"
using namespace std;

void barva::pouzij()
{
    cout << "[" << rgb << "]";
}

void graficky_objekt::nakresli()
{
    if (!nakresleno)
    {
        nakresleno = true;
        proved_kresleni(); // virtuálka
    }
}

void graficky_objekt::smaz()
{
    if (get_nakresleno())
    {
        cout << "smazán ";
        proved_mazani(); // virtuálka
        set_nakresleno(false);
    }
}

zakladni_bod::zakladni_bod(int _x, int _y)
{
    set_x(_x);
    set_y(_y);
}

void zakladni_bod::proved_kresleni()
{
    cout << "(" << x << ", " << y << ")";
}

zakladni_usecka::zakladni_usecka(zakladni_bod _pocatek, zakladni_bod _konec)
    : pocatek(_pocatek), konec(_konec)
{ }

zakladni_usecka::zakladni_usecka(int x1, int y1, int x2, int y2)
    : pocatek(x1, y1), konec(x2, y2)
{ }

void zakladni_usecka::proved_kresleni()
{
    cout << "<";
    pocatek.proved_kresleni();
    cout << "; ";
    konec.proved_kresleni();
    cout << ">";
}

bod::bod(int _x, int _y, barva _barva)
    : zakladni_bod(_x, _y), barva_bodu(_barva)
{ }

void bod::proved_kresleni()
{
    zakladni_bod::proved_kresleni();
    barva_bodu.pouzij();
}

usecka::usecka(int x1, int y1, int x2, int y2, barva _barva)
    : zakladni_usecka(x1, y1, x2, y2), barva_usecky(_barva)
{ }

usecka::usecka(zakladni_bod _pocatek, zakladni_bod _konec, barva _barva)
    : zakladni_usecka(_pocatek, _konec), barva_usecky(_barva)
{ }

void usecka::proved_kresleni()
{
    zakladni_usecka::proved_kresleni();
    barva_usecky.pouzij();
}

obrazek::obrazek()
{

}

// pøijímá referenci na objekt typu obrazek
// a je to vlastnì kopírovací konstruktor
obrazek::obrazek(obrazek& obr)
{
    for(auto p: obr.kresba)
    {
        kresba.push_back(p->klon());
    }
}

obrazek::~obrazek()
{
    for (auto p : kresba)
    {
        delete p;
    }
}

void obrazek::proved_kresleni()
{
    for (auto go : kresba)
    {
        go->proved_kresleni();
    }
}

void obrazek::proved_mazani()
{
    for (auto p : kresba)
    {
        p->proved_mazani();
    }
}

// pøijímá referenci na objekt typu graficky_objekt
// ale, mùže pøijmout i potomka
void obrazek::pridej(graficky_objekt& go)
{
    kresba.push_back(go.klon());
}

// staticky
auto zakladni_a_barevne_graficke_objekty_staticky() -> void
{
    zakladni_bod zb(1,2);
    bod A(5, 8, 9);
    usecka us(1, 2, 3, 4, 990);
    obrazek obr;
    obr.pridej(us);
    obr.pridej(A);
    obr.pridej(zb);

    obr.nakresli();
    obrazek obr1(obr); // volá "kopírovací konstruktor"

}

// dynamicky
auto zakladni_a_barevne_graficke_objekty_dynamicky() -> void
{
    bod A(5, 8, 9);
    usecka us(1, 2, 3, 4, 990);

    // info: Jazyk C++ nedovoluje deklarovat instanci abstraktní tøídy.
    // graficky_objekt *pgo = new graficky_objekt();

    graficky_objekt *pgo = new obrazek();
    // Tento øádek vytváøí nový objekt typu obrazek pomocí operátoru new
    // a nastavuje ukazatel pgo na tento novì vytvoøený objekt.
    // Pøitom je ukazatel deklarován s typem graficky_objekt,
    // což naznaèuje, že obrazek je odvozen od graficky_objekt.

    // pgo->pridej(A); // error: 'class graficky_objekt' has no member named 'pridej'|

    // Zavolání metody pridej ve tøídì obrazek s ukazatelen ba instanci objektu.
    ((obrazek*)pgo)->pridej(A);
    ((obrazek*)pgo)->pridej(us);
    // Vytvoøení ukazatele na obrazek:
    // (obrazek*) øíká kompilátoru, aby interpretoval blok pamìti,
    // který je pùvodnì interpretován jako graficky_objekt* (typ, na který ukazuje pgo), jako obrazek*.
    // To znamená, že vytváøí nový ukazatel, který bude ukazovat na stejnou adresu v pamìti,
    // ale bude interpretován jako ukazatel na obrazek.

    A.set_x(6666); // toto se nevykreslí

    pgo->nakresli();

    pgo->smaz();
    cout << endl;;

    // /*
    bod AA(123, 456, 789);
	bod BB(321, 654, 987);
	graficky_objekt *zachraneny_go = pgo; // jen z plezíru
        zachraneny_go->nakresli();
	pgo = new usecka(AA, BB, 565); // Tím dojde ke "ztrátì" reference na objekt typu obrazek, který byl vytvoøen na prvním øádku.
	pgo->nakresli();
    // */


	delete pgo;
}
