#include <iostream>
#include "15_preprocesor.h"

using namespace std;

//m�sto #if defined jm�no m��eme ps�t #ifdef jm�no,
//m�sto #if !defined jm�no m��eme ps�t #ifndef jm�no.


//
// P��KLAD 15.8: VYVOL�N� CHYBY
//

#ifndef __cplusplus
#error Pro p�eklad souboru xyz.h je t�eba C++
#endif

//
// P��KLAD 15.7: LADIC� TISK POT�ET�
//
// Makro pro ladic� tisk, kter� jsme definovali vp��kladu 15.4,
// m��eme svyu�it�m syntaktick� zkratky p�epsat do tvaru:
#define LADIM

#ifdef LADIM
#define TISK(x) cout << #x << " = " << x << endl
#else
#define TISK(x) void(0)
#endif

//
// P��KLAD 15.6: DO�ASN� ODSTRAN�N� ��STI ZDROJOV�HO K�DU
//

#if 0
blablablabla preprocesor tento text vy�ad� :-)
#endif


//
// P��KLAD 15.5: OCHRANA P�ED OPAKOVAN�M �TEN�M
//
#if !defined __JMENO_H__
#define __JMENO_H__
// zde je vlastn� obsah hlavi�kov�ho souboru
#endif

// #define LADIM
//
// P��KLAD 15.4: LADIC� TISK JE�T� JEDNOU
//
#if 0
#if defined LADIM
 #define TISK(x) cout << #x << " = " << x << endl
#else
 #define TISK(x) void(0)
#endif
#endif
//
// P��KLAD 15.3: MAKRO PRO LADIC� TISK
//

// #define TISK(x) cout << #x << " = " << x << endl
// pokra�ov�n� v��e

//
// P��KLAD 15.2: V�PO�ET DRUH� MOCNINY A PROBL�MY S MAKRY
//
// makra s parametry jsou d�dictv�m po jazyce C; v C++ se jim sp�e vyh�b�me.

// �ablona funkce pro v�po�et druh� mocniny pro r�zn� typy
template<typename T> T sqr(T x)
{
    return x*x;
}

auto vypis_druhou_mocninu_makrem() -> void
{
    int i{8};
    double x{8.1};
    cout << endl;
    // makra s parametry jsou d�dictv�m po jazyce C; v C++ se jim sp�e vyh�b�me.
#define SQR(x) x*x
    cout << "SQR(i): " << SQR(i) << endl;
    cout << "SQR(x): " << SQR(x) << endl;
    cout << "SQR(i+1): #define SQR(x) x*x: " << SQR(i+1) << endl; // i + 1*i + 1 by macro seen
#undef SQR


#define SQR(x) ((x)*(x)) // Korekce - form�ln� parametry v�dy uz�vorkovat v�. cel�ho v�razu
    cout << "SQR(i+1): #define SQR(x) ((x)*(x)): " << SQR(i+1) << " i: " << i << endl;
    // vyh�bat se t�mto v�skyt�m - m��e se m�nit dle architektury
    cout << "SQR(i++): " << SQR(i++) << " i: " << i <<  " WRONG RESULT" << endl << endl; // 72 - 9x8 // pou�ije i++ * i++ - vyh�bat se t�mto v�skyt�m

    cout << "sqr(i++): " << sqr(i++) << " i: " << i << " OK" << endl; // pou�ita funkce �ablony

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
// P��KLAD 15.1: MANIFESTA�N� KONSTANTY
//
#define N 100
auto vypis_manifestacni_konstanty() -> void
{
    int A[N] {1,3,6,8,2}; // Pou�it� manifesta�n� konstanty

    for(int i = 0; i < N; i++)
    {
        cout << A[i] << " " ;
    }
    cout << endl;
}
