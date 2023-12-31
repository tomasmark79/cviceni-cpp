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
    // výètový typ
    // enum zvoleno_t { lexikograficky, numericky }; // odebráno v 20.4.1
    using u_komparator = bool(*)(string, string);

    // dostane parametry main
    volba(int argc, char** argv);

    // ukonèí program
    [[noreturn]] void napoveda();

    // zvoleno_t zvoleno(); // odebráno v 20.4.1
    u_komparator zvoleno();

private:
    u_komparator komparator;
    // zvoleno_t zjistena_volba; // odebráno v 20.4.1
    static string text_napovedy;
    static wstring text_napovedy_wide;
};
// Declaration of Class tridic
class tridic
{
    vector<string> soubor;
    string radka;
    void nacti();
    void serad(volba::zvoleno_t zvoleno);
    void vypis();
public:
    void zpracuj(volba::zvoleno_t zvoleno);
    void zpracuj2(volba::zvoleno_t zvoleno);
};

#endif // PRIKLAD_2_H_INCLUDED
