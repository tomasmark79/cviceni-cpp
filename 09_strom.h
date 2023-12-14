#ifndef STROM_H_INCLUDED
#define STROM_H_INCLUDED
#include "09_uzel.h"

using namespace std;

class strom
{
public:
    strom();
    ~strom();
    string hledej();
    void vyprazdni();
    void pridej_zvire();
private:
    uzel *koren /*výchozí*/ , *aktualni /*s ním se pracuje*/;
    void vyprazdni(uzel * koren);
};

int hraj_hru_hadej_zvire();

#endif // STROM_H_INCLUDED
