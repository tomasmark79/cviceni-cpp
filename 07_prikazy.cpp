#include <iostream>
#include "07_prikazy.h"

using namespace std;

const int pocet_pozdravu = 3;
void vypis_pozdrav_pomoci_pole_string(int i)
{
    string pozdrav[pocet_pozdravu] { "Ahoj", "Nazdar", "Poklona" };
    string vychozi = "Poklona";
    if ((i >= 0) && (i <= pocet_pozdravu))
    {
        cout << pozdrav[i];
    }
    else
    {
        cout << vychozi;
    }

    cout << endl;
}

void vypis_pozdrav_pomoci_switch(char i)
{
    switch (i)
    {
    case 0:
        cout << "Ahoj";
        break;
    case 1:
    case 2:
        cout << "Nazdar";
        break;
    default:
        cout << "Poklona";
        break;
    }
    cout << endl;
}

int vstup_je_hodnota_cislo()
{
    int a;
    if(!cin) cout << "Zadaná hodnota nepøedstavuje èíslo" << endl;
    if (cin)
    {
        // Úmyslnì prázdný pøíkaz
        ;

    }
    else
    {
        cout << "ZADANá HODNOTA NEPøEDSTAVUJE èíSLO" << endl;
    }

    return 0;
}

int vstup_mam_pokracovat(string dotaz)
{
    string odpoved;
    bool rozhodnuto;
    do
    {
        cout << dotaz << endl;
        cout << "Odpovìzte 'ano' nebo 'ne', nebo 'seru na to' a stisknìte Enter: ";
        cin >> odpoved;

        rozhodnuto = (odpoved[0] == 'a') || (odpoved[0] == 'n') || (odpoved[0] == 's');
    }
    while (!rozhodnuto);   // dokud false, opakuj dotaz
    return odpoved[0]=='a'; // vrati TRUE kdyz odpvoed byla 'a'
}

void for_cyklus_nekonecny()
{
    cout << "-- >zahájil se nekoneèný cyklus" << endl;
    for ( ; ; )
    {
        ;
    }
}

void for_pruchod_indexem_a_objektem()
{
    const int N = 10;
    int A[N] {1,2,3,4,5,6,7,8,9,10};
    int B[N] {11,12,13,14,15,16,17,18,19,20};

    cout << "For jak jej zname" << endl ;
    for (int i = 0; i < N; i ++)
    {
        cout << A[i] << " ";
    }
    cout << endl << endl ;

    cout << "For pro kontejner" << endl;
    for (int i : A)
    {
        cout << i << " ";
    }
    cout << endl << endl ;



    // toto meni pouze kopii promenne "i"
    cout << "For pro kontejner se zmenou i++" << endl ;
    for (int i : B)
    {
        i+=1;
        cout << i << " ";
    }
    cout << endl << endl ;

    // toto meni jiz vlastni prvky kontejneru
    cout << "Zde jsme ridici promennou deklarovali jako referenci na typ int"<< endl;
    for (int &i : B)
    {
        i+=1;
        cout << i << " ";
    }
    // cout << B[0];

    cout << endl << endl ;
}

void vypis_for_a_prikaz_break()
{
    const int N = 5;
    int A[N] {10,11,50,68,-6};

    int vysledek = -1;
    for (int i = 0; i < N; i++)
    {
        if (A[i] < 0)
        {
            vysledek = i;
            break; // vyskoci ven
        }
    }
    if (vysledek < 0)
    {
        cout << "Není tam" << endl;
    }
    else
    {
        cout << "První záporný prvek má index " << vysledek << endl;
    }
}

void vypis_for_a_prikaz_continue()
{
    int N = 9;
    int A[N] {1,2,-3,4,5,6,7,8,9};

    for (int i : A)
    {
        if (i < 0)
            // continue; // preskakuje na konec cyklu a zahaji dalsi iteraci
            goto konec;

        cout << i << " ";

        konec:;
    }
    cout << endl;
}
