#include <iostream>
#include "04_pokrocilejsi_konstrukce_a_techniky.h"

using namespace std;

int Napis::pocet = 0;

Napis::Napis()
{
}

Napis::Napis(string txt)
{
    text(txt);
    pocet++;
}

Napis::~Napis()
{
    pocet--;
}

void Napis::vypis() const
{
    // cout << _text << endl;
    cout << this->_text << endl;
}

int Napis::pocet_napisu()
{
    return pocet;
}

void vypis_pocet_napisu()
{
    cout << "Po�et n�pis�: " << Napis::pocet_napisu() << endl;
    Napis napis("Nazdar, lidi");
    napis.vypis();
    cout << "Po�et n�pis�: " << Napis::pocet_napisu() << endl;
    Napis napis1("Nazdar, lidi");
    napis1.vypis();
    cout << "Po�et n�pis�:  " << Napis::pocet_napisu() << endl;

    // Napis p;
    // (*p).vypis();
}

void vypis_mnoho_verzi_teze_tridy()
{
    // inicializace t��dy Dvojice
    Dvojice<int, int> obj1{1,1};
    // z�sk�n� prvk�
    cout << "Prvni: " << obj1.get_prvni() << endl;
    cout << "Druha: " << obj1.get_druha() << endl;
    cout << " Cislo instance tridy nalezici k sablone dle pouziteho typu: " << obj1.get_pocet_instanci() << endl;

    // inicializace t��dy Dvojice
    Dvojice<string, int> obj2{"String", 1};
    // z�sk�n� prvk�
    cout << "Prvni: " << obj2.get_prvni() << endl;
    cout << "Druha: " << obj2.get_druha() << endl;
    cout << " Cislo instance tridy nalezici k sablone dle pouziteho typu: " << obj2.get_pocet_instanci() << endl;

    // inicializace t��dy Dvojice
    Dvojice<string, int> obj3{"String", 1};
    // z�sk�n� prvk�
    cout << "Prvni: " << obj3.get_prvni() << endl;
    cout << "Druha: " << obj3.get_druha() << endl;
    cout << " Cislo instance tridy nalezici k sablone dle pouziteho typu: " << obj3.get_pocet_instanci() << endl;

    // inicializace t��dy Dvojice
    Dvojice<string, int> obj4{"String", 1};
    // z�sk�n� prvk�
    cout << "Prvni: " << obj4.get_prvni() << endl;
    cout << "Druha: " << obj4.get_druha() << endl;
    cout << " Cislo instance tridy nalezici k sablone dle pouziteho typu: " << obj4.get_pocet_instanci() << endl;

    // inicializace t��dy Dvojice
    Dvojice<string, string> obj5{"String", "String"};
    // z�sk�n� prvk�
    cout << "Prvni: " << obj5.get_prvni() << endl;
    cout << "Druha: " << obj5.get_druha() << endl;
    cout << " Cislo instance tridy nalezici k sablone dle pouziteho typu: " << obj5.get_pocet_instanci() << endl;

    // inicializace t��dy Dvojice
    Dvojice<string, string> obj6{"String", "String"};
    // z�sk�n� prvk�
    cout << "Prvni: " << obj6.get_prvni() << endl;
    cout << "Druha: " << obj6.get_druha() << endl;
    cout << " Cislo instance tridy nalezici k sablone dle pouziteho typu: " << obj6.get_pocet_instanci() << endl;
}

//Jin� mo�n� implementace
//Vra�me se k p�vodn� podob� t��dy vektor. M�sto abychom z n� odstra�ovali metodu plus()
//a nahrazovali ji oper�torem s��t�n�, deklarujeme oper�tor + jako oby�ejnou funkci se dv�ma
//parametry, je� vyu�ije slu�eb t�to metody. To znamen�, �e metodu plus() ponech�me a do
//hlavi�kov�ho souboru p�id�me za deklaraci t��dy vektor je�t� prototyp:

// jako oby�ejnou funkci
/*
vektor operator+(vektor u, vektor w)
{
    return u.plus(w);
}
*/

////
//// P��KLAD 16.1: OPER�TOR JAKO SP��TELEN� FUNKCE
////
//vektor operator+(vektor u, vektor w)
//{
//    double vysledek[dim];
//    for(int i = 0; i < dim; i++)
//    {
//        vysledek[i] = u.pole[i] + w.pole[i];
//    }
//    return vysledek;
//}


//vektor vektor::plus(vektor w)
//{
//    double vysledek[dim];
//    for(int i = 0; i < dim; i++)
//    {
//        vysledek[i] = pole[i] + w.pole[i];
//    }
//    return vysledek;
//}

vektor vektor::operator+(vektor w)
{
   double vysledek[dim];
   for(int i = 0; i < dim; i++)
   {
      vysledek[i] = pole[i] - w.pole[i];
   }
   return vektor(vysledek);
}

vektor vektor::operator-(vektor w)
{
    double vysledek[dim];
    for(int i = 0; i < dim; i++)
    {
        vysledek[i] = pole[i] - w.pole[i];
    }
    return vektor(vysledek);
}

vektor vektor::operator*(vektor w)
{
    double vysledek[dim];
    for(int i = 0; i < dim; i++)
    {
        vysledek[i] = pole[i] * w.pole[i];
    }
    return vektor(vysledek);
}

vektor::vektor(double _pole[])
{
    for(int i = 0; i < dim; i++)
    {
        pole[i]= _pole[i];
    }
}

vektor::vektor(double x, double y, double z)
{
    pole[0] = x;
    pole[1] = y;
    pole[2] = z;
}


void vypis_vektor()
{
    cout << "Hello world!" << endl;

    vektor v1; // tot� co vektor v1{0, 0, 0};
    cout << v1.get_1() << endl;

    vektor v2{1}; // tot� co vektor v1{1, 0, 0};
    cout << v2.get_1() << endl;
    vektor v3{1, 3}; // tot� co vektor v1{1, 3, 0};
    cout << v3.get_1() << endl;

    vektor u{1,2,3}, v{3,2,1}, w;

    cout << u.get_1() << endl;

    // w = v.plus(u);
    // cout << w.get_1() << endl;

    v = u + w;
    v = u - w;
    v = u * w;

    // vektor f(v);
}

