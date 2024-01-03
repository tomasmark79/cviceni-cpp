#include <Windows.h>
#include "20_priklad.h"
#include <fcntl.h>

using namespace std;

// Members of Class volba

// surov� �et�zecov� liter�l v ANSI
string volba::text_napovedy_cz = R"(
CP1250
SORT - program pro se�azen� ��dek dan�ho souboru. Pou�it�:
sort volba < vstupn�-soubor > v�stupn�-soubor
Mo�n� volby:
-n nebo /n �azen� podle ��sel na po��tc�ch ��dek
-l nebo /l lexikografick� �azen�
-a nebo /a abecedn� �azen�
)";

// �et�zec p�eveden funkc�
string volba::text_napovedy_v_852 = retezec_Cp1250_na_string_Cp852(R"(
CP852
SORT - program pro se�azen� ��dek dan�ho souboru. Pou�it�:
sort volba < vstupn�-soubor > v�stupn�-soubor
Mo�n� volby:
-n nebo /n �azen� podle ��sel na po��tc�ch ��dek
-l nebo /l lexikografick� �azen�
-a nebo /a abecedn� �azen�
)");

[[noreturn]]
void volba::napoveda()
{
    // nastav_konzolu_pro_cp1250();
    // p�id�no cestou - nen� z u�ebnice
    // SetConsoleOutputCP(CP_UTF8); // nasatv� na v�stupu utf8

    // CZ pro ANSI
    nastav_konzolu_pro_cp1250(); // �esk� prost�ed�
    cerr << text_napovedy_cz << endl;
    obnov_puvodni_nastaveni_konzoly();

    // CZ pro ANSI
    cerr << text_napovedy_v_852 << endl;

//    // UK pro UTF-8
//    setlocale(LC_ALL, "Russian");
//    SetConsoleOutputCP(866);
//    wcerr << text_napovedy_uk;
//
//    // CZ pro UTF-8
//    setlocale(LC_ALL, "Czech");
//    SetConsoleOutputCP(1250);
//    wcerr << text_napovedy_wide;


    // wcerr.imbue(std::locale(""));
    // nastav_rastr_cascadia();
    // wcerr << text_napovedy_uk << endl;
    // wcerr << text_napovedy_wide << endl;
    // printf_locale_vystup();
    // toto nastav� nastav� v�choz� hodnotu
    /*
            wcerr.imbue(std::locale(""));
            wcerr.imbue(std::locale("C"));
            wcerr.imbue(std::locale("POSIX"));
            */
    // wcerr << text_napovedy_wide << endl;

    // obnov_puvodni_nastaveni_konzoly();
    exit(1);
}

// asociativn� kontejner
map<string, volba::u_komparator> volba::tabulka_voleb
{
    {"-l", lexikograficky},
    {"-n", podle_cisel},
    {"-a", alfabeticky}
};

// novĂ˝ zpĹŻsob s asociativnĂ­m kontejnerem
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

