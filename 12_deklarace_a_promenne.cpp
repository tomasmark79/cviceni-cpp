#include <iostream>
#include "12_deklarace_a_promenne.h"

using namespace std;

/*
Celkov� lze tyto deklarace interpretovat jako vytvo�en� struktur dat,
kter� mohou b�t pou�ity pro pr�ci s maticemi nebo jin�mi v�cedimenzion�ln�mi daty.
Ka�d� z t�chto zp�sob� deklarace ukazuje na odli�n� zp�sob pr�ce s pam�t� a p��stupu k prvk�m.
*/

void vypis_pole_ukazatelu()
{
    //
    const int n{8}, eol{8};
    int *pole_ukazatelu = new int[n] {0xA0,0xA1,0xA2};

    /*
    Jedn� se o deklaraci ukazatele na pole int (int).
    Symbol D je ukazatel, kter� ukazuje na pole o velikosti n.
    Prvky tohoto pole jsou cel� ��sla (int).
    Ukazatel D umo��uje p��stup k prvk�m pole.
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
    Jedn� se o deklaraci ukazatele na pole ukazatel� na int (int *).
    Symbol E je ukazatel, kter� ukazuje na pole o velikosti k.
    Prvky tohoto pole jsou ukazatele na int (int *).
    Ukazatel *E umo��uje p��stup k prvk�m pole ukazatel�.
    (*E)[0], (*E)[1], a� po (*E)[k-1] jsou ukazatele na int.
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
    Jedn� se o deklaraci pole ukazatel� na int (int *).
    Symbol C je pole o velikosti m, kde ka�d� prvek pole je ukazatel na int.
    Prom�nn� C[0], C[1], a� po C[n-1] jsou ukazatele na int.
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
    // aplikovateln� i na modifik�tor volatile
    int a{1}, b{2}, c{}; // stejn� jako int a{1}, b{2}, c{0};

    // p je ukazatel na konstantu typu int. (Tedy p se m�nit m��e, ale prom�nn�, na kterou ukazuje, se m�nit nesm�.)
    const int *p = &a; // ukazatel na -> konstantu typu int
    cout << *p << " " << p << " " << &p << endl;
    p = &b; // *p = &b; // nelze
    cout << *p << " " << p << " " << &p << endl;

    // q je konstantn� ukazatel na typ int. (Tedy q se m�nit nesm�, po celou dobu sv� existence bude ukazovat na tou� prom�nnou, ale tato prom�nn� se m�nit sm�.)
    int *const q = &a; // konstantn� ukazatel na -> typ int
    cout << *q << " " << q << " " << &q << endl;
    *q = b; // (v podstat� p�ep�e a na 2) // q = &a; // nelze
    cout << *q << " " << q << " " << &q << endl;

    // r je konstantn� ukazatel na konstantu typu int. (Tentokr�t se nesm� m�nit ani ukazatel, ani prom�nn�, na kterou ukazuje.)
    const int *const r = &a; // konstantn� ukazatel na -> konstantu typu int
    cout << *r << " " << r << " " << &r << endl;
    // *r = &b; // nelze
    // r = &b; // nelze

}

void vypis_deklaraci_typedef()
{
    const int M{16},N{16};

    // Klasicky - nep�ehledn�
    // int (*pole_ukazatelu_pesky [N])[M];
    // nebo
    // pomoc� typedef
    typedef int pole[M];    //deklarujeme typ pole p�edstavuj�c� pole o M prvc�ch typu int
    typedef pole *ukazatel_na_pole; // Pak deklarujeme typ ukazatel_na_pole p�edstavuj�c� ukazatel na typ pole
    ukazatel_na_pole pole_ukazatelu[N]; // {0xA0,0xA1,0xA2}; // Deklarace po�adovan�ho pole je pak u� jednoduch�:

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

    // Klasicky - nep�ehledn�
    // int (*pole_ukazatelu_pesky [N])[M];
    // nebo
    // pomoc� typedef
    using pole = int[M];    //deklarujeme typ pole p�edstavuj�c� pole o M prvc�ch typu int
    using ukazatel_na_pole = pole*; // Pak deklarujeme typ ukazatel_na_pole p�edstavuj�c� ukazatel na typ pole
    ukazatel_na_pole pole_ukazatelu[N]; // {0xA0,0xA1,0xA2}; // Deklarace po�adovan�ho pole je pak u� jednoduch�:

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
    cout << "pomocn� funkce" << endl;
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

