#include "20_priklad.h"
#include "20_komparatory.h"
#include <fstream>
using namespace std;

// Members of Class volba

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

[[noreturn]]
void volba::napoveda()
{
    // nastav_konzolu_pro_cp1250();
    // p�id�no cestou - nen� z u�ebnice
    // SetConsoleOutputCP(CP_UTF8); // nasatv� na v�stupu utf8

    // ANSI Varianty

    // VARIANTA 1
    // program p�evede �et�zec 1250 na 852 (jde jen u kompatibiln�ch znak�)
    cerr << text_napovedy_v_852 << endl;

    // VARIANTA 2
    // Nau�� konzolov� okno pou��vat k�dovou str�nku 1250.
    nastav_konzolu_pro_cp1250();
    cerr << text_napovedy_cz << endl;

    // Obnov� konzolov� okno do p�ovdn�ho stavu
    obnov_puvodni_nastaveni_konzoly();

    exit(1);
}

// asociativn� kontejner
map<string, volba::u_komparator> volba::tabulka_voleb
{
    {"-l", lexikograficky},
    {"-n", podle_cisel},
    {"-a", alfabeticky},
    {"-A", abecedne},
    {"-lo", negace<lexikograficky>},
    {"-no", negace<podle_cisel>},
    {"-ao", negace<alfabeticky>},
    {"-Ao", negace<abecedne>},
};

// konstruktor vytvo�� ukazatel na funkci dle asociativn�ho kontejneru tabulky voleb
volba::volba(int argc, char **argv)
{
    argc=2;
    argv[1] = "-no";
    try
    {
        if (argc != 2)
        {
            throw runtime_error("�patn� po�et parametr�!");
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
    setlocale(LC_ALL, "Czech");
    nacti();
    serad(komparator);
    vypis();
}

void tridic::nacti()
{

    // �ten� ze souboru napevno
    // vhodn� pro lad�n�
    // string jmeno = "abcd-ansi.txt";
    string jmeno = "vstup";

    ifstream vstup(jmeno);
    if (!vstup)
    {
        cerr << "Nepoda�ilo se otev��t soubor " << jmeno << endl;
        return;
    }
    while (getline(vstup, radka))
    {
        soubor.push_back(radka);
        cout << "soubor size: " << soubor.size() << endl;
    }

    // �ten� ze souboru vstupn�m proudem
    // while (getline(cin, radka))

}

void tridic::serad(volba::u_komparator komparator)
{
    try
    {
        sort(soubor.begin(), soubor.end(), komparator);
    } catch (exception &e)
    {
        cout << e.what() << endl;
    }
}

void tridic::vypis()
{
    for (auto lajna : soubor)
    {
        cout << lajna << endl;
    }
}
