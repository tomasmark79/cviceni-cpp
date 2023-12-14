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
    cout << "Poèet nápisù: " << Napis::pocet_napisu() << endl;
    Napis napis("Nazdar, lidi");
    napis.vypis();
    cout << "Poèet nápisù: " << Napis::pocet_napisu() << endl;
    Napis napis1("Nazdar, lidi");
    napis1.vypis();
    cout << "Poèet nápisù:  " << Napis::pocet_napisu() << endl;

    // Napis p;
    // (*p).vypis();
}

void vypis_mnoho_verzi_teze_tridy()
{
    // inicializace tøídy Dvojice
    Dvojice<int, int> obj1{1,1};
    // získání prvkù
    cout << "Prvni: " << obj1.get_prvni() << endl;
    cout << "Druha: " << obj1.get_druha() << endl;
    cout << " Cislo instance tridy nalezici k sablone dle pouziteho typu: " << obj1.get_pocet_instanci() << endl;

    // inicializace tøídy Dvojice
    Dvojice<string, int> obj2{"String", 1};
    // získání prvkù
    cout << "Prvni: " << obj2.get_prvni() << endl;
    cout << "Druha: " << obj2.get_druha() << endl;
    cout << " Cislo instance tridy nalezici k sablone dle pouziteho typu: " << obj2.get_pocet_instanci() << endl;

    // inicializace tøídy Dvojice
    Dvojice<string, int> obj3{"String", 1};
    // získání prvkù
    cout << "Prvni: " << obj3.get_prvni() << endl;
    cout << "Druha: " << obj3.get_druha() << endl;
    cout << " Cislo instance tridy nalezici k sablone dle pouziteho typu: " << obj3.get_pocet_instanci() << endl;

    // inicializace tøídy Dvojice
    Dvojice<string, int> obj4{"String", 1};
    // získání prvkù
    cout << "Prvni: " << obj4.get_prvni() << endl;
    cout << "Druha: " << obj4.get_druha() << endl;
    cout << " Cislo instance tridy nalezici k sablone dle pouziteho typu: " << obj4.get_pocet_instanci() << endl;

    // inicializace tøídy Dvojice
    Dvojice<string, string> obj5{"String", "String"};
    // získání prvkù
    cout << "Prvni: " << obj5.get_prvni() << endl;
    cout << "Druha: " << obj5.get_druha() << endl;
    cout << " Cislo instance tridy nalezici k sablone dle pouziteho typu: " << obj5.get_pocet_instanci() << endl;

    // inicializace tøídy Dvojice
    Dvojice<string, string> obj6{"String", "String"};
    // získání prvkù
    cout << "Prvni: " << obj6.get_prvni() << endl;
    cout << "Druha: " << obj6.get_druha() << endl;
    cout << " Cislo instance tridy nalezici k sablone dle pouziteho typu: " << obj6.get_pocet_instanci() << endl;
}

//Jiná možná implementace
//Vrame se k pùvodní podobì tøídy vektor. Místo abychom z ní odstraòovali metodu plus()
//a nahrazovali ji operátorem sèítání, deklarujeme operátor + jako obyèejnou funkci se dvìma
//parametry, jež využije služeb této metody. To znamená, že metodu plus() ponecháme a do
//hlavièkového souboru pøidáme za deklaraci tøídy vektor ještì prototyp:

// jako obyèejnou funkci
/*
vektor operator+(vektor u, vektor w)
{
    return u.plus(w);
}
*/

////
//// PØÍKLAD 16.1: OPERÁTOR JAKO SPØÁTELENÁ FUNKCE
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

    vektor v1; // totéž co vektor v1{0, 0, 0};
    cout << v1.get_1() << endl;

    vektor v2{1}; // totéž co vektor v1{1, 0, 0};
    cout << v2.get_1() << endl;
    vektor v3{1, 3}; // totéž co vektor v1{1, 3, 0};
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

