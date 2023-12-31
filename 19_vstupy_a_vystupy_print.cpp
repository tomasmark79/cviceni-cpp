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
            string("Nepoda�ilo se otev��t soubor ") + vyst.jmeno);
    }
    // ...Ostatn� kontroly z�stanou stejn� jako v p��kladu 19.9
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

// P��KLAD 19.20: �TEME TEXTOV� SOUBOR, PRVN� POKUS
void cteni(char *jmeno)
{
    FILE *proud = fopen(jmeno, "r");
    if(!proud)
    {
        throw runtime_error("Nepoda�ilo se na��st vstupn� soubor");
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

// Rozhodneme-li se pou��t zabezpe�en� funkce, bude m�t tvar:
void cteni_s(char *jmeno)
{
    FILE *proud;
    int kod = fopen_s(&proud, jmeno, "r");
    if (kod)
    {
        throw runtime_error("Nepoda�ilo se na��st vstupn� soubor");
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
        //P��KLAD 19.18: SPECIFIKACE KONVERZE

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
        printf("%4.2f %7.5f\n", x, sin(x)); // Zde jsme ov�em zadali napevno
        // jak ���ku, tak p�esnost, a to, jak v�me, nen� dobr�.
        // Proto pou�ijeme mo�nost zadat tyto hodnoty jako parametry funkce printf().
        // Stejn� form�tovan� v�sledek dostaneme, kdy� nap�eme:
        printf("%*.*f %*.*f\n", 4, 2, x, 7, 5, sin(x));

        cout << endl;
        FILE *proud = fopen("data_print.txt", "w");
        popis_funkce fun {sin, (char*)"sin" };
        popis_tabulky tab{ 0,1,11 };
        popis_vystupu vyst{4,7,2,5, proud, (char*)"sin"};
        tabulka(fun, tab, vyst);

        popis_vystupu vyst2{4,7,2,5, stdout, (char*)"sin"};
        tabulka(fun, tab, vyst2);

        // P��KLAD 19.20: �TEME TEXTOV� SOUBOR, PRVN� POKUS
        printf("\n");
        cteni((char*)"data.txt"); // D�vod, pro� se nep�e�etl cel� text ulo�en� vsouboru,
        // je podobn� jako vp��kladu 19.2: vstupn� pole funkce fscanf()
        // kon�� uprvn�ho b�l�ho znaku. �e�en� si uk�eme d�le.
        cteni_s((char*)"data.txt");




    }
    catch (invalid_argument &e)
    {
        cerr << e.what() << endl;
    }
}
