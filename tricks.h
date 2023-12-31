#ifndef TRICKS_H_INCLUDED
#define TRICKS_H_INCLUDED
#include <iostream>
#include <algorithm>

using namespace std;

// -----------------------------------------------------------------|
//                                                                  |
// Získání poètu prvkù z pole
//                                                                  |
// -----------------------------------------------------------------|



#define ARRAYSIZEM(b) (sizeof(b)/sizeof(b[0]))
auto getCountOfElements() -> void;
template<typename T, size_t N>
size_t ARRAYSIZET(T (&a)[N])
{
    return N;
}

// -----------------------------------------------------------------|
//                                                                  |
// Zpøehlednìní knihovní funkce pomocí inicializace konstruktoru
//                                                                  |
// -----------------------------------------------------------------|
auto clarityOfCode001() -> void;

// -----------------------------------------------------------------|
//                                                                  |
// Operátor New a Delete
//                                                                  |
// -----------------------------------------------------------------|
auto operatorNew_Whoops() -> void;
class operator_new_a_delete_informace
{

public:
    operator_new_a_delete_informace() {};
    ~operator_new_a_delete_informace() {};

// standardní operátor new z knihovny nikdy nevrátí nullptr
// v pøípadì, že neuspìje s alokací, vyvolá vyjímku!

// 1. nechat vyjímku bez obsluhy a systém se postará o úklid
// 2. obsloužit vyjímku - zálohování na posl. operaci

    // pøetížení
    void * operator new(std::size_t sz)
    {
        cout << "pøetížení operátoru new - uvnitø tøídy" << " ";
        // avoid std::malloc(0) který
        // má vracet nullptr pøi úspìchu
        if (sz == 0)
            ++sz;

        if (void *ptr = std::malloc(sz))
            return ptr;

        throw std::bad_alloc{}; // required by [new.delete.single]/3
    }

    // pøetížení
    void * operator new[](std::size_t sz)
    {
        cout << "pøetížení operátoru new[] - uvnitø tøídy" << " ";
        // avoid std::malloc(0) který
        // má vracet nullptr pøi úspìchu
        if (sz == 0)
            ++sz;

        if (void *ptr = std::malloc(sz))
            return ptr;

        throw std::bad_alloc{}; // required by [new.delete.single]/3
    }

    // pøetížení
    void operator delete (void *ptr) noexcept
    {
        cout << "pøetížení operátoru delete - uvnitø tøídy" << endl;
        std::free(ptr);
    }

    // pøetížení
    void operator delete[](void* ptr) noexcept
    {
        cout << "pøetížení operátoru delete[] - uvnitø tøídy" << endl;
        std::free(ptr);
    }
};


// -----------------------------------------------------------------|
//                                                                  |
//
//                                                                  |
// -----------------------------------------------------------------|







#endif // TRICKS_H_INCLUDED
