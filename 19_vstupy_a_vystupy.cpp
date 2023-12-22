#include "19_vstupy_a_vystupy.h"

using namespace std;


// P��KLAD 19.1: ZAPISUJEME DATA DO TEXTOV�HO SOUBORU
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


// P��KLAD 19.2: �TEME DATA Z TEXTOV�HO SOUBORU, PRVN� POKUS
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

// P��KLAD 19.3: �TEN� Z TEXTOV�HO SOUBORU, DRUH� POKUS
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

// P��KLAD 19.5: POMOCN� FUNKCE
void kontrola_19_5(popis_funkce fun, popis_tabulky tab)
{
    if (!fun.f)
    {
        throw invalid_argument(
            "Pr�zdn� ukazatel na tabelovanou funkci");
    }
    if (tab.kolik <= 0)
    {
        throw invalid_argument("Nekladn� po�et po�adovan�ch hodnot");
    }
    if ((tab.kolik == 1) && (tab.od != tab.po))
    {
        throw invalid_argument(
            "Po�adov�na jedin� hodnota v intervalu nenulov� d�lky");
    }
}

// P��KLAD 19.6: VYLEP�UJEME TISK TABULKY � P�ESNOST RE�LN�CH ��SEL
// P��KLAD 19.8: TISK HLAVI�KY
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

// P��KLAD 19.7: VYLEP�UJEME TISK TABULKY � P�ESNOST JAKO PARAMETR
/*void tabulka(funkce f, string jmeno, double od, double po,
             int kolik, int presnost_x, int presnost_f, int sirka_x, int sirka_f)
*/
// moc parametr� jsme zde nahradili strukturami
// P��KLAD 19.9: P��LI� MNOHO PARAMETR�
// P��KLAD 19.10: Z�PIS TABULKY DO SOUBORU � P�ESM�ROV�N�
// P��KLAD 19.11: Z�PIS TABULKY DO SOUBORU � P�ED�V�ME PROUD

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
// 19.3 N�stroje zd�d�n� od jazyka C
//
// FILE

void kontrola_proudu(FILE *proud, char *jmeno)
{
    if (!proud)
    {
        throw runtime_error(
            string("Nepoda�ilo se otev��t soubor ") + jmeno);
    }
}

// P��KLAD 19.12: VYTVO�EN� BIN�RN�HO SOUBORU
void zapis_19_12(char *jmeno)
{
    FILE *proud = fopen(jmeno, "wb");
    if (!proud)
    {
        throw runtime_error(
            string("Nepoda�ilo se otev��t soubor ") + jmeno);
    }
    for (int i = 1; i <= 10; i++)
    {
        fwrite(&i, sizeof(i), 1, proud);
    }
    fclose(proud);
}

// P��KLAD 19.14: �TEN� BIN�RN�HO SOUBORU
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

// P��KLAD 19.13: BIN�RN� SOUBOR V TEXTOV�M RE�IMU
//
void zapis_19_13_safe(char *jmeno)
{
    FILE *proud = nullptr;
    errno_t kod = fopen_s(&proud, jmeno, "w");
    if (kod)
    {
        throw runtime_error(
            string("Nepoda�ilo se otev��t soubor ") + jmeno);
    }
    for (int i = 1; i <= 10; i++)
    {
        fwrite(&i, sizeof(i), 1, proud);
    }
    fclose(proud);
}

// P��KLAD 19.15: P�IPOJEN� DAT NA KONEC SOUBORU
void pripojeni_19_15(char *jmeno, int *co, int kolik)
{
    FILE *proud = fopen(jmeno, "ab");
    kontrola_proudu(proud, jmeno);
    fwrite(co, sizeof(int), kolik, proud);
    fclose(proud);
}

// P��KLAD 19.16: �TEME P�EDPOSLEDN� POLO�KU V SOUBORU
void predposledni_hodnota_19_16(char *jmeno)
{
    FILE*proud = fopen(jmeno, "rb");
    kontrola_proudu(proud, jmeno);
    fseek(proud, -2*(long)sizeof(int), SEEK_END);
    int i;
    fread(&i, sizeof(i), 1, proud);
    cout << i << endl;
}

// P��KLAD 19.17: AKTUALIZACE SOUBORU
void aktualizace_19_17(char *jmeno)
{
    FILE *proud = fopen(jmeno, "rb+");
    kontrola_proudu(proud, jmeno);
    int i;
    while (fread(&i, sizeof(int), 1, proud))
    {
        //if (i / 2 == 0) // toto je v u�ebnici �patn� (toto nenajde sud� ��slo)
        if (i % 2 == 0) // toto je opraven� mnou a najde sud� ��slo
        {
            i = i / 2;
            fseek(proud, -(long)sizeof(int), SEEK_CUR);
            fwrite(&i, sizeof(int), 1, proud);
            fseek(proud, 0, SEEK_CUR); // sice o 0 bajt�, ale nutn� mezi write and read.
        }
    }
    fclose(proud);
}

// P��KLAD 19.19: JE�T� JEDNOU TABULKA FUNKCE
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
    zapisujeme_data_do_textoveho_souboru("X:\\data.txt", "�lu�ou�k� k�� p��ern� �p�l ��belsk� �dy");
    cout << endl;
    zapisujeme_data_do_textoveho_souboru("data.txt", "�lu�ou�k� k�� p��ern� �p�l ��belsk� �dy");
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
        popis_vystupu vyst1{ 10, 10, 1, 1, cout }; // parametr ostream jen pro uk�zku
        tabulka(f1, tab1, vyst1, cout);
        tabulka(f1, tab1, vyst1, fileproud);
        // tabulka(f1, tab1, vyst1, (fileproud) ? fileproud : cout); // funguje dle o�ek�v�n� - bu� a nebo
        cout << endl;

        popis_funkce f2{ sin, "sin" };
        popis_tabulky tab2{ 0, 1, 15 };
        popis_vystupu vyst2{ 10, 10, 8, 2, cout }; // parametr ostream jen pro uk�zku

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
