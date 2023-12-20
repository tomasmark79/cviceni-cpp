#include <iostream>
#include <iomanip>
#include <assert.h>
#include <limits>
#include <memory>
#include "18_chyby_za_behu_programu.h"

using namespace std;

#define FAKT_MAX (int)12
#define FAKT_TEST_NR (int)11
#define FAKT_TEST_NR_OUTOR (int)19

//
// PØÍKLAD 18.3: DETEKCE CELOÈÍSLENÉHO PØETEÈENÍ
//

template<typename T>
T bezpecny_soucet(T a, T b)
// int bezpecny_soucet(int a, int b)
{
    if ((a > 0) && (b > numeric_limits<T>::max() - a))
    {
        throw overflow_error("Výsledek > <T>");
    }
    if ((a < 0) && (b < numeric_limits<T>::min() + a))
    {
        throw overflow_error("Výsledek < <T>");
    }
    return a + b;
}
int bezpecny_rozdil(int a, int b)
{
    if ((b < 0) && (a > numeric_limits<int>::max() + b))
    {
        throw overflow_error("Výsledek > INT_MAX");
    }
    if ((b > 0) && (a < numeric_limits<int>::min() + b))
    {
        throw overflow_error("Výsledek < INT_MIN");
    }
    return a - b;
}
int bezpecny_soucin(int a, int b)
{
    if (b == 0)
    {
        return 0;
    }
    if (a > numeric_limits<int>::max() / b)
    {
        throw overflow_error("Výsledek > INT_MAX");
    }
    if (a < numeric_limits<int>::min() / b)
    {
        throw overflow_error("Výsledek < INT_MIN");
    }
    return a * b;
}
int bezpecny_podil(int a, int b)
{
    if (b == 0)
    {
        throw domain_error("Dìlení nulou");
    }
    if ((a == numeric_limits<int>::min()) && (b == -1))
    {
        throw overflow_error("Výsledek dìlení mimo rozsah");
    }
    return a / b;
}

int faktorial_18_3(int n)
{
    if (n < 0)
    {
        throw invalid_argument("Záporný parametr faktoriálu");
    }
    int vysledek = 1;
    while (n > 1)
    {
        vysledek = bezpecny_soucin(n, vysledek);
        n--;
    }
    return vysledek;
}
//
// PØÍKLAD 18.2: VÝPOÈET FAKTORIÁLU V KNIHOVNÍ FUNKCI
//

int faktorial_18_2(int n)
{
    if ((n < 0) || (n > FAKT_MAX))
    {
        throw out_of_range("Parametr faktoriálu mimo dovolený rozsah!");
    }
    int vysledek = 1;
    while (n>1)
    {
        vysledek *= n--;
    }
    return vysledek;
}

//
// PØÍKLAD 18.1: VÝPOÈET FAKTORIÁLU – VSTUPNÍ A VÝSTUPNÍ PODMÍNKY
// Makro assert
//

//  Není-li podmínka splnìna, vypíše toto makro zprávu o chybì
// a ukonèí bìh programu

int faktorial18(int n)
{
    assert(n >= 0);
    int vysledek = 1;
    while (n>1)
    {
        vysledek *= n--;
    }
    assert(vysledek > 0);
    return vysledek;
}

auto vypis_vstupni_a_vystupni_podminky() -> void
{
    // faktorial pøeteèe do záporného tvaru pøi hodnotì 18 pro typ int
    // cout << faktorial18(18) << endl;

//    cout << "faktorial_18_2(" << FAKT_TEST_NR << ") = "
//         << faktorial_18_2(FAKT_TEST_NR) << endl;

//    cout << "faktorial_18_2(" << FAKT_TEST_NR_OUTOR << ") = "
//         << faktorial_18_2(FAKT_TEST_NR_OUTOR) << endl;

    cout << "bezpecny_soucet: " << " = "
         << bezpecny_soucet<long long int>(1234567890123888, -6445645545454545) << endl;

//    cout << "bezpecny_rozdil: " << " = "
//         << bezpecny_rozdil(-1234567890123, 1234567890123) << endl;

//    cout << "bezpecny_soucin: " << " = "
//         << bezpecny_soucin(-1234567890123, 1234567890123) << endl;

//    cout << "bezpecny_podil: " << " = "
//         << bezpecny_podil(5, 0) << endl;

//    cout << "faktorial_18_3(" << FAKT_TEST_NR_OUTOR << ") = "
//         << faktorial_18_3(FAKT_TEST_NR_OUTOR) << endl;

// Poznamenejme, že kdybychom chtìli funkce pro bezpeèné aritmetické operace uložit do knihovny,
// naprogramovali bychom je jako šablony sparametrem pøedstavujícím typ operandù.

}

//
// PØÍKLAD 18.5: BÌH PROGRAMU S VÝJIMKAMI
//

//
// PØÍKLAD 18.4: ZACHYCENÍ VÝJIMKY
//

void vypis_18_4(int od, int po)
{
    for (int i = od; i < po + 1; i++)
    {
        try
        {
            cout << setw(3) << i << ": ";
            cout << setw(11) << faktorial_18_3(i);
            cout << ";" << endl;
        }
        catch (exception &e) // exception je pøedkem invalid_argument, overflow_error a dalších ...
        {
            cout << e.what() << endl;
        }
    }
}

auto vypis_zachyceni_vyjimky() -> void
{
    vypis_18_4(-2, 13);
}

//
// PØÍKLAD 18.6: ÚKLID POMOCÍ DESTRUKTORÙ
//
void zpracuj18_6_1(int *p, int n)
{
    cout << "znak: " << p[0] << " délka: " << n << endl;
}; // Prototyp funkce pro zpracování
void vypis18_6_1(int *p, int n)
{
    cout << "znak: " << p[0] << " délka: " << n << endl;
}; // a výpis pole

void pokus18_6_1(int n)
{
    int *pole = new int[n] {}; // Inicializace nulami
    zpracuj18_6_1(pole, n);
    vypis18_6_1(pole, n);
    delete [] pole;
}

// Kód založený na chytrých ukazatelích mùže vypadat takto:
void zpracuj18_6_2(unique_ptr<int[]> &p, int n)
{
    cout << "znak: " << p[0] << " délka: " << n << endl;
};
void vypis18_6_2(unique_ptr<int[]> &p, int n)
{
    cout << "znak: " << p[0] << " délka: " << n << endl;
};

void pokus18_6_2(int n)
{
    unique_ptr<int[]> pole{ new int[n] {0} };
    zpracuj18_6_2(pole, n);
    vypis18_6_2(pole, n);
}

auto vypis_uklid_pomoci_destruktoru_a_chytre_ukazatele() -> void
{
    pokus18_6_1(100);
    pokus18_6_2(100);
}

//
// PØÍKLAD 18.7: FUNKCE, Z NÍŽ SE NEMÙŽE ROZŠÍØIT VÝJIMKA
//

void vypis_18_7(unique_ptr<int[]> &pole, int n) noexcept(false)
{
    cout << "// PØÍKLAD 18.7: FUNKCE, Z NÍŽ SE NEMÙŽE ROZŠÍØIT VÝJIMKA" << endl;
    for (int i = 0; i < n; i++)
        cout << pole[i] << endl;
}

auto vypis_funkce_z_niz_se_nemuze_sirit_vyjimka() -> void
{
    const int n {5};
    unique_ptr<int[]> pole{ new int[10] {9,8,7,6,5} };
    vypis_18_7(pole, n);
}
