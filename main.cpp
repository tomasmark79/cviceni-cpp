#include <stdlib.h>
#include <iostream>
#include "cestina.h"
#include "zajimavosti.h"

#include "03_slozitejsi_programy.h"
#include "04_pokrocilejsi_konstrukce_a_techniky.h"
#include "06_zakladni_datove_typy.h"
#include "07_prikazy.h"
#include "09_prace_s_pameti.h"
#include "09_strom.h"
#include "10_vyctove_typy_struktury_a_unie.h"
#include "11_vyrazy.h"
#include "12_deklarace_a_promenne.h"
#include "13_funkce.h"
#include "14_program_a_jeho_beh.h"
#include "15_preprocesor.h"
// #include "16_objektove_typy.h"
#include "17_dedeni.h"

using namespace std;

#ifndef __cplusplus
#  error C++ is required
#elif __cplusplus <= 201103L
#  error C++14 is required
#endif

// #define KAP4
#define KAP17

// 2x funkce pro kapitola 14
void fce1()
{
    cout << "ukon�ovac� pr�ce: fce1" << endl;
}
void fce2()
{
    cout << "ukon�ovac� pr�ce: fce2" << endl;
}

int main(int argc, char *argv[], char* env[])
{
    zarid_cestinu();
    // print_colors();

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
    // 16
    Tabs::printFunctionHeader("Kapitola 17:");

#endif

    return 0;
}
