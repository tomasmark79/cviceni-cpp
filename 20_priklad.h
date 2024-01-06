#ifndef PRIKLAD_2_H_INCLUDED
#define PRIKLAD_2_H_INCLUDED

//#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
//#include <fstream>
//#include <sstream>
#include <map>
//#include <unordered_map>
//#include <math.h>

using namespace std;

void nastav_rastr_cascadia();
void nastav_konzolu_pro_cp1250();
void obnov_puvodni_nastaveni_konzoly();
string retezec_Cp1250_na_string_Cp852(const char *text_napovedy_1250);
string string_Cp1250_na_string_Cp852( string text_1250 );
void printf_locale_vystup();

// Declaration of Class volba
class volba
{
public:
    using u_komparator = bool(*)(string, string); // UKAZATEL na funci
    volba(int argc, char** argv);

    [[noreturn]] void napoveda();
    u_komparator zvoleno(); // get zvoleno
    void nacti_napovedu();

private:
    static map<string, u_komparator> tabulka_voleb;
    u_komparator komparator;
    static string zalozni_text_napovedy;
    ;
    static string text_napovedy_v_852;
    static string text_napovedy_cz;
    string text_napovedy;
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
