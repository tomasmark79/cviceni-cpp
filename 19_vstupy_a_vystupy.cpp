#include "19_vstupy_a_vystupy.h"

using namespace std;

//
// P��KLAD 19.1: ZAPISUJEME DATA DO TEXTOV�HO SOUBORU
//

void zapisujeme_data_do_textoveho_souboru(string jmeno, string text)
{
    ofstream vystup(jmeno);
    if (!vystup)
    {
        cerr << "Nepoda�ilo se otev��t soubor " << jmeno << endl;
        return;
    }
    for (int i = 1; i <= 10; i++)
    {
        vystup << i << " ";
    }
    vystup << endl << text << endl;
}

//
// P��KLAD 19.2: �TEME DATA Z TEXTOV�HO SOUBORU, PRVN� POKUS
//

// oper�tor >> �te jen po nejbli��� b�l� znak
void cteni(string jmeno) // Nep�e�te cel� text
{
    ifstream vstup(jmeno);
    if (!vstup)
    {
        cerr << "Nepoda�ilo se otev��t soubor " << jmeno << endl;
        return;
    }
    int i;
    while (vstup >> i) // p�i na�ten� textu nastane chyba a vstup vr�t� false
    {
        cout << i << " ";
    }

    vstup.clear(); // oprava
    cout << endl;

    string textik;

    vstup >> textik;

    cout << textik << endl;
}

//
// P��KLAD 19.3: �TEN� Z TEXTOV�HO SOUBORU, DRUH� POKUS
//
void cteni_19_3(string jmeno)
{
    ifstream vstup(jmeno);
    if (!vstup)
    {
        cerr << "Nepoda�ilo se otev��t soubor " << jmeno << endl;
        return;
    }
    int i;
    while (vstup >> i) // p�i na�ten� textu nastane chyba a vstup vr�t� false
    {
        cout << i << " ";
    }

    vstup.clear(); // oprava - nutn�, aby se opravil proud a mohl se d�le pou��vat
    cout << endl;

    // ...Kontrola a �ten� cel�ch ��sel je stejn� jako p�edt�m
    string vysledek;
    string textik;
    while (vstup >> textik)
    {
        vysledek += textik + " ";
    }
    cout << vysledek << endl;
}

// Tentokr�t dostaneme o�ek�van� v�stup pro jak�koli jedno��dkov� text.
void cteni_s_getline(string jmeno)
{
    ifstream vstup(jmeno);
    if (!vstup)
    {
        cerr << "Nepoda�ilo se otev��t soubor " << jmeno << endl;
        return;
    }
    int i;
    while (vstup >> i) // p�i na�ten� textu nastane chyba a vstup vr�t� false
    {
        cout << i << " ";
    }
    // ...Kontrola a �ten� cel�ch ��sel je stejn� jako p�edt�m...
    vstup.clear();
    cout << endl;

    string textik;
    getline(vstup, textik);
    cout << textik << endl;
}


//
// P��KLAD 19.4: TABULKA FUNKCE � P��PRAVA
//

using funkce = double (*)(double);

void kontrola(funkce f, double od, double po, int kolik)
{
    if (!f)
    {
        throw invalid_argument(
            "Pr�zdn� ukazatel na tabelovanou funkci");
    }
    if (kolik <= 0)
    {
        throw invalid_argument("Nekladn� po�et po�adovan�ch hodnot");
    }
    if ((kolik == 1) && (od != po))
    {
        throw invalid_argument(
            "Po�adov�na jedin� hodnota v intervalu nenulov� d�lky");
    }
}

void zahlavi19(string jmeno)
{
    cout << __func__ << ": " << jmeno << endl;
}

void tabulka(funkce f, string jmeno, double od, double po, int kolik)
{
    kontrola(f, od, po, kolik);

    // vypo�te krok tabelace, tedy interval mezi jednotliv�mi hodnotami,
    // v nich� budeme po��tat a tisknout hodnoty p�edan� funkce
    // P�i v�po�tu kroku, tedy vzd�lenosti mezi body, v nich� chceme p�edanou funkci po��tat
    // a tisknout, jsme na rozd�l od p��kladu 13.8 vzali v �vahu i mo�nost kolik == 1.
    // V takov�m p��pad� se krok nepou�ije, tak�e na hodnot� t�to prom�nn� nez�le��,
    // a proto jsme do n� ulo�ili hodnotu 0.
    double krok = kolik == 1 ? 0 : (po - od) / (kolik - 1);

    zahlavi19(jmeno);
    for (int i = 0; i < kolik; i++)
    {
        double x = od + i*krok;
        cout << x << " " << f(x) << endl;
    }
}

auto vstupy_vystupy() -> void
{
    zapisujeme_data_do_textoveho_souboru("X:\data.txt", "�lu�ou�k� k�� p��ern� �p�l ��belsk� �dy");
    zapisujeme_data_do_textoveho_souboru("data.txt", "�lu�ou�k� k�� p��ern� �p�l ��belsk� �dy");
    cteni("data.txt");
    cteni_19_3("data.txt");
    cteni_s_getline("data.txt");
    cout << endl;

    tabulka(sin, "sin(x)", 0, 1, 19);
}
