#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include "cestina.h"

#include "zajimavosti.h"
// #include "tricks.h"

//#include "03_slozitejsi_programy.h"
//#include "04_pokrocilejsi_konstrukce_a_techniky.h"
//#include "06_zakladni_datove_typy.h"
//#include "07_prikazy.h"
//#include "09_prace_s_pameti.h"
//#include "09_strom.h"
//#include "10_vyctove_typy_struktury_a_unie.h"
//#include "11_vyrazy.h"
//#include "12_deklarace_a_promenne.h"
//#include "13_funkce.h"
//#include "14_program_a_jeho_beh.h"
//#include "15_preprocesor.h"
//#include "16_objektove_typy.h"
//#include "17_dedeni.h"
//#include "17_zakladni_a_barevne_graficke_objekty.h"
//#include "18_chyby_za_behu_programu.h"
//#include "19_vstupy_a_vystupy.h"
//#include "19_vstupy_a_vystupy_print.h"
#include "20_inicializace.h"
#include "20_priklad.h"
#include "20_priklad_wide.h"
#include "20_komparatory.h"

using namespace std;

#ifndef __cplusplus
#  error C++ is required
#elif __cplusplus <= 201103L
#  error C++14 + is required
#endif

// Defini�n� deklaraci statick� datov� slo�ky mus�me uv�st mimo t�lo t��dy.
// Typicky ji zapisujeme do implementa�n�ho souboru.
// V n� kl��ov� slovo static neuv�d�me; identifik�tor statick� slo�ky v n�
// mus�me kvalifikovat jm�nem t��dy pomoc� oper�toru ::.
// Tato definice m��e obsahovat inicializaci.
int Tabs::nTabCount = 0; // v C++ staticka prom�nn� (slo�ka), t��dn� slo�ka

    // Zd�razn�me, �e p��kazy pro p�esm�rov�n� vstupu a v�stupu
    // nejsou pargametry programu. Tyto p��kazy zpracuje
    // opera�n� syst�m p�ed spu�t�n�m programu.

//#define TRICKS

//#define KAP3
//#define KAP4
//#define KAP6
//#define KAP7
//#define KAP9
//#define KAP10
//#define KAP11
//#define KAP12
//#define KAP13
//#define KAP14
//#define KAP15
//#define KAP16
//#define KAP17
//#define KAP18
//#define KAP19

#define SHOW_WORKING_FILE_PATH
//#define SHOW_USER_LOCALE
#define KAP20 // sort



#ifdef USE_WIDE_ENTRY_POINT_MAIN
int wmain( int argc, wchar_t *argv[]) // need -municode
#else
int main(int argc, char *argv[], char* env[])
#endif // USE_WIDE_ENTRY_POINT_MAIN

{

#ifdef SHOW_WORKING_FILE_PATH
    // c++ 2017 -
    // char *buf = nullptr; cout << "getcwd: " << getcwd(buf, 1024) << endl;
    // c++ 2017 +
    cout << std::filesystem::current_path() << endl;
#endif // SHOW_WORKING_FILE_PATH

#ifdef SHOW_USER_LOCALE
    // https://en.cppreference.com/w/cpp/locale/locale
    std::wcout << "User-preferred locale setting is "
               << std::locale("").name().c_str() << '\n';
    // on startup, the global locale is the "C" locale
    std::wcout << 1000.01 << '\n';

    // replace the C++ global locale and the "C" locale with the user-preferred locale
    std::locale::global(std::locale(""));

    // use the new global locale for future wide character output
    std::wcout.imbue(std::locale());

    // output the same number again
    std::wcout << 1000.01 << '\n';

    // jen pokus
    try
    {
        // Z�sk�n� v�choz�ho jazyka syst�mu
        LANGID systemLangID = GetSystemDefaultUILanguage();
        std::cout << "V�choz� jazyk syst�mu: " << systemLangID << std::endl;

        // Z�sk�n� jazyka u�ivatele
        LANGID userLangID = GetUserDefaultUILanguage();
        std::cout << "Jazyk u�ivatele: " << userLangID << std::endl;

        // Z�sk�n� n�zvu lok�ln�ho nastaven�
        wchar_t* localeName = new wchar_t[LOCALE_NAME_MAX_LENGTH];

        if (GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SNAME, localeName, LOCALE_NAME_MAX_LENGTH) == 0) {
            delete[] localeName;
            throw std::runtime_error("Chyba p�i z�sk�v�n� n�zvu lok�ln�ho nastaven�.");
        }

        size_t len = wcslen(localeName) + 1;
        char* localeNameChar = new char[len];
        wcstombs(localeNameChar, localeName, len);
        // Zde m��ete p�ev�st LANGID na odpov�daj�c� n�zev lokalizace a pou��t jej v k�du
        // pod windows nejde pou��t nic - jen "", "C", "POSIX"
        // std::locale::global(std::locale(localeNameChar));

        delete[] localeName;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Chyba: " << e.what() << std::endl;
    }

