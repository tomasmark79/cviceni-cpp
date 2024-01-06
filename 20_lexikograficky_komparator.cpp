#include "20_lexikograficky_komparator.h"

bool lexikograficky_komparator::operator()(string lajna1, string lajna2)
{
    return lajna1 < lajna2;
}
