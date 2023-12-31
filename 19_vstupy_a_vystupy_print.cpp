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
    char pomlcky[delka]; //, mezery[delka];
    memset(pomlcky, '-', delka - 1);
    pomlcky[delka - 1] = 0;
    int pocet_pomlcek = vyst.sirka_x + 11 + vyst.sirka_f;
    int pocet_mezer = vyst.sirka_x + vyst.sirka_f;
    fprintf(vyst.proud, "Tabulka funkce %s \n", fun.jmeno);
    fprintf(vyst.proud, "%.*s\n", pocet_pomlcek, pomlcky);
    fprintf(vyst.proud, "%*s%*c%s(x)\n", vyst.sirka_x, "x",
            pocet_mezer, ' ', fun.jmeno);
    fprintf(vyst.proud, "%.*s\n", pocet_pomlcek, pomlcky);
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
        fprintf(vyst.proud, "%*.*f %*.*f\n",
                vyst.sirka_x, vyst.presnost_x, x,
                vyst.sirka_f, vyst.presnost_f, fun.f(x));
    }
}
const int kolik = 50;

// PØÍKLAD 19.20: ÈTEME TEXTOVÝ SOUBOR, PRVNÍ POKUS
void cteni(char *jmeno)
{
    FILE *proud = fopen(jmeno, "r");
    if(!proud)
    {
        throw runtime_error("Nepodaøilo se naèíst vstupní soubor");
    }

    int i;
    while (fscanf(proud, " %i", &i) > 0)
    {
        printf("%d ", i);
    }
    printf("\n");
    char text[kolik] {};
    fscanf(proud, "%s", text);
    printf("%s\n", text);
    fclose(proud);
}

// Rozhodneme-li se použít zabezpeèené funkce, bude mít tvar:
void cteni_s(char *jmeno)
{
    FILE *proud;
    int kod = fopen_s(&proud, jmeno, "r");
    if (kod)
    {
        throw runtime_error("Nepodaøilo se naèíst vstupní soubor");
    }
    int i;
    while (fscanf_s(proud, " %i", &i) > 0)
    {
        printf_s("%d ", i);
    }
    printf_s("\n");
    char text[kolik] {};
    fscanf_s(proud, "%s", text, kolik);
    printf_s("%s\n", text);
    fclose(proud);
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
        popis_funkce fun {sin, (char*)"sin" };
        popis_tabulky tab{ 0,1,11 };
        popis_vystupu vyst{4,7,2,5, proud, (char*)"sin"};
        tabulka(fun, tab, vyst);

        popis_vystupu vyst2{4,7,2,5, stdout, (char*)"sin"};
        tabulka(fun, tab, vyst2);

        // PØÍKLAD 19.20: ÈTEME TEXTOVÝ SOUBOR, PRVNÍ POKUS
        printf("\n");
        cteni((char*)"data.txt"); // Dùvod, proè se nepøeèetl celý text uložený vsouboru,
        // je podobný jako vpøíkladu 19.2: vstupní pole funkce fscanf()
        // konèí uprvního bílého znaku. Øešení si ukážeme dále.
        cteni_s((char*)"data.txt");




    }
    catch (invalid_argument &e)
    {
        cerr << e.what() << endl;
    }
}
