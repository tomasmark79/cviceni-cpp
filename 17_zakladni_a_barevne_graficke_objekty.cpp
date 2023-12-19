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
        proved_kresleni(); // virtu�lka
    }
}

void graficky_objekt::smaz()
{
    if (get_nakresleno())
    {
        cout << "smaz�n ";
        proved_mazani(); // virtu�lka
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

// p�ij�m� referenci na objekt typu obrazek
// a je to vlastn� kop�rovac� konstruktor
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

// p�ij�m� referenci na objekt typu graficky_objekt
// ale, m��e p�ijmout i potomka
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
    obrazek obr1(obr); // vol� "kop�rovac� konstruktor"

}

// dynamicky
auto zakladni_a_barevne_graficke_objekty_dynamicky() -> void
{
    bod A(5, 8, 9);
    usecka us(1, 2, 3, 4, 990);

    // info: Jazyk C++ nedovoluje deklarovat instanci abstraktn� t��dy.
    // graficky_objekt *pgo = new graficky_objekt();

    graficky_objekt *pgo = new obrazek();
    // Tento ��dek vytv��� nov� objekt typu obrazek pomoc� oper�toru new
    // a nastavuje ukazatel pgo na tento nov� vytvo�en� objekt.
    // P�itom je ukazatel deklarov�n s typem graficky_objekt,
    // co� nazna�uje, �e obrazek je odvozen od graficky_objekt.

    // pgo->pridej(A); // error: 'class graficky_objekt' has no member named 'pridej'|

    // Zavol�n� metody pridej ve t��d� obrazek s ukazatelen ba instanci objektu.
    ((obrazek*)pgo)->pridej(A);
    ((obrazek*)pgo)->pridej(us);
    // Vytvo�en� ukazatele na obrazek:
    // (obrazek*) ��k� kompil�toru, aby interpretoval blok pam�ti,
    // kter� je p�vodn� interpretov�n jako graficky_objekt* (typ, na kter� ukazuje pgo), jako obrazek*.
    // To znamen�, �e vytv��� nov� ukazatel, kter� bude ukazovat na stejnou adresu v pam�ti,
    // ale bude interpretov�n jako ukazatel na obrazek.

    A.set_x(6666); // toto se nevykresl�

    pgo->nakresli();

    pgo->smaz();
    cout << endl;;

    // /*
    bod AA(123, 456, 789);
	bod BB(321, 654, 987);
	graficky_objekt *zachraneny_go = pgo; // jen z plez�ru
        zachraneny_go->nakresli();
	pgo = new usecka(AA, BB, 565); // T�m dojde ke "ztr�t�" reference na objekt typu obrazek, kter� byl vytvo�en na prvn�m ��dku.
	pgo->nakresli();
    // */


	delete pgo;
}
