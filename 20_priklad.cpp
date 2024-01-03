#include <Windows.h>
#include "20_priklad.h"
#include <fcntl.h>

using namespace std;

// Members of Class volba

// øetìzec pøeveden funkcí
string volba::text_napovedy_v_852 = retezec_Cp1250_na_string_Cp852(R"(
CP852
SORT - program pro seøazení øádek daného souboru. Použití:
sort volba < vstupní-soubor > výstupní-soubor
Možné volby:
-n nebo /n øazení podle èísel na poèátcích øádek
-l nebo /l lexikografické øazení
-a nebo /a abecední øazení
)");

// surový øetìzecový literál v ANSI
string volba::text_napovedy_cz = R"(
CP1250
SORT - program pro seøazení øádek daného souboru. Použití:
sort volba < vstupní-soubor > výstupní-soubor
Možné volby:
-n nebo /n øazení podle èísel na poèátcích øádek
-l nebo /l lexikografické øazení
-a nebo /a abecední øazení
)";

[[noreturn]]
void volba::napoveda()
{
    // nastav_konzolu_pro_cp1250();
    // pøidáno cestou - není z uèebnice
    // SetConsoleOutputCP(CP_UTF8); // nasatví na výstupu utf8

    // ANSI Varianty

    // VARIANTA 1
    // program pøevede øetìzec 1250 na 852 (jde jen u kompatibilních znakù)
    cerr << text_napovedy_v_852 << endl;

    // VARIANTA 2
    // Nauèí konzolové okno používat kódovou stránku 1250.
    nastav_konzolu_pro_cp1250();
    cerr << text_napovedy_cz << endl;

    // Obnoví konzolové okno do pùovdního stavu
    obnov_puvodni_nastaveni_konzoly();

    exit(1);
}

// asociativní kontejner
map<string, volba::u_komparator> volba::tabulka_voleb
{
    {"-l", lexikograficky},
    {"-n", podle_cisel},
    {"-a", alfabeticky}
};

// konstruktor vytvoøí ukazatel na funkci dle asociativního kontejneru tabulky voleb
volba::volba(int argc, char **argv)
{
    try
    {
        if (argc != 2)
        {
            throw runtime_error("!");
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
