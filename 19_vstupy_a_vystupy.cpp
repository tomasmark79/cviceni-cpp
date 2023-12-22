#include "19_vstupy_a_vystupy.h"

using namespace std;


// PØÍKLAD 19.1: ZAPISUJEME DATA DO TEXTOVÉHO SOUBORU
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


// PØÍKLAD 19.2: ÈTEME DATA Z TEXTOVÉHO SOUBORU, PRVNÍ POKUS
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

// PØÍKLAD 19.3: ÈTENÍ Z TEXTOVÉHO SOUBORU, DRUHİ POKUS
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

struct popis_funkce
{
    using funkce = double (*)(double);
    funkce f;
    string jmeno;
};
struct popis_tabulky
{
    double od, po;
    int kolik;
};
struct popis_vystupu
{
    int sirka_x, sirka_f, presnost_x, presnost_f;
    ostream& proud;
};

// PØÍKLAD 19.5: POMOCNÉ FUNKCE
void kontrola_19_5(popis_funkce fun, popis_tabulky tab)
{
    if (!fun.f)
    {
        throw invalid_argument(
            "Prázdnı ukazatel na tabelovanou funkci");
    }
    if (tab.kolik <= 0)
    {
        throw invalid_argument("Nekladnı poèet poadovanıch hodnot");
    }
    if ((tab.kolik == 1) && (tab.od != tab.po))
    {
        throw invalid_argument(
            "Poadována jediná hodnota v intervalu nenulové délky");
    }
}

// PØÍKLAD 19.6: VYLEPŠUJEME TISK TABULKY – PØESNOST REÁLNİCH ÈÍSEL
// PØÍKLAD 19.8: TISK HLAVIÈKY
void zahlavi_19(popis_funkce fun, popis_tabulky tab, popis_vystupu vyst,
                ostream& proud)
{
    const int mezera = 10;
    int pocet_pomlcek = vyst.sirka_x + mezera + vyst.sirka_f;

    proud << "Tabulka funkce " << fun.jmeno << endl
          << string(pocet_pomlcek, '-') << endl;

    proud << setw(vyst.sirka_x) << "x";
    proud << setw(vyst.sirka_f + mezera) << "f";
    proud << endl
          << string(pocet_pomlcek, '-') << endl;
}

// PØÍKLAD 19.7: VYLEPŠUJEME TISK TABULKY – PØESNOST JAKO PARAMETR
/*void tabulka(funkce f, string jmeno, double od, double po,
             int kolik, int presnost_x, int presnost_f, int sirka_x, int sirka_f)
*/
// moc parametrù jsme zde nahradili strukturami
// PØÍKLAD 19.9: PØÍLIŠ MNOHO PARAMETRÙ
// PØÍKLAD 19.10: ZÁPIS TABULKY DO SOUBORU – PØESMÌROVÁNÍ
// PØÍKLAD 19.11: ZÁPIS TABULKY DO SOUBORU – PØEDÁVÁME PROUD

void tabulka(popis_funkce fun, popis_tabulky tab, popis_vystupu vyst,
             ostream& proud)
{
    kontrola_19_5(fun, tab);
    double krok = tab.kolik == 1 ? 0 : (tab.po - tab.od) / (tab.kolik - 1);

    zahlavi_19(fun, tab, vyst, proud);

    proud << fixed;

    for (int i = 0; i < tab.kolik; i++)
    {
        double x = tab.od + i*krok;
        proud << setprecision(vyst.presnost_x) << setw(vyst.sirka_x) << x << "          "
              << setprecision(vyst.presnost_f) << setw(vyst.sirka_f) << fun.f(x) << endl;
    }
}


//
//
// 19.3 Nástroje zdìdìné od jazyka C
//
// FILE

void kontrola_proudu(FILE *proud, char *jmeno)
{
    if (!proud)
    {
        throw runtime_error(
            string("Nepodaøilo se otevøít soubor ") + jmeno);
    }
}

// PØÍKLAD 19.12: VYTVOØENÍ BINÁRNÍHO SOUBORU
void zapis_19_12(char *jmeno)
{
    FILE *proud = fopen(jmeno, "wb");
    if (!proud)
    {
        throw runtime_error(
            string("Nepodaøilo se otevøít soubor ") + jmeno);
    }
    for (int i = 1; i <= 10; i++)
    {
        fwrite(&i, sizeof(i), 1, proud);
    }
    fclose(proud);
}

// PØÍKLAD 19.14: ÈTENÍ BINÁRNÍHO SOUBORU
void cteni_19_14(char *jmeno)
{
    FILE *proud = fopen(jmeno, "rb");
    kontrola_proudu(proud, jmeno);
    int i;
    while (fread(&i, sizeof(i), 1, proud))
    {
        cout << i << endl;
    }
    fclose(proud);
}

