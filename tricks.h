#ifndef TRICKS_H_INCLUDED
#define TRICKS_H_INCLUDED
#include <iostream>
#include <algorithm>

using namespace std;

// -----------------------------------------------------------------|
//                                                                  |
// Z�sk�n� po�tu prvk� z pole
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
// Zp�ehledn�n� knihovn� funkce pomoc� inicializace konstruktoru
//                                                                  |
// -----------------------------------------------------------------|
auto clarityOfCode001() -> void;

// -----------------------------------------------------------------|
//                                                                  |
// Oper�tor New a Delete
//                                                                  |
// -----------------------------------------------------------------|
auto operatorNew_Whoops() -> void;
class operator_new_a_delete_informace
{

public:
    operator_new_a_delete_informace() {};
    ~operator_new_a_delete_informace() {};

// standardn� oper�tor new z knihovny nikdy nevr�t� nullptr
// v p��pad�, �e neusp�je s alokac�, vyvol� vyj�mku!

// 1. nechat vyj�mku bez obsluhy a syst�m se postar� o �klid
// 2. obslou�it vyj�mku - z�lohov�n� na posl. operaci

    // p�et�en�
    void * operator new(std::size_t sz)
    {
        cout << "p�et�en� oper�toru new - uvnit� t��dy" << " ";
        // avoid std::malloc(0) kter�
        // m� vracet nullptr p�i �sp�chu
        if (sz == 0)
            ++sz;

        if (void *ptr = std::malloc(sz))
            return ptr;

        throw std::bad_alloc{}; // required by [new.delete.single]/3
    }

    // p�et�en�
    void * operator new[](std::size_t sz)
    {
        cout << "p�et�en� oper�toru new[] - uvnit� t��dy" << " ";
        // avoid std::malloc(0) kter�
        // m� vracet nullptr p�i �sp�chu
        if (sz == 0)
            ++sz;

        if (void *ptr = std::malloc(sz))
            return ptr;

        throw std::bad_alloc{}; // required by [new.delete.single]/3
    }

    // p�et�en�
    void operator delete (void *ptr) noexcept
    {
        cout << "p�et�en� oper�toru delete - uvnit� t��dy" << endl;
        std::free(ptr);
    }

    // p�et�en�
    void operator delete[](void* ptr) noexcept
    {
        cout << "p�et�en� oper�toru delete[] - uvnit� t��dy" << endl;
        std::free(ptr);
    }
};


// -----------------------------------------------------------------|
//                                                                  |
//
//                                                                  |
// -----------------------------------------------------------------|







#endif // TRICKS_H_INCLUDED
