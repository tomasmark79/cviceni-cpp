#include "tricks.h"

using namespace std;
// -----------------------------------------------------------------|
//                                                                  |
// Získání poètu prvkù z pole
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
// Zpøehlednìní knihovní funkce pomocí inicializace konstruktoru
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
// Operátor New a Delete
//                                                                  |
// -----------------------------------------------------------------|
// pøetíení operatoru new[] mimo tøídu - je to kopie originální šablony
void * operator new[](size_t size)
{
        cout << "pøetíení operátoru new[] - mimo tøídu" << " ";
        // avoid std::malloc(0) kterı
        // má vracet nullptr pøi úspìchu
        if (size == 0)
            ++size;

        if (void *ptr = std::malloc(size))
            return ptr;

        throw std::bad_alloc{}; // required by [new.delete.single]/3
}

// informace o operatorech new a delete
auto operatorNew_Whoops() -> void
{
    // ukázka pøetíení operátorù NEW a DELETE
    for (int i{0};i<4;i++)
    {
        operator_new_a_delete_informace *p1 =
            new operator_new_a_delete_informace [100000000ul];

        if (p1 == nullptr)
        {
            cout << endl << "Alokace vrátila nullptr" << endl;
            break;
        }
        // delete[] p1;
    }

    // knihovní otestování alokátoru operátoru NEW
    try
    {
        while (true)
        {
            new int [100000000ul];
        }
    }
    catch (const bad_alloc& e)
    {
        cout << endl << "Alokace vrátila vyjímku: " << e.what() << " ";
    }

    // vs //
    // bez vyjímkové otestování alokátoru operátoru NEW
    while (true)
    {
        // Non-throwing version of new
        int * p = new(nothrow) int[100000000ul];
        if (p==nullptr)
        {
            cout << endl << "Alokace vrátila nullptr" << endl;
            break;
        }
    }
}

// -----------------------------------------------------------------|
//                                                                  |
// placement new
//                                                                  |
// -----------------------------------------------------------------|
// nechceme replikovat sami protoe je to dlouhá cesta pøes násl. volání
    // virtual base classes
    // non-virtual base classes
    // class members
    // class constructor

// proto takto je to ideální implementace
auto konstrukce_pameti_na_rychlejsim_hw_chipu() -> void
{
    // buffer na zásobníku - co je ultra rychlá pamì
    unsigned char buf[sizeof(int)*3];

    // novı ukazatel na umístìní v buf o velikosti 3 prvkù
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









