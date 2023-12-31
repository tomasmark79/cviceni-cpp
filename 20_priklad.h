#ifndef PRIKLAD_2_H_INCLUDED
#define PRIKLAD_2_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "20_komparatory.h"

using namespace std;

void nastav_konzolu_pro_cp1250();
void obnov_puvodni_nastaveni_konzoly();
string retezec_Cp1250_na_string_Cp852(const char *text_napovedy_1250);

// Declaration of Class volba
class volba
{
public:
    using u_komparator = bool(*)(string, string); // UKAZATEL na funci
    volba(int argc, char** argv);
    [[noreturn]] void napoveda();
    u_komparator zvoleno(); // get zvoleno

private:
    u_komparator komparator;
    static string text_napovedy;
    static wstring text_napovedy_wide;
};

// Declaration of Class tridic
class tridic
{
    vector<string> soubor;
    string radka;
    void nacti();
    void serad(volba::u_komparator komparator);
    void vypis();
public:
    void zpracuj(volba::u_komparator komparator);
};

#endif // PRIKLAD_2_H_INCLUDED
