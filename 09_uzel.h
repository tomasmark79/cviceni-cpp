#ifndef UZEL_H_INCLUDED
#define UZEL_H_INCLUDED

#include <string>
using namespace std;

/*
class uzel
{
public:
    string znak; // rozlišovací znak, nebo hledané zvíøe
    bool otazka; // true je otázka, false je odpovìï
    uzel *ma, *nema; // ukazatele pro pøechod k rozl. uzlu nebo k odpovìdi

    uzel(string _znak, bool _otazka, uzel *_ma, uzel *_nema)
    {
        znak = _znak;
        otazka = _otazka;
        ma = _ma;
        nema = _nema;
    }
};
*/

// tato struktura nahradila tøídu uzel
/*
Konstruktor je zbyteènı, nebo stejného vısledku dosáhneme inicializací struktury. Upravíme-li takto deklaraci typu
uzel, nic se nezmìní, zbytek programu není tøeba mìnit
*/

struct uzel
{
    string znak;
    bool otazka;
    uzel *ma, *nema;
};


#endif // UZEL_H_INCLUDED
