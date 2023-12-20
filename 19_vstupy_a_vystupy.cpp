#include "19_vstupy_a_vystupy.h"

using namespace std;

//
// PØÍKLAD 19.1: ZAPISUJEME DATA DO TEXTOVÉHO SOUBORU
//

void zapisujeme_data_do_textoveho_souboru(string jmeno, string text)
{
    ofstream vystup(jmeno);
    if (!vystup)
    {
        cerr << "Nepodaøilo se otevøít soubor " << jmeno << endl;
        return;
    }
    for (int i = 1; i <= 10; i++)
    {
        vystup << i << " ";
    }
    vystup << endl << text << endl;
}

//
// PØÍKLAD 19.2: ÈTEME DATA Z TEXTOVÉHO SOUBORU, PRVNÍ POKUS
//

// operátor >> ète jen po nejbliší bílı znak
void cteni(string jmeno) // Nepøeète celı text
{
    ifstream vstup(jmeno);
    if (!vstup)
    {
        cerr << "Nepodaøilo se otevøít soubor " << jmeno << endl;
        return;
    }
    int i;
    while (vstup >> i) // pøi naètení textu nastane chyba a vstup vrátí false
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
// PØÍKLAD 19.3: ÈTENÍ Z TEXTOVÉHO SOUBORU, DRUHİ POKUS
//
void cteni_19_3(string jmeno)
{
    ifstream vstup(jmeno);
    if (!vstup)
    {
        cerr << "Nepodaøilo se otevøít soubor " << jmeno << endl;
        return;
    }
    int i;
    while (vstup >> i) // pøi naètení textu nastane chyba a vstup vrátí false
    {
        cout << i << " ";
    }

    vstup.clear(); // oprava - nutné, aby se opravil proud a mohl se dále pouívat
    cout << endl;

    // ...Kontrola a ètení celıch èísel je stejné jako pøedtím
    string vysledek;
    string textik;
    while (vstup >> textik)
    {
        vysledek += textik + " ";
    }
    cout << vysledek << endl;
}

// Tentokrát dostaneme oèekávanı vıstup pro jakıkoli jednoøádkovı text.
void cteni_s_getline(string jmeno)
{
    ifstream vstup(jmeno);
    if (!vstup)
    {
        cerr << "Nepodaøilo se otevøít soubor " << jmeno << endl;
        return;
    }
    int i;
    while (vstup >> i) // pøi naètení textu nastane chyba a vstup vrátí false
    {
        cout << i << " ";
    }
    // ...Kontrola a ètení celıch èísel je stejné jako pøedtím...
    vstup.clear();
    cout << endl;

    string textik;
    getline(vstup, textik);
    cout << textik << endl;
}


//
// PØÍKLAD 19.4: TABULKA FUNKCE – PØÍPRAVA
//

using funkce = double (*)(double);

void kontrola(funkce f, double od, double po, int kolik)
{
    if (!f)
    {
        throw invalid_argument(
            "Prázdnı ukazatel na tabelovanou funkci");
    }
    if (kolik <= 0)
    {
        throw invalid_argument("Nekladnı poèet poadovanıch hodnot");
    }
    if ((kolik == 1) && (od != po))
    {
        throw invalid_argument(
            "Poadována jediná hodnota v intervalu nenulové délky");
    }
}

void zahlavi19(string jmeno)
{
    cout << __func__ << ": " << jmeno << endl;
}

void tabulka(funkce f, string jmeno, double od, double po, int kolik)
{
    kontrola(f, od, po, kolik);

    // vypoète krok tabelace, tedy interval mezi jednotlivımi hodnotami,
    // v nich budeme poèítat a tisknout hodnoty pøedané funkce
    // Pøi vıpoètu kroku, tedy vzdálenosti mezi body, v nich chceme pøedanou funkci poèítat
    // a tisknout, jsme na rozdíl od pøíkladu 13.8 vzali v úvahu i monost kolik == 1.
    // V takovém pøípadì se krok nepouije, take na hodnotì této promìnné nezáleí,
    // a proto jsme do ní uloili hodnotu 0.
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
    zapisujeme_data_do_textoveho_souboru("X:\data.txt", "luouèkı kùò pøíšernì úpìl ïábelské ódy");
    zapisujeme_data_do_textoveho_souboru("data.txt", "luouèkı kùò pøíšernì úpìl ïábelské ódy");
    cteni("data.txt");
    cteni_19_3("data.txt");
    cteni_s_getline("data.txt");
    cout << endl;

    tabulka(sin, "sin(x)", 0, 1, 19);
}
