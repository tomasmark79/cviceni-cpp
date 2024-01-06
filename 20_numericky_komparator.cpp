#include "20_numericky_komparator.h"
#include <sstream>

bool numericky_komparator::operator()(string lajna1, string lajna2)
{
    istringstream vstup1(lajna1), vstup2(lajna2); // #include <sstream>
    int n1, n2;
    if ((vstup1 >> n1) && (vstup2 >> n2)) {
        return n1 < n2;
    }
    // Ošetøení pøípadu, kdy nelze naèíst èísla
    return lajna1 < lajna2;

}