#endif // SHOW_WORKING_FILE_PATH


#if defined KAP20 && defined USE_WIDE_ENTRY_POINT_MAIN
    wvolba wzjistena_volba(argc, argv);
    wtridic wradic;
    wradic.wzpracuj(wzjistena_volba.wzvoleno());
#endif


#if defined KAP20 && !defined USE_WIDE_ENTRY_POINT_MAIN
    volba zjistena_volba(argc, argv);
    tridic radic;
    radic.zpracuj(zjistena_volba.zvoleno());
#endif



#ifdef TRICKS
    Tabs::reset();
    Tabs::printFunctionHeader("Tricks:");
    cout << endl;
    operatorNew_Whoops();
#endif

#ifdef KAP3
    // 03
    cout << "Kapitola 03:" << endl;
    //vstup();
    //kontrola_meze();
    //napoveda();
    //faktorial_priprava();
    //faktorial_v_namespace(int m);
    //faktorial_rekurzivni_v_namespace(int m);
    //faktorial(int m);
    //faktorial(double m);
    //faktorial_rekurzivni(int m);
    vypis_globalni_promennou();
    vstup_faktorial();
    vstup_zadej_dve_cisla_ktere_je_vetsi();
#endif
#ifdef KAP4
    // 04
    cout << "Kapitola 04:" << endl;
    vypis_pocet_napisu();
    vypis_mnoho_verzi_teze_tridy();
#endif
#ifdef KAP6
    // 06
    cout << "Kapitola 06:" << endl;
    // char prevod_na_velke_znaky(char c);
    // std::string binarizuj(int m);
    // int vypis_zaokrouhlovaci_chyby();
    vypis_zaokrouhlovaci_priklady();
    vypis_plochy_a_obvodu_trojuhelnika();
    vypis_minimummaximum();
#endif
#ifdef KAP7
    // 07
    cout << "Kapitola 07:" << endl;
    vypis_pozdrav_pomoci_pole_string(1);
    vypis_pozdrav_pomoci_switch('1');
    vstup_je_hodnota_cislo();
    vstup_mam_pokracovat("Chcete pokra�ovat?");
    for_pruchod_indexem_a_objektem();
    vypis_for_a_prikaz_break();
    vypis_for_a_prikaz_continue();
    for_cyklus_nekonecny();
#endif
#ifdef KAP9
    // 09
    cout << "Kapitola 09:" << endl;
    //prohod_promenne_pomoci_reference(int &a, int &b);
    //prohod_promenne(int *a, int *b);
    //char *otoc_retezec(const char *zadano, char *otoceno);
    //char *otoc_retezec_na_miste(char * txt);
    //size_t delka_retezce_adresova_aritmetika(char* txt);
    vypis_chyboveho_textu_dle_parametru(1);
    //f(int &n);
    //f(int &&n);
    //f(double &n);
    //f(double &&n);
    reference_na_r_hodnotu();
    vypis_clenskou_slozku_z_chytry_ukazatel();
    vypis_prikladu_z_teto_sekce_09();
    hraj_hru_hadej_zvire();
#endif
#ifdef KAP10
    // 10
    cout << "Kapitola 10:" << endl;
    vypis_prikladu_z_teto_sekce_10();

#endif
#ifdef KAP11
    // 11
    cout << "Kapitola 11:" << endl;
    vypis_volani_funkce_dle_operatoru();
#endif

