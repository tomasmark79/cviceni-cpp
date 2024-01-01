#include "20_priklad.h"
using namespace std;

// Members of Class volba
string volba::text_napovedy = retezec_Cp1250_na_string_Cp852(R"(
SORT - program pro seøazení øádek daného souboru. Použití:
sort volba < vstupní-soubor > výstupní-soubor
Možné volby:
-n nebo /n øazení podle èísel na poèátcích øádek
-l nebo /l lexikografické øazení
(C) Piškvorky software 2017
)");

[[noreturn]]
void volba::napoveda()
{
    // nastav_konzolu_pro_cp1250();
    cerr << text_napovedy << endl;

    // toto nastaví výchozí hodnotu
    /*
            wcerr.imbue(std::locale(""));
            wcerr.imbue(std::locale("C"));
            wcerr.imbue(std::locale("POSIX"));
            */
    // wcerr << text_napovedy_wide << endl;

    // obnov_puvodni_nastaveni_konzoly();
    exit(1);

}

// asociativní kontejner
map<string, volba::u_komparator> volba::tabulka_voleb
{
    {"-l", lexikograficky}, {"-n", podle_cisel},
};

//// Toto je možnost s lambda výrazem, jen pro ukázku
//map<string, volba::u_komparator> volba::tabulka_voleb
//{
//    {
//        "-l", [](string lajna1, string lajna2)->bool
//        {
//            return lajna1 < lajna2;
//        }
//    },
//    {
//        "-n", podle_cisel
//    },
//};

// nový zpùsob s asociativním kontejnerem
volba::volba(int argc, char **argv)
{
    try
    {
        if (argc != 2)
        {
            throw runtime_error("Špatný poèet parametrù!");
        }
        if (argv[1][0] == '/')
        {
            argv[1][0] = '-';
        }
        komparator = tabulka_voleb.at(argv[1]);
    }
    catch (exception &e)
    {
        napoveda();
    }
}

// starý zpùsob bez asociativního kontejneru
//volba::volba(int argc, char **argv)
//{
//    if (argc != 2)
//        napoveda(); // program exit
//    if ((argv[1][0] != '-') && (argv[1][0] != '/')) //viz 14.1.3
//        napoveda(); // program exit
//    switch (argv[1][1])
//    {
//    case 'l':
//        komparator = lexikograficky;
//        return;
//    case 'n':
//        komparator = podle_cisel;
//        return;
//    default:
//        napoveda(); // program exit
//    }
//}

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
