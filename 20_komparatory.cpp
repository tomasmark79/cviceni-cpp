#include "20_komparatory.h"
#include <unordered_map>
#include <sstream>

using namespace std;

// locale lok("Czech_Czech Republic.1250"); // nelze s G++ compilatorem
// Jestlie k pøekladu poslední verze našeho programu pouijete pøekladaè g++
// a spustíte program s volbou pro abecední øazení, skonèí vıjimkou, nebo – jak víme
// – tento pøekladaè pod Windows podporuje pouze lokální nastavení "C".
// To znamená, e si musíme napsat odpovídající nástroje samy :-).

std::locale lok(""); // toto je však OK

map <char, char> slozena_pismena
{
    {'C', 'H'},
};

unordered_map<char, char> mala_na_velka
{
    { 'á', 'Á' },
    { 'ä', 'Ä' },
    { 'è', 'È' },
    { 'ï', 'Ï' },
    { 'é', 'É' },
    { 'ì', 'Ì' },
    { 'í', 'Í' },
    { 'å', 'Å' },
    { '¾', '¼' },
    { 'ò', 'Ò' },
    { 'ó', 'Ó' },
    { 'ô', 'Ô' },
    { 'à', 'À' },
    { 'ø', 'Ø' },
    { 'š', 'Š' },
    { '', '' },
    { 'ú', 'Ú' },
    { 'ù', 'Ù' },
    { 'ı', 'İ' },
    { '', '' },
};
static unordered_map< string, pair<string, char>> uprava
{
    { "A",{ "Aa", 'a' } },
    { "Á",{ "Aa", 'b' } },
    { "Ä",{ "Aa", 'e' } },
    { "B",{ "Ba", 'a' } },
    { "C",{ "Ca", 'a' } },
    { "È",{ "Cb", 'a' } },
    { "D",{ "Da", 'a' } },
    { "Ï",{ "Da", 'b' } },
    { "E",{ "Ea", 'a' } },
    { "É",{ "Ea", 'b' } },
    { "Ì",{ "Ea", 'c' } },
    { "F",{ "Fa", 'a' } },
    { "G",{ "Ga", 'a' } },
    { "H",{ "Ha", 'a' } },
    { "CH",{ "Hb", 'a' } },
    { "I",{ "Ia", 'a' } },
    { "Í",{ "Ia", 'b' } },
    { "J",{ "Ja", 'a' } },
    { "K",{ "Ka", 'a' } },
    { "L",{ "La", 'a' } },
    { "Å",{ "La", 'b' } },
    { "¼",{ "La", 'c' } },
    { "M",{ "Ma", 'a' } },
    { "N",{ "Na", 'a' } },
    { "Ò",{ "Na", 'b' } },
    { "O",{ "Oa", 'a' } },
    { "Ó",{ "Oa", 'b' } },
    { "Ô",{ "Oa", 'f' } },
    { "P",{ "Pa", 'a' } },
    { "Q",{ "Qa", 'a' } },
    { "R",{ "Ra", 'a' } },
    { "À",{ "Ra", 'b' } },
    { "Ø",{ "Rb", 'a' } },
    { "S",{ "Sa", 'a' } },
    { "Š",{ "Sb", 'a' } },
    { "T",{ "Ta", 'a' } },
    { "",{ "Ta", 'b' } },
    { "U",{ "Ua", 'a' } },
    { "Ú",{ "Ua", 'b' } },
    { "Ù",{ "Ua", 'd' } },
    { "V",{ "Va", 'a' } },
    { "W",{ "Wa", 'a' } },
    { "X",{ "Xa", 'a' } },
    { "Y",{ "Ya", 'a' } },
    { "İ",{ "Ya", 'b' } },
    { "Z",{ "Za", 'a' } },
    { "",{ "Zb", 'a' } },
    { " ",{ " ", ' ' } },
};

char velke(char znak)
{
    if ((znak >= 'a') && (znak <= 'z'))
    {
        return znak - 'a' + 'A';
    }
    if (mala_na_velka.find(znak) != mala_na_velka.end())
    {
        return mala_na_velka[znak];
    }
    return znak;
}

string velke(string text)
{
    string vysledek;
    for (char p : text)
    {
        vysledek += velke(p);
    }
    return vysledek;
}


string zastup(string text)
{
    string primarni, sekundarni, pismeno;
    string TEXT = velke(text);
    for (unsigned i = 0; i < TEXT.length(); i++)
    {
        pismeno.clear();
        pismeno += TEXT[i];
        if (
            (slozena_pismena.find(TEXT[i]) != slozena_pismena.end()) &&
            (i + 1 < TEXT.length()) &&
            (TEXT[i+1] == slozena_pismena[TEXT[i]])
           )
        {
            // jedná se o písmeno CH
            pismeno += slozena_pismena[TEXT[i]];
            i++;
        }
        primarni += uprava[pismeno].first;
        sekundarni += uprava[pismeno].second;
    }
    return primarni + ' ' + sekundarni;
}


bool abecedne(string lajna1, string lajna2) // Opakujeme se
{
    setlocale(LC_CTYPE, "Czech");
    return zastup(lajna1) < zastup(lajna2);
}

bool alfabeticky(string lajna1, string lajna2)
{
    // toto zajistí èeské prostøedí
    // !!! jene pro celı program a né jen pro funkci tøízení abecednì podle Czech
    // co je problém!
    setlocale(LC_CTYPE, "Czech"); // èeské znaky
    setlocale(LC_COLLATE, "Czech"); // èeské skládání

    return lok(lajna1, lajna2);
}


bool lexikograficky(string lajna1, string lajna2)
{
    return lajna1 < lajna2;
}

bool podle_cisel(string lajna1, string lajna2)
{
    istringstream vstup1(lajna1), vstup2(lajna2); // #include <sstream>
    int n1, n2;
    if ((vstup1 >> n1) && (vstup2 >> n2)) {
        return n1 < n2;
    }
    // Ošetøení pøípadu, kdy nelze naèíst èísla
    return lajna1 < lajna2;
}

bool walfabeticky(wstring lajna1, wstring lajna2)
{
    setlocale(LC_ALL, "Czech");
    return lok(lajna1, lajna2);
}

bool wlexikograficky(wstring lajna1, wstring lajna2)
{
    return lajna1 < lajna2;
}

bool wpodle_cisel(wstring lajna1, wstring lajna2)
{
    wistringstream vstup1(lajna1), vstup2(lajna2); // #include <sstream>
    int n1, n2;
    if ((vstup1 >> n1) && (vstup2 >> n2)) {
        return n1 < n2;
    }
    // Ošetøení pøípadu, kdy nelze naèíst èísla
    return lajna1 < lajna2;
}
