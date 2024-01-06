#ifndef NUMERICKY_KOMPARATOR_H_INCLUDED
#define NUMERICKY_KOMPARATOR_H_INCLUDED
#include "20_komparatory.h"

class numericky_komparator : public komparator
{
public:
    numericky_komparator() {}
    virtual bool operator()(string lajna1, string lajna2) override;
};

#endif // NUMERICKY_KOMPARATOR_H_INCLUDED
