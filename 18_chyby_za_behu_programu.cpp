#include <iostream>
#include <assert.h>
#include <limits>
#include "18_chyby_za_behu_programu.h"

using namespace std;

#define FAKT_MAX (int)12
#define FAKT_TEST_NR (int)11
#define FAKT_TEST_NR_OUTOR (int)19

//
// PØÍKLAD 18.3: DETEKCE CELOÈÍSLENÉHO PØETEÈENÍ
//

int bezpecny_soucet(int a, int b)
{
    if ((a > 0) && (b > numeric_limits<int>::max() - a))
    {
        throw overflow_error("Výsledek > INT_MAX");
    }
    if ((a < 0) && (b < numeric_limits<int>::min() + a))
    {
        throw overflow_error("Výsledek < INT_MIN");
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

//    cout << "bezpecny_soucet: " << " = "
//         << bezpecny_soucet(1234567890123, 1234567890123) << endl;

//    cout << "bezpecny_rozdil: " << " = "
//         << bezpecny_rozdil(-1234567890123, 1234567890123) << endl;

//    cout << "bezpecny_soucin: " << " = "
//         << bezpecny_soucin(-1234567890123, 1234567890123) << endl;

//    cout << "bezpecny_podil: " << " = "
//         << bezpecny_podil(5, 0) << endl;

    cout << "faktorial_18_3(" << FAKT_TEST_NR_OUTOR << ") = "
         << faktorial_18_3(FAKT_TEST_NR_OUTOR) << endl;

// Poznamenejme, že kdybychom chtìli funkce pro bezpeèné aritmetické operace uložit do knihovny,
// naprogramovali bychom je jako šablony sparametrem pøedstavujícím typ operandù.

}
