#include "20_komparatory.h"
#include <unordered_map>
#include <sstream>

using namespace std;

// locale lok("Czech_Czech Republic.1250"); // nelze s G++ compilatorem
// Jestli�e k p�ekladu posledn� verze na�eho programu pou�ijete p�eklada� g++
// a spust�te program s volbou pro abecedn� �azen�, skon�� v�jimkou, nebo� � jak v�me
// � tento p�eklada� pod Windows podporuje pouze lok�ln� nastaven� "C".
// To znamen�, �e si mus�me napsat odpov�daj�c� n�stroje samy :-).

std::locale lok(""); // toto je v�ak OK

map <char, char> slozena_pismena
{
    {'C', 'H'},
};

unordered_map<char, char> mala_na_velka
{
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
    { '�', '�' },
};
static unordered_map< string, pair<string, char>> uprava
{
    { "A",{ "Aa", 'a' } },
    { "�",{ "Aa", 'b' } },
    { "�",{ "Aa", 'e' } },
    { "B",{ "Ba", 'a' } },
    { "C",{ "Ca", 'a' } },
    { "�",{ "Cb", 'a' } },
    { "D",{ "Da", 'a' } },
    { "�",{ "Da", 'b' } },
    { "E",{ "Ea", 'a' } },
    { "�",{ "Ea", 'b' } },
    { "�",{ "Ea", 'c' } },
    { "F",{ "Fa", 'a' } },
    { "G",{ "Ga", 'a' } },
    { "H",{ "Ha", 'a' } },
    { "CH",{ "Hb", 'a' } },
    { "I",{ "Ia", 'a' } },
    { "�",{ "Ia", 'b' } },
    { "J",{ "Ja", 'a' } },
    { "K",{ "Ka", 'a' } },
    { "L",{ "La", 'a' } },
    { "�",{ "La", 'b' } },
    { "�",{ "La", 'c' } },
    { "M",{ "Ma", 'a' } },
    { "N",{ "Na", 'a' } },
    { "�",{ "Na", 'b' } },
    { "O",{ "Oa", 'a' } },
    { "�",{ "Oa", 'b' } },
    { "�",{ "Oa", 'f' } },
    { "P",{ "Pa", 'a' } },
    { "Q",{ "Qa", 'a' } },
    { "R",{ "Ra", 'a' } },
    { "�",{ "Ra", 'b' } },
    { "�",{ "Rb", 'a' } },
    { "S",{ "Sa", 'a' } },
    { "�",{ "Sb", 'a' } },
    { "T",{ "Ta", 'a' } },
    { "�",{ "Ta", 'b' } },
    { "U",{ "Ua", 'a' } },
    { "�",{ "Ua", 'b' } },
    { "�",{ "Ua", 'd' } },
    { "V",{ "Va", 'a' } },
    { "W",{ "Wa", 'a' } },
    { "X",{ "Xa", 'a' } },
    { "Y",{ "Ya", 'a' } },
    { "�",{ "Ya", 'b' } },
    { "Z",{ "Za", 'a' } },
    { "�",{ "Zb", 'a' } },
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
            // jedn� se o p�smeno CH
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
    // toto zajist� �esk� prost�ed�
    // !!! jen�e pro cel� program a n� jen pro funkci t��zen� abecedn� podle Czech
    // co� je probl�m!
    setlocale(LC_CTYPE, "Czech"); // �esk� znaky
    setlocale(LC_COLLATE, "Czech"); // �esk� skl�d�n�

    return lok(lajna1, lajna2);
}


bool lexikograficky(string lajna1, string lajna2)
{
    return lajna1 < lajna2;
}

bool podle_cisel(string lajna1, string lajna2)
{
    istringstream vstup1(lajna1), vstup2(lajna2)/*, vstup3(lajna2)*/; // #include <sstream>
    int n1, n2;
    vstup1 >> n1;
    vstup2 >> n2;
    cout << "1: " << "\t" << n1 << " ";
    cout << "2: " << "\t" << " " << n2 << " ";
    if (n1 < n2)
        cout << "vstup1 < vstup2" << "   -   ";
    else if (n1 > n2)
        cout << "vstup1 > vstup2" << "   -   ";
    else if (n1 == n2)
        cout << "vstup1 = vstup2" << "   -   ";
    cout << "return: " << (n1 < n2) << endl;
    return n1 < n2;
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
    vstup1 >> n1;
    vstup2 >> n2;
    return (n1 < n2);
}
