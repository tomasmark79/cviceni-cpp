#ifndef UZEL_H_INCLUDED
#define UZEL_H_INCLUDED

#include <string>
using namespace std;

/*
class uzel
{
public:
    string znak; // rozli�ovac� znak, nebo hledan� zv��e
    bool otazka; // true je ot�zka, false je odpov��
    uzel *ma, *nema; // ukazatele pro p�echod k rozl. uzlu nebo k odpov�di

    uzel(string _znak, bool _otazka, uzel *_ma, uzel *_nema)
    {
        znak = _znak;
        otazka = _otazka;
        ma = _ma;
        nema = _nema;
    }
};
*/

// tato struktura nahradila t��du uzel
/*
Konstruktor je zbyte�n�, nebo� stejn�ho v�sledku dos�hneme inicializac� struktury. Uprav�me-li takto deklaraci typu
uzel, nic se nezm�n�, zbytek programu nen� t�eba m�nit
*/

struct uzel
{
    string znak;
    bool otazka;
    uzel *ma, *nema;
};


#endif // UZEL_H_INCLUDED
