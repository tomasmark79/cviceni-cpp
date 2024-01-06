#ifndef INICIALIZACE_H_INCLUDED
#define INICIALIZACE_H_INCLUDED
#include <unordered_map>
#include <string>

using namespace std;

extern unordered_map<char, char> mala_na_velka;
extern unordered_map<char, char> slozena_pismena;
extern unordered_map< string, pair<string, char>> uprava;



class ini_soubor
{
    string jmeno_souboru;
    bool novy_usek(string text);
    bool najdi_usek(ifstream& proud, string zahlavi);
    void priprava(ifstream& proud, string jmeno_useku);
    static string text_chyby[];
public:
    ini_soubor(string jmeno);
    void nacti_dvojice_znaku(string zahlavi,
                             unordered_map<char, char>& mapa);
    void nacti_trojice(string zahlavi,
                  unordered_map<string, pair<string, char>>& mapa);
    void nacti_text(string zahlavi, string &text);
    void inicializace_abecedniho_razeni(
        unordered_map<char, char>& mala_na_velka,
        unordered_map<char, char>& slozena_pismena,
        unordered_map<string, pair<string, char>>& uprava);
};

// informativní deklarace k umožnìní pøístupu z venku
extern ini_soubor inicializator;

#endif // INICIALIZACE_H_INCLUDED