#ifdef KAP12
    // 12
    cout << "Kapitola 12:" << endl;
    vypis_pole_ukazatelu();
    vypis_ukazatele_a_konstanty();
    vypis_deklaraci_typedef();
    vypis_deklaraci_using();
    vypis_zastineni_funkce_promennou();

#endif
#ifdef KAP13
    // 13
    cout << "Kapitola 13:" << endl;
    vypis_volani_funkci();
    vypis_vysledku_ukazatelu_na_funkce_double();
    vypis_zakazana_funkce();
    vypis_proverka(5, 5);
    vypis_moc3();
    volani_strlen_konstantni_ukazka();
    vypis_tisk();
    vypis_printf();
    vypis_vypustky();
    vypis_funkci_variadicke_sablony();
    vypis_vysledku_pretizeni_funkce_vypoctu_plochy_trojuhelnika();
    vypis_vyber_pretizene_funkce();
    vypis_ukazatel_na_funkci();
    vypis_volani_funkce_graf_pres_ukazatel();
    vypis_volani_lambda_vyraz();
#endif
#ifdef KAP14
    // 14
    cout << "Kapitola 14:" << endl;
    // provedou se ukon�ovac� pr�ce pomoc� zaregistrov�n� funkce
    atexit(fce1);
    atexit(fce2);

    cout << "Parametry p��kazov� ��dky programu p�i spu�t�n�: " << endl;
    for(int i = 0; i < argc; i++)
    {
        cout << argv[i] << " ";
    }

    //
    // P��KLAD 14.3: V�PIS V�ECH PROM�NN�CH PROST�ED�
    //
    cout << "Aktu�ln� syst�mov� prom�nn�: " << endl;
    for(int i{0}; env[i]; i++)
    {
        // posledn� prvek pole env obsahuje nullptr
        cout << env[i] << endl;
    }
    //
    // P��KLAD 14.2: OBSAH SYST�MOV� PROM�NN� PATH
    //
    // Vyp�e prom�nn� opera�n�ho syst�mu
    // Nullptr = pokud neexistuje prom�nn�
    cout << "Prom�nn� PATH: " << endl << getenv("PATH") << endl;

    // ukonceni_app();
    // sestreleni_app();
#endif
#ifdef KAP15
    // 15
    cout << "Kapitola 15:" << endl;
    vypis_manifestacni_konstanty();
    vypis_druhou_mocninu_makrem();
#endif
#ifdef KAP16
    // 16
    Tabs::printFunctionHeader("Kapitola 16:");

    vypis_sprateleny_operator_plus();
    vypis_vektoru_pres_aliasy();
    vypis_konverzni_konstruktor();
    vypis_explicitni_konstruktor();
    vypis_kopirovaci_a_stehovaci_konstruktor();
    vypis_inicializace_vektoru_seznamem_inicializatoru_nebo_i_jinak();
    vypis_explicitni_volani_konstruktoru();
    vypis_pole_komplexnich_cisel();
    vypis_delegovani_konstruktoru();
    vypis_kopirovani_vektoru();
    vypis_prirazovani_vektoru();
    vypis_vektor_jako_slozka_slozitejsi_tridy();
    vypis_imaginarni_jednotka();
    vypis_konstantni_instance();

#endif
#ifdef KAP17
    Tabs::reset();
    Tabs::printFunctionHeader("Kapitola 17: Start");

    zakladni_a_barevne_graficke_objekty_staticky();

    zakladni_a_barevne_graficke_objekty_dynamicky();
#endif

#ifdef KAP18
    Tabs::reset();
    Tabs::printFunctionHeader("Kapitola 18: Start");
    cout << endl;
    //vypis_vstupni_a_vystupni_podminky();
    //vypis_zachyceni_vyjimky();
    vypis_uklid_pomoci_destruktoru_a_chytre_ukazatele();
    vypis_funkce_z_niz_se_nemuze_sirit_vyjimka();
#endif
#ifdef KAP19
    Tabs::reset();
    Tabs::printFunctionHeader("Kapitola 19: Vstupy a v�stupy");
    cout << endl;
    vstupy_vystupy();
    vstupy_vystupy_print();
#endif




     return 0;
}
