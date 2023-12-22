#include "19_vstupy_a_vystupy_print.h"

using namespace std;
using funkce = double (*)(double);

struct popis_funkce
{

    funkce f;
    char* jmeno;
};

struct popis_tabulky
{
    double od, po;
    int kolik;
};

struct popis_vystupu
{
    int sirka_x, sirka_f, presnost_x, presnost_f;
    FILE *proud;
    char *jmeno;
};

void zahlavi(popis_funkce fun, popis_tabulky tab, popis_vystupu vyst)
{
    const int delka = 50;
    char pomlcky[delka], mezery[delka];
    memset(pomlcky, '-', delka - 1);
    pomlcky[delka - 1] = 0;
    int pocet_pomlcek = vyst.sirka_x + 11 + vyst.sirka_f;
    int pocet_mezer = vyst.sirka_x + vyst.sirka_f;
    fprintf(vyst.proud, "Tabulka funkce %s \n", fun.jmeno);
    fprintf(vyst.proud, "%.*s\n", pocet_pomlcek, pomlcky);
    fprintf(vyst.proud, "%*s%*c%s(x)\n", vyst.sirka_x, "x",
            pocet_mezer, ' ', fun.jmeno);
    fprintf(vyst.proud, "%.*s\n", pocet_pomlcek, pomlcky);
    printf("%s", fun.jmeno);
}

void kontrola(popis_funkce fun, popis_tabulky tab, popis_vystupu vyst)
{
    if(!vyst.proud)
    {
        throw runtime_error(
            string("Nepodaøilo se otevøít soubor ") + vyst.jmeno);
    }
    // ...Ostatní kontroly zùstanou stejné jako v pøíkladu 19.9
}

void tabulka(popis_funkce fun, popis_tabulky tab, popis_vystupu vyst)
{
    kontrola(fun, tab, vyst);

    double krok =
        tab.kolik == 1 ? 0 : (tab.po - tab.od) / (tab.kolik - 1);

    zahlavi(fun, tab, vyst);

    for (int i = 0; i < tab.kolik; i++)
    {
        double x = tab.od + i*krok;
        fprintf(vyst.proud, "%*.*f %*.*f\n", vyst.sirka_x,
                vyst.presnost_x, x, vyst.sirka_f, vyst.presnost_f,
                fun.f(x));
    }
}

auto vstupy_vystupy_print() -> void
{
    try
    {
        //PØÍKLAD 19.18: SPECIFIKACE KONVERZE

        int m = 0x1feb;
        printf("%d ", m);
        printf("%x ", m);
        printf("%X ", m);

        double xxx = 213.765e3;
        printf("%f ", xxx);
        printf("%e ", xxx);
        printf("%E ", xxx);
        printf("%g ", xxx);
        printf("%G ", xxx);

        cout << endl;
        double x = 0.4;
        printf("%4.2f %7.5f\n", x, sin(x)); // Zde jsme ovšem zadali napevno
        // jak šíøku, tak pøesnost, a to, jak víme, není dobré.
        // Proto použijeme možnost zadat tyto hodnoty jako parametry funkce printf().
        // Stejnì formátovaný výsledek dostaneme, když napíšeme:
        printf("%*.*f %*.*f\n", 4, 2, x, 7, 5, sin(x));

        cout << endl;
        FILE *proud = fopen("data_print.txt", "w");
        popis_funkce fun {sin, "sin" };
        popis_tabulky tab{ 0,1,11 };
        popis_vystupu vyst{4,7,2,5, proud, "sin"};
        tabulka(fun, tab, vyst);

        }
    catch (invalid_argument &e)
    {
        cerr << e.what() << endl;
    }
}
