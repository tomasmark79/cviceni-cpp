#ifndef ZAKLADNI_DATOVE_TYPY_H_INCLUDED
#define ZAKLADNI_DATOVE_TYPY_H_INCLUDED

#include <iostream>

char prevod_na_velke_znaky(char c);
std::string binarizuj(int m);
int vypis_zaokrouhlovaci_chyby();
void vypis_zaokrouhlovaci_priklady();
int vypis_plochy_a_obvodu_trojuhelnika();

class bod06
{
    double x, y;
    void set_x(double _x)
    {
        x = _x;
    }
    void set_y(double _y)
    {
        y = _y;
    }

public:
//    bod06(double _x, double _y); // constructor
//    {
//        x = _x;
//        y = _y;
//    }
//  bod06(double _x, double _y) : x(_x), y(_y) {}
    bod06(double _x, double _y)
    {
        set_x(_x);
        set_y(_y);
    }

    friend double vzdalenost(bod06 A, bod06 B);
};

// sablony normalne patri do hlavickovych souboru
template<typename T>
T maximum(T a, T b)
{
    return a > b ? a : b;
}

template<typename A>
A minimum(A a, A b)
{
    return a < b ? a : b;
}

void vypis_minimummaximum();

#endif // ZAKLADNI_DATOVE_TYPY_H_INCLUDED
