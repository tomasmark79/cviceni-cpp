#include "20_priklad.h"
using namespace std;

// Members of Class volba
string volba::text_napovedy = retezec_Cp1250_na_string_Cp852(R"(
SORT - program pro se�azen� ��dek dan�ho souboru. Pou�it�:
sort volba < vstupn�-soubor > v�stupn�-soubor
Mo�n� volby:
-n nebo /n �azen� podle ��sel na po��tc�ch ��dek
-l nebo /l lexikografick� �azen�
(C) Pi�kvorky software 2017
)");

[[noreturn]]
void volba::napoveda()
{
    // nastav_konzolu_pro_cp1250();
    cerr << text_napovedy << endl;

    // toto nastav� v�choz� hodnotu
    /*
    wcerr.imbue(std::locale(""));
    wcerr.imbue(std::locale("C"));
    wcerr.imbue(std::locale("POSIX"));
    */
    // wcerr << text_napovedy_wide << endl;

    // obnov_puvodni_nastaveni_konzoly();
    exit(1);

}
volba::volba(int argc, char **argv)
{
    if (argc != 2)
        napoveda(); // program exit
    if ((argv[1][0] != '-') && (argv[1][0] != '/')) //viz 14.1.3
        napoveda(); // program exit
    switch (argv[1][1])
    {
    case 'l':
        komparator = lexikograficky;
        return;
    case 'n':
        komparator = podle_cisel;
        return;
    default:
        napoveda(); // program exit
    }
}
volba::u_komparator volba::zvoleno()
{
    return komparator;
}

// Members of Class tridic
void tridic::zpracuj(volba::u_komparator komparator)
{
    nacti();
    serad(komparator);
    vypis();
}

void tridic::nacti()
{
    while (getline(cin, radka))
    {
        soubor.push_back(radka);
    }
}

void tridic::serad(volba::u_komparator komparator)
{
    sort(soubor.begin(), soubor.end(), komparator);
}

void tridic::vypis()
{
    for (auto lajna : soubor)
    {
        cout << lajna << endl;
    }
}