// PØÍKLAD 19.13: BINÁRNÍ SOUBOR V TEXTOVÉM REIMU
//
void zapis_19_13_safe(char *jmeno)
{
    FILE *proud = nullptr;
    errno_t kod = fopen_s(&proud, jmeno, "w");
    if (kod)
    {
        throw runtime_error(
            string("Nepodaøilo se otevøít soubor ") + jmeno);
    }
    for (int i = 1; i <= 10; i++)
    {
        fwrite(&i, sizeof(i), 1, proud);
    }
    fclose(proud);
}

// PØÍKLAD 19.15: PØIPOJENÍ DAT NA KONEC SOUBORU
void pripojeni_19_15(char *jmeno, int *co, int kolik)
{
    FILE *proud = fopen(jmeno, "ab");
    kontrola_proudu(proud, jmeno);
    fwrite(co, sizeof(int), kolik, proud);
    fclose(proud);
}

// PØÍKLAD 19.16: ÈTEME PØEDPOSLEDNÍ POLOKU V SOUBORU
void predposledni_hodnota_19_16(char *jmeno)
{
    FILE*proud = fopen(jmeno, "rb");
    kontrola_proudu(proud, jmeno);
    fseek(proud, -2*(long)sizeof(int), SEEK_END);
    int i;
    fread(&i, sizeof(i), 1, proud);
    cout << i << endl;
}

// PØÍKLAD 19.17: AKTUALIZACE SOUBORU
void aktualizace_19_17(char *jmeno)
{
    FILE *proud = fopen(jmeno, "rb+");
    kontrola_proudu(proud, jmeno);
    int i;
    while (fread(&i, sizeof(int), 1, proud))
    {
        //if (i / 2 == 0) // toto je v uèebnici špatnì (toto nenajde sudé èíslo)
        if (i % 2 == 0) // toto je opravené mnou a najde sudé èíslo
        {
            i = i / 2;
            fseek(proud, -(long)sizeof(int), SEEK_CUR);
            fwrite(&i, sizeof(int), 1, proud);
            fseek(proud, 0, SEEK_CUR); // sice o 0 bajtù, ale nutné mezi write and read.
        }
    }
    fclose(proud);
}

// PØÍKLAD 19.19: JEŠTÌ JEDNOU TABULKA FUNKCE
void tabulka_19_19(popis_funkce fun, popis_tabulky tab, popis_vystupu vyst,
                   ostream& proud)
{
    kontrola_19_5(fun, tab);
    double krok = tab.kolik == 1 ? 0 : (tab.po - tab.od) / (tab.kolik - 1);

    zahlavi_19(fun, tab, vyst, proud);

    proud << fixed;

    for (int i = 0; i < tab.kolik; i++)
    {
        double x = tab.od + i*krok;
        proud << setprecision(vyst.presnost_x) << setw(vyst.sirka_x) << x << "          "
              << setprecision(vyst.presnost_f) << setw(vyst.sirka_f) << fun.f(x) << endl;
    }
}

auto vstupy_vystupy() -> void
{
    zapisujeme_data_do_textoveho_souboru("X:\\data.txt", "luouèkı kùò pøíšernì úpìl ïábelské ódy");
    cout << endl;
    zapisujeme_data_do_textoveho_souboru("data.txt", "luouèkı kùò pøíšernì úpìl ïábelské ódy");
    cteni("data.txt");
    cteni_19_3("data.txt");
    cteni_s_getline("data.txt");
    cout << endl;

    ofstream fileproud("tabulka.txt");

    try
    {
        popis_funkce f1{ [](double x)->double {return x*x; }, "x^2" };
        cout << endl;
        popis_tabulky tab1{ 998, 1008, 11 };
        popis_vystupu vyst1{ 10, 10, 1, 1, cout }; // parametr ostream jen pro ukázku
        tabulka(f1, tab1, vyst1, cout);
        tabulka(f1, tab1, vyst1, fileproud);
        // tabulka(f1, tab1, vyst1, (fileproud) ? fileproud : cout); // funguje dle oèekávání - buï a nebo
        cout << endl;

        popis_funkce f2{ sin, "sin" };
        popis_tabulky tab2{ 0, 1, 15 };
        popis_vystupu vyst2{ 10, 10, 8, 2, cout }; // parametr ostream jen pro ukázku

        tabulka(f2, tab2, vyst2, cout);
        tabulka(f2, tab2, vyst2, fileproud);

        zapis_19_12((char*)"data.dta");
        cteni_19_14((char*)"data.dta");

        int A[] { 11,12,13,14,15,16 };
        pripojeni_19_15((char*)"data.dta", A, sizeof(A) / sizeof(int)); // 1 - 16

        predposledni_hodnota_19_16((char*)"data.dta"); // 15
        aktualizace_19_17((char*)"data.dta");

        zapis_19_13_safe((char*)"data-safe.dta");
        cteni_19_14((char*)"data-safe.dta");

    }
    catch (invalid_argument &e)
    {
        cerr << e.what() << endl;
    }
}
