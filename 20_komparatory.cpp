#include "20_komparatory.h"

bool podle_cisel(string lajna1, string lajna2)
{
    istringstream vstup1(lajna1), vstup2(lajna2); // #include <sstream>
    int n1, n2;
    vstup1 >> n1;
    vstup2 >> n2;
    return n1 < n2;
}
