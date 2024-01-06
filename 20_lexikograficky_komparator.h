#ifndef LEXIKOGRAFICKY_KOMPARATOR_H_INCLUDED
#define LEXIKOGRAFICKY_KOMPARATOR_H_INCLUDED
#include "20_komparatory.h"

class lexikograficky_komparator : public komparator
{
public:
    lexikograficky_komparator() {}
    virtual bool operator()(string lajna1, string lajna2) override;
};



#endif // LEXIKOGRAFICKY_KOMPARATOR_H_INCLUDED
