#include <iostream>
#include "15_preprocesor.h"

using namespace std;

//místo #if defined jméno mùžeme psát #ifdef jméno,
//místo #if !defined jméno mùžeme psát #ifndef jméno.


//
// PØÍKLAD 15.8: VYVOLÁNÍ CHYBY
//

#ifndef __cplusplus
#error Pro pøeklad souboru xyz.h je tøeba C++
#endif

//
// PØÍKLAD 15.7: LADICÍ TISK POTØETÍ
//
// Makro pro ladicí tisk, které jsme definovali vpøíkladu 15.4,
// mùžeme svyužitím syntaktické zkratky pøepsat do tvaru:
#define LADIM

#ifdef LADIM
#define TISK(x) cout << #x << " = " << x << endl
#else
#define TISK(x) void(0)
#endif

//
// PØÍKLAD 15.6: DOÈASNÌ ODSTRANÌNÍ ÈÁSTI ZDROJOVÉHO KÓDU
//

#if 0
blablablabla preprocesor tento text vyøadí :-)
#endif


//
// PØÍKLAD 15.5: OCHRANA PØED OPAKOVANÝM ÈTENÍM
//
#if !defined __JMENO_H__
#define __JMENO_H__
// zde je vlastní obsah hlavièkového souboru
#endif

// #define LADIM
//
// PØÍKLAD 15.4: LADICÍ TISK JEŠTÌ JEDNOU
//
#if 0
#if defined LADIM
 #define TISK(x) cout << #x << " = " << x << endl
#else
 #define TISK(x) void(0)
#endif
#endif
//
// PØÍKLAD 15.3: MAKRO PRO LADICÍ TISK
//

// #define TISK(x) cout << #x << " = " << x << endl
// pokraèování výše

//
// PØÍKLAD 15.2: VÝPOÈET DRUHÉ MOCNINY A PROBLÉMY S MAKRY
//
// makra s parametry jsou dìdictvím po jazyce C; v C++ se jim spíše vyhýbáme.

// šablona funkce pro výpoèet druhé mocniny pro rùzné typy
template<typename T> T sqr(T x)
{
    return x*x;
}

auto vypis_druhou_mocninu_makrem() -> void
{
    int i{8};
    double x{8.1};
    cout << endl;
    // makra s parametry jsou dìdictvím po jazyce C; v C++ se jim spíše vyhýbáme.
#define SQR(x) x*x
    cout << "SQR(i): " << SQR(i) << endl;
    cout << "SQR(x): " << SQR(x) << endl;
    cout << "SQR(i+1): #define SQR(x) x*x: " << SQR(i+1) << endl; // i + 1*i + 1 by macro seen
#undef SQR


#define SQR(x) ((x)*(x)) // Korekce - formální parametry vždy uzávorkovat vè. celého výrazu
    cout << "SQR(i+1): #define SQR(x) ((x)*(x)): " << SQR(i+1) << " i: " << i << endl;
    // vyhýbat se tìmto výskytùm - mùže se mìnit dle architektury
    cout << "SQR(i++): " << SQR(i++) << " i: " << i <<  " WRONG RESULT" << endl << endl; // 72 - 9x8 // použije i++ * i++ - vyhýbat se tìmto výskytùm

    cout << "sqr(i++): " << sqr(i++) << " i: " << i << " OK" << endl; // použita funkce šablony

    cout << "__LINE__: " <<__LINE__ << endl;
    cout << "__DATE__: " <<__DATE__ << endl;
    cout << "__TIME__: " <<__TIME__ << endl;
    cout << "__FILE__: " <<__FILE__ << endl;
    cout << "__cplusplus: " <<__cplusplus << endl;


#undef SQR


    TISK(i);
    TISK(x);
}

//
// PØÍKLAD 15.1: MANIFESTAÈNÍ KONSTANTY
//
#define N 100
auto vypis_manifestacni_konstanty() -> void
{
    int A[N] {1,3,6,8,2}; // Použití manifestaèní konstanty

    for(int i = 0; i < N; i++)
    {
        cout << A[i] << " " ;
    }
    cout << endl;
}
