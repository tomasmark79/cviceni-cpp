#include "tricks.h"

using namespace std;
// -----------------------------------------------------------------|
//                                                                  |
// Z�sk�n� po�tu prvk� z pole
//                                                                  |
// -----------------------------------------------------------------|
auto getCountOfElements() -> void
{
    int a[] = {1,2,3,4,5,6,7,8,9};
    cout << ARRAYSIZEM(a) << endl;
    cout << ARRAYSIZET(a) << endl;
}

// -----------------------------------------------------------------|
//                                                                  |
// Zp�ehledn�n� knihovn� funkce pomoc� inicializace konstruktoru
//                                                                  |
// -----------------------------------------------------------------|
auto clarityOfCode001() -> void
{
    int a{},b{},c{},d{},e{};

    // unclarity #include <algorithm>
    int x1 = min(a,
                 min(b,
                     min(c,
                         min (d, e))));

    // clarity #include <algorithm>
    int x2 = min( { a, b, c, d, e } );
}


// -----------------------------------------------------------------|
//                                                                  |
// Oper�tor New a Delete
//                                                                  |
// -----------------------------------------------------------------|
// p�et�en� operatoru new[] mimo t��du - je to kopie origin�ln� �ablony
void * operator new[](size_t size)
{
        cout << "p�et�en� oper�toru new[] - mimo t��du" << " ";
        // avoid std::malloc(0) kter�
        // m� vracet nullptr p�i �sp�chu
        if (size == 0)
            ++size;

        if (void *ptr = std::malloc(size))
            return ptr;

        throw std::bad_alloc{}; // required by [new.delete.single]/3
}

// informace o operatorech new a delete
auto operatorNew_Whoops() -> void
{
    // uk�zka p�et�en� oper�tor� NEW a DELETE
    for (int i{0};i<4;i++)
    {
        operator_new_a_delete_informace *p1 =
            new operator_new_a_delete_informace [100000000ul];

        if (p1 == nullptr)
        {
            cout << endl << "Alokace vr�tila nullptr" << endl;
            break;
        }
        // delete[] p1;
    }

    // knihovn� otestov�n� alok�toru oper�toru NEW
    try
    {
        while (true)
        {
            new int [100000000ul];
        }
    }
    catch (const bad_alloc& e)
    {
        cout << endl << "Alokace vr�tila vyj�mku: " << e.what() << " ";
    }

    // vs //
    // bez vyj�mkov� otestov�n� alok�toru oper�toru NEW
    while (true)
    {
        // Non-throwing version of new
        int * p = new(nothrow) int[100000000ul];
        if (p==nullptr)
        {
            cout << endl << "Alokace vr�tila nullptr" << endl;
            break;
        }
    }
}

// -----------------------------------------------------------------|
//                                                                  |
// placement new
//                                                                  |
// -----------------------------------------------------------------|
// nechceme replikovat sami proto�e je to dlouh� cesta p�es n�sl. vol�n�
    // virtual base classes
    // non-virtual base classes
    // class members
    // class constructor

// proto takto je to ide�ln� implementace
auto konstrukce_pameti_na_rychlejsim_hw_chipu() -> void
{
    // buffer na z�sobn�ku - co� je ultra rychl� pam�
    unsigned char buf[sizeof(int)*3];

    // nov� ukazatel na um�st�n� v buf o velikosti 3 prvk�
    int *pInt = new (buf)int(3);

    pInt[0] = 0;
    pInt[1] = 1;
    pInt[2] = 2;

    delete pInt;
}


// -----------------------------------------------------------------|
//                                                                  |
//
//                                                                  |
// -----------------------------------------------------------------|









