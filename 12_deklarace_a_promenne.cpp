#include <iostream>
#include "12_deklarace_a_promenne.h"

using namespace std;

/*
Celkovì lze tyto deklarace interpretovat jako vytvoøení struktur dat,
které mohou být použity pro práci s maticemi nebo jinými vícedimenzionálními daty.
Každý z tìchto zpùsobù deklarace ukazuje na odlišný zpùsob práce s pamìtí a pøístupu k prvkùm.
*/

void vypis_pole_ukazatelu()
{
    //
    const int n{8}, eol{8};
    int *pole_ukazatelu = new int[n] {0xA0,0xA1,0xA2};

    /*
    Jedná se o deklaraci ukazatele na pole int (int).
    Symbol D je ukazatel, který ukazuje na pole o velikosti n.
    Prvky tohoto pole jsou celá èísla (int).
    Ukazatel D umožòuje pøístup k prvkùm pole.
    */
    int (*D)[n];
    D = reinterpret_cast<int(*)[n]>(pole_ukazatelu);

    for (int i{0},eol{8-1}; i<n; i++,--eol)
    {
        cout << "0x" << hex << (*D)[i] << " ";
        if (!eol)
        {
            cout << endl;
            eol=8;
        }
    }

    /*
    Jedná se o deklaraci ukazatele na pole ukazatelù na int (int *).
    Symbol E je ukazatel, který ukazuje na pole o velikosti k.
    Prvky tohoto pole jsou ukazatele na int (int *).
    Ukazatel *E umožòuje pøístup k prvkùm pole ukazatelù.
    (*E)[0], (*E)[1], až po (*E)[k-1] jsou ukazatele na int.
    */
    int *(*E)[n];
    E = reinterpret_cast<int*(*)[n]>(&pole_ukazatelu);

    for (int i{0},eol{8-1}; i<n; i++,--eol)
    {
        cout << "0x" << hex << (*E)[0][i] << " ";
        if (!eol)
        {
            cout << endl;
            eol=8;
        }
    }
    /*
    Jedná se o deklaraci pole ukazatelù na int (int *).
    Symbol C je pole o velikosti m, kde každý prvek pole je ukazatel na int.
    Promìnné C[0], C[1], až po C[n-1] jsou ukazatele na int.
    */
    int *C[n];
    for (int i{0} ; i < n ; i++ )
        C[i] = pole_ukazatelu;

    for (int i{0},eol{8-1}; i<n; i++,--eol)
    {
        cout << "0x" << hex << (*C)[i] << " ";
        if (!eol)
        {
            cout << endl;
            eol=8;
        }
    }

}

void vypis_ukazatele_a_konstanty()
{
    // aplikovatelné i na modifikátor volatile
    int a{1}, b{2}, c{}; // stejné jako int a{1}, b{2}, c{0};

    // p je ukazatel na konstantu typu int. (Tedy p se mìnit mùže, ale promìnná, na kterou ukazuje, se mìnit nesmí.)
    const int *p = &a; // ukazatel na -> konstantu typu int
    cout << *p << " " << p << " " << &p << endl;
    p = &b; // *p = &b; // nelze
    cout << *p << " " << p << " " << &p << endl;

    // q je konstantní ukazatel na typ int. (Tedy q se mìnit nesmí, po celou dobu své existence bude ukazovat na touž promìnnou, ale tato promìnná se mìnit smí.)
    int *const q = &a; // konstantní ukazatel na -> typ int
    cout << *q << " " << q << " " << &q << endl;
    *q = b; // (v podstatì pøepíše a na 2) // q = &a; // nelze
    cout << *q << " " << q << " " << &q << endl;

    // r je konstantní ukazatel na konstantu typu int. (Tentokrát se nesmí mìnit ani ukazatel, ani promìnná, na kterou ukazuje.)
    const int *const r = &a; // konstantní ukazatel na -> konstantu typu int
    cout << *r << " " << r << " " << &r << endl;
    // *r = &b; // nelze
    // r = &b; // nelze

}

void vypis_deklaraci_typedef()
{
    const int M{16},N{16};

    // Klasicky - nepøehlednì
    // int (*pole_ukazatelu_pesky [N])[M];
    // nebo
    // pomocí typedef
    typedef int pole[M];    //deklarujeme typ pole pøedstavující pole o M prvcích typu int
    typedef pole *ukazatel_na_pole; // Pak deklarujeme typ ukazatel_na_pole pøedstavující ukazatel na typ pole
    ukazatel_na_pole pole_ukazatelu[N]; // {0xA0,0xA1,0xA2}; // Deklarace požadovaného pole je pak už jednoduchá:

    // inicializace
    for (int y{0}; y < N; y++)
    {
        for (int i{0}; i < N; i++)
        {
            pole_ukazatelu[y] = new pole[M];
            (*pole_ukazatelu[y])[i] = 0xA0+i;
            cout << (*pole_ukazatelu[y])[i] << " -> " << &(*pole_ukazatelu[y])[i] << " | ";
        }
    }
}

void vypis_deklaraci_using()
{
    const int M{16},N{16};

    // Klasicky - nepøehlednì
    // int (*pole_ukazatelu_pesky [N])[M];
    // nebo
    // pomocí typedef
    using pole = int[M];    //deklarujeme typ pole pøedstavující pole o M prvcích typu int
    using ukazatel_na_pole = pole*; // Pak deklarujeme typ ukazatel_na_pole pøedstavující ukazatel na typ pole
    ukazatel_na_pole pole_ukazatelu[N]; // {0xA0,0xA1,0xA2}; // Deklarace požadovaného pole je pak už jednoduchá:

    // inicializace
    for (int y{0}; y < N; y++)
    {
        for (int i{0}; i < N; i++)
        {
            pole_ukazatelu[y] = new pole[M];
            (*pole_ukazatelu[y])[i] = 0xA0+i;
            cout << (*pole_ukazatelu[y])[i] << " -> " << &(*pole_ukazatelu[y])[i] << " | ";
        }
    }
}

cislo faktorial_w_using(cislo m)
{
    cislo vysledek = 1;
    for(cislo i = 2; i <= m; i++)
    {
        vysledek *= i;
    }
    return vysledek;
}

void deklarace_auto()
{
    auto i = 0, *p = &i;
}

int pomoc_funkce_nebo_promenna() // 1
{
    cout << "pomocná funkce" << endl;
    return 6;
}

void vypis_zastineni_funkce_promennou() // 2
{
    int i = pomoc_funkce_nebo_promenna(), pomoc_funkce_nebo_promenna = 86; // 3
    cout << pomoc_funkce_nebo_promenna << " " << ::pomoc_funkce_nebo_promenna() << endl; // 4
    {
        //5
        int i = pomoc_funkce_nebo_promenna; // 6
        int pomoc_funkce_nebo_promenna = 97; // 7
        cout << pomoc_funkce_nebo_promenna << " " << ::pomoc_funkce_nebo_promenna() << endl; // 8
    } //9
    cout << pomoc_funkce_nebo_promenna << endl; // 10
}

