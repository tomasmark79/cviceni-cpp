#include "20_inicializace.h"
#include "20_priklad.h"
#include <iostream>
#include <fstream>
#include <sstream>



using namespace std;

void ini_soubor::inicializace_abecedniho_razeni(
    unordered_map<char, char> & mala_na_velka,
    unordered_map<char, char> & slozena_pismena,
    unordered_map< string, pair<string, char>> & uprava)
{
    try
    {
        unordered_map< string, pair<string, char>> uprava_pom;
        unordered_map<char, char> mala_na_velka_pom;
        unordered_map<char, char> slozena_pismena_pom;
        nacti_dvojice_znaku("[mal·-na-velk·]", mala_na_velka_pom);
        nacti_dvojice_znaku("[sloûen·-pÌsmena]", slozena_pismena_pom);
        nacti_trojice("[˙prava]", uprava_pom);
        mala_na_velka = mala_na_velka_pom;
        slozena_pismena = slozena_pismena_pom;
        uprava = uprava_pom;
        uprava.insert({ " ",{ " ", ' ' } });
    }
    catch (runtime_error e)
    {
        cerr << e.what() << endl
             << string_Cp1250_na_string_Cp852(
                 "Bude pouûito v˝chozÌ nastavenÌ") << endl;
    }
}

ini_soubor::ini_soubor(string jmeno)
    :jmeno_souboru(jmeno)
{
    inicializace_abecedniho_razeni(mala_na_velka, slozena_pismena, uprava);
}

string ini_soubor::text_chyby[]
{
    "Nepoda¯ilo se otev¯Ìt soubor s daty!", "Nepoda¯ilo se najÌt ˙sek "
};

bool ini_soubor::najdi_usek(ifstream &proud, string zahlavi)
{
    string slovo;
    while (proud >> slovo && slovo != zahlavi)
        ;
    return slovo == zahlavi;
}

void ini_soubor::priprava(ifstream &proud, string jmeno_useku)
{
    if (!proud)
        throw runtime_error(text_chyby[0]);
    if (!najdi_usek(proud, jmeno_useku))
        throw runtime_error(text_chyby[1] + jmeno_useku);
    proud >> ws; // Discards leading whitespace from an input stream.
}

void ini_soubor::nacti_dvojice_znaku(string zahlavi,
                                     unordered_map<char, char>& mapa)
{
    ifstream proud(jmeno_souboru);
    priprava(proud, zahlavi); // nastavÌ "kurzor" ËtenÌ
    string lajna;
    char prvni, druhy;
    while (getline(proud, lajna))
    {
        istringstream vstup(lajna);
        vstup >> prvni;
        if (prvni == '[') break;
        vstup >> druhy;
        mapa.insert({ prvni, druhy });
    }
    proud.close();
}

void ini_soubor::nacti_trojice(string zahlavi,
                               unordered_map<string, pair<string, char>>& mapa)
{
    ifstream proud(jmeno_souboru);
    priprava(proud, zahlavi);
    string lajna;
    string prvni, druhy;
    char treti;
    while (getline(proud, lajna))
    {
        istringstream vstup(lajna);
        vstup >> prvni;
        if (prvni[0] == '[') break;
        vstup >> druhy >> treti;
        mapa.insert({ prvni,{ druhy, treti } });
    }
    proud.close();
}

bool ini_soubor::novy_usek(string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        if ((text[i] != ' ') && (text[i] != '\t'))
        {
            return text[i] == '['; // return true if exisrt [ (bool)
        }
    }
    return false;
}

void ini_soubor::nacti_text(string zahlavi, string &text)
{
    ifstream proud(jmeno_souboru);
    priprava(proud, zahlavi);
    string lajna;
    text.clear();
    while (getline(proud, lajna))
    {
        if (novy_usek(lajna)) break;
        text += lajna + '\n';
    }
    proud.close();
}

unordered_map<char, char> mala_na_velka
{
    { '·', '¡' },
    { '‰', 'ƒ' },
    { 'Ë', '»' },
    { 'Ô', 'œ' },
    { 'È', '…' },
    { 'Ï', 'Ã' },
    { 'Ì', 'Õ' },
    { 'Â', '≈' },
    { 'æ', 'º' },
    { 'Ú', '“' },
    { 'Û', '”' },
    { 'Ù', '‘' },
    { '‡', '¿' },
    { '¯', 'ÿ' },
    { 'ö', 'ä' },
    { 'ù', 'ç' },
    { '˙', '⁄' },
    { '˘', 'Ÿ' },
    { '˝', '›' },
    { 'û', 'é' },
};
unordered_map< string, pair<string, char>> uprava
{
    { "A",{ "Aa", 'a' } },
    { "¡",{ "Aa", 'b' } },
    { "ƒ",{ "Aa", 'e' } },
    { "B",{ "Ba", 'a' } },
    { "C",{ "Ca", 'a' } },
    { "»",{ "Cb", 'a' } },
    { "D",{ "Da", 'a' } },
    { "œ",{ "Da", 'b' } },
    { "E",{ "Ea", 'a' } },
    { "…",{ "Ea", 'b' } },
    { "Ã",{ "Ea", 'c' } },
    { "F",{ "Fa", 'a' } },
    { "G",{ "Ga", 'a' } },
    { "H",{ "Ha", 'a' } },
    { "CH",{ "Hb", 'a' } },
    { "I",{ "Ia", 'a' } },
    { "Õ",{ "Ia", 'b' } },
    { "J",{ "Ja", 'a' } },
    { "K",{ "Ka", 'a' } },
    { "L",{ "La", 'a' } },
    { "≈",{ "La", 'b' } },
    { "º",{ "La", 'c' } },
    { "M",{ "Ma", 'a' } },
    { "N",{ "Na", 'a' } },
    { "“",{ "Na", 'b' } },
    { "O",{ "Oa", 'a' } },
    { "”",{ "Oa", 'b' } },
    { "‘",{ "Oa", 'f' } },
    { "P",{ "Pa", 'a' } },
    { "Q",{ "Qa", 'a' } },
    { "R",{ "Ra", 'a' } },
    { "¿",{ "Ra", 'b' } },
    { "ÿ",{ "Rb", 'a' } },
    { "S",{ "Sa", 'a' } },
    { "ä",{ "Sb", 'a' } },
    { "T",{ "Ta", 'a' } },
    { "ç",{ "Ta", 'b' } },
    { "U",{ "Ua", 'a' } },
    { "⁄",{ "Ua", 'b' } },
    { "Ÿ",{ "Ua", 'd' } },
    { "V",{ "Va", 'a' } },
    { "W",{ "Wa", 'a' } },
    { "X",{ "Xa", 'a' } },
    { "Y",{ "Ya", 'a' } },
    { "›",{ "Ya", 'b' } },
    { "Z",{ "Za", 'a' } },
    { "é",{ "Zb", 'a' } },
    { " ",{ " ", ' ' } },
};

unordered_map<char, char> slozena_pismena
{
    {'C', 'H'},
};

// glob·lnÌ ninicializace instance
ini_soubor inicializator("c:\\Projects\\_GitProjects\\Invisiwind\\Build\\bin\\Debug\\inicializace.txt");
