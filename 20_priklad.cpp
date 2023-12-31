#include <iostream>
#include "20_priklad.h"
// #include <cstring>
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

/* toto pou�it� �et�zc� s jin�mi ne� ASCII znaky nen� doporu�en�!
wstring volba::text_napovedy_wide = R"(
SORT - program pro se�azen� ��dek dan�ho souboru. Pou�it�:
sort volba < vstupn�-soubor > v�stupn�-soubor
Mo�n� volby:
-n nebo /n �azen� podle ��sel na po��tc�ch ��dek
-l nebo /l lexikografick� �azen�
(C) Pi�kvorky software 2017
)";
*/


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
        zjistena_volba = lexikograficky;
        return;
    case 'n':
        zjistena_volba = numericky;
        return;
    default:
        napoveda(); // program exit
    }
}
volba::zvoleno_t volba::zvoleno()
{
    return zjistena_volba;
}

// Members of Class tridic
void tridic::zpracuj(volba::zvoleno_t zvoleno)
{
    nacti();
    serad(zvoleno);
    vypis();
}

void tridic::nacti()
{
    while (getline(cin, radka))
    {
        soubor.push_back(radka);
    }
}

void tridic::serad(volba::zvoleno_t zvoleno)
{
    if(zvoleno == volba::lexikograficky)
    {
        sort(soubor.begin(), soubor.end());
    }
    else if (zvoleno == volba::numericky) // elseif jen tak :-)
    {
        sort(soubor.begin(), soubor.end(), podle_cisel);
    }
}

void tridic::vypis()
{
    for (auto lajna : soubor)
    {
        cout << lajna << endl;
    }
}


//// moje �prava
//void tridic::zpracuj_muj()
//{
//    string jmeno = "cz.txt";
//    string jmenoVystup = "cz-sorted.txt";
//    ifstream vstup(jmeno);
//    if (!vstup)
//    {
//        cerr << "Nepoda�ilo se otev��t soubor " << jmeno << endl;
//        return;
//    }
//
//    cout << "reading..." << endl;
//    while (getline(vstup, radka))
//    {
//        soubor.push_back(radka); // ulo�� **kopii** p�edan� instance
//    }
//
//    cout << "sorting..." << endl;
//    sort(soubor.begin(), soubor.end());
//    cout << "sorted..." << endl;
//    ofstream vystup(jmenoVystup);
//    if (!vystup)
//    {
//        cerr << "Nepoda�ilo se otev��t soubor " << jmenoVystup << endl;
//        return;
//    }
//
//    cout << "writting..." << endl;
//    for(auto lajna: soubor)
//    {
//        vystup << lajna << endl;
//    }
//
//    cout << "written..." << endl;
//}


