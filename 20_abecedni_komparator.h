#ifndef ABECEDNI_KOMPARATOR_H_INCLUDED
#define ABECEDNI_KOMPARATOR_H_INCLUDED

#include "20_komparatory.h"
#include "20_inicializace.h"
#include <unordered_map>
#include <string>

class abecedni_komparator : public komparator
{
    unordered_map<char, char> mala_na_velka;
    unordered_map< string, pair<string, char>> uprava;
    unordered_map<char, char> slozena_pismena;
    char velke(char znak);
    string velke(string text);
    string zastup(string text);
public:
    abecedni_komparator();
    virtual bool operator()(string lajna1, string lajna2);
};


#endif // ABECEDNI_KOMPARATOR_H_INCLUDED
