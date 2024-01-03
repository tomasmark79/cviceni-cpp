#ifndef PRIKLAD_WIDE_H_INCLUDED
#define PRIKLAD_WIDE_H_INCLUDED

#include "20_komparatory.h"

using namespace std;

class wvolba
{
public:
    using wu_komparator = bool(*)(wstring, wstring); // UKAZATEL na funci
    wvolba(int argc, wchar_t *argv[]);

    [[noreturn]] void wnapoveda();
    wu_komparator wzvoleno(); // get zvoleno

private:
    static map<wstring, wu_komparator> wtabulka_voleb;
    wu_komparator wkomparator;
    static wstring text_napovedy_wide;
    static wstring text_napovedy_uk;
};

class wtridic
{
    vector<wstring> wsoubor;
    wstring wradka;

    void wnacti();
    void wserad(wvolba::wu_komparator wkomparator);
    void wvypis();

public:
    void wzpracuj(wvolba::wu_komparator wkomparator);
};



#endif // PRIKLAD_WIDE_H_INCLUDED
