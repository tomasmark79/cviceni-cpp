#include <iostream>
#include <algorithm>
#include <cstring>
#include "09_prace_s_pameti.h"

using namespace std;

void prohod_promenne(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void prohod_promenne_pomoci_reference(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

char *otoc_retezec(const char *zadano, char *otoceno)
{
    size_t delka = strlen(zadano);
    for (size_t i = 0, j = delka - 1; i < delka; i++, j --)
    {
        otoceno[j] = zadano[i];
    }
    otoceno[delka] = '\0';
    return otoceno;
}

/* Práce s pamìtí 161
PØÍKLAD 9.5: OTOÈENÍ ØETÌZCE NA MÍSTÌ
Také funkci pro otoèení øetìzce na místì mùžeme implementovat s využitím adresové aritmetiky. Podívejme se na
zdrojový kód:
*/
// není nutné používat, jedná se spíše o folklór C++ ke kterému tato funkce neodmyslitelnì patøí
char *otoc_retezec_na_miste(char * txt)
{
    for (char *p = txt, *q = p + (strlen(txt) - 1); p < q; p++, q--)
    {
        char pom = *p;
        *p = *q;
        *q = pom;
    }
    return txt;
}

/* Podívejme se na možnou implementaci funkce pro urèení délky znakového øetìzce založenou na použití adresové
aritmetiky.
*/
size_t delka_retezce_adresova_aritmetika(char* txt)
{
    char *pom;
    for (pom = txt; *pom; pom++)
        ;
    return pom - txt;
}

//const int pocet_zprav = 6;
//const int delka_zprav = 30;


// deklarace s inicializaci pomoci pole
/*
char texty[][delka_zprav] = { "Chybí adresa", "Nesprávné PSÈ",
                              "Neexistuje obec", "Nesprávná ulice", "Nesprávné èíslo domu",
                              "Adresát neznámý"
                            };
*/
// deklarace s inicializaci pomoci ukazatele
char *chybove_texty[] =
{
    "Chybí adresa", "Nesprávné PSÈ","Neexistuje obec", "Nesprávná ulice", "Nesprávné èíslo domu",
    "Adresát neznámý", "AbrakaDabra Ope Se Za Mi"
};
char *chyba_chyby = "Neznámá chyba";

void vypis_chyboveho_textu_dle_parametru(int n)
{
    int pocet_zprav = sizeof(chybove_texty) / sizeof(char*);
    if ((n > 0) || (n <= pocet_zprav))
    {
        cout << chybove_texty[n - 1];
    }
    else
    {
        cout << chyba_chyby;
    }
    cout << endl;
}

// To znamená, že napøíklad ukazatel na jednorozmìrné pole typu int o 6 prvcích mùžeme deklarovat zápisem:
// int i[6] {1,2,3,4,5}, (*pi)[6];
// pi = i;
// pi = i;

//    cout << "Hodnota neobjektové promìnné o velikosti jenoho pole na adrese " << &pi << " je " << ((int*)*pi[0]) << endl;

// Vynecháme-li závorky, dostaneme deklaraci pole ukazatelù. To znamená, že napøíklad deklarace:
//  int * pi2[6]; // zavádí pole 6 ukazatelù na int.


void f(int &n)
{
    // ...
    cout << "int & :" << n << endl;
}

void f(int &&n)
{
    // ...
    cout << "int && :" << n << endl;
}

void f(double &n)
{
    // ...
    cout << "double & :" << n << endl;
}

void f(double &&n)
{
    // ...
    cout << "double && :" << n << endl;
}

void reference_na_r_hodnotu()
{
    int i = 1;
    int x = 99;
    double d = 1.1;
    f(i);   // &    1
    f(i+2); // &&   3
    f(i+9); // &&   10
    f(i++); // &&   1
    f(--i); // &    1
    f(++i); // &    2
    f(99);  // &&   99
    f(x+i); // &&   101
    f(x/i); // &&   49
    f(x%i); // &&   1
    f(d);   // &    1.1
    f(d++); // &&   1.1
    f(++d); // &    3.1
    f(++d+i); // &&  6.3


    f(move(i)); //  && 2;
    /*Chceme-li zavolat funkci s parametrem pøedstavujícím referenci na r-hodnotu a potøebujeme-li jí pøitom pøedat
    l-hodnotu, využijeme knihovní funkce move() deklarovanou v hlavièkovém souboru <utility>, napøí-
    klad:
    */
}

void vypis_clenskou_slozku_z_chytry_ukazatel()
{
    ChytryUkazatel<int> intPointer(new int(42));
    ChytryUkazatel<double> doublePointer(new double(3.14));
    ChytryUkazatel<long> longPointer(new long(545464466));

    std::cout << "Hodnota intPointer: " << intPointer.getValue() << std::endl;
    std::cout << "Hodnota doublePointer: " << doublePointer.getValue() << std::endl;
    std::cout << "Hodnota longPointer: " << longPointer.getValue() << std::endl;
}

void vypis_prikladu_z_teto_sekce_09()
{

    // pøedávání parametrù odkazem se hodí, když potøebujeme, aby funkce mìnila své parametry
    int an {1}, bn{2};
    prohod_promenne_pomoci_reference(an, bn); //
    cout << "an " << an << " bn " << bn << endl;
    swap<int>(an,bn); //
    cout << "an " << an << " bn " << bn << endl;

    // odkazovaná promìnná &
    int absint = 8;
    int &ref_absint = absint;
    ref_absint = 45;
    int *p_absint = &ref_absint;
    cout << ref_absint << " adresa " << p_absint << endl;

    // dynamické pole
    int *pipi_slozene = new int {9};
    delete pipi_slozene;
    //nebo
    int *pipi_kulate = new int (9);
    delete pipi_kulate;

    int *pipi_slozene_0 = new int {}; // 0
    delete pipi_slozene_0;
    //nebo
    int *pipi_kulate_0 = new int (); // 0
    delete pipi_kulate_0;

    // dynamické pole vícerozmìrné
    // int(*pppp)[2][3][4] = new int[3][2][3][4];
    // ukazatel na dvourozmìrné pole s inicializací
    //  ukazatel=[]                0 1   0 1   0 1
    int(*ppp)[2] = new(nothrow) int[3][2] { {1,2},{3,4},{5,6} };
    //                            0     1     2
    cout << ppp[1][1] << endl;
    delete [] ppp;

    // dvourozmìrné pole
    int(*qq)[2] = new(nothrow) int[1][2] { {1,2}, {3,4} };
    cout << qq[0][0] << endl;
    delete [] qq; // Operátor delete nemìní obsah ukazatele


    char * pozdr {"Dobrý den"};
    cout << pozdr << endl << endl;

    cout << "sizeof texty = " << sizeof(chybove_texty) << " char* sizeof = " << sizeof(char*) << endl;
    cout << "podíl = " << sizeof(chybove_texty)/sizeof(char*) << endl << endl;

    int pocet_zprav = sizeof(chybove_texty) / sizeof(char*);
    vypis_chyboveho_textu_dle_parametru(1);
    vypis_chyboveho_textu_dle_parametru(2);
    vypis_chyboveho_textu_dle_parametru(pocet_zprav);

    cout << endl;

    // 9.2.3 Adresová aritmetika
    // delka3
    char text[20] {"abcdefg"};
    size_t delka3_n = delka_retezce_adresova_aritmetika(text);
    cout << "Adresová aritmetika: " << endl << "Délka øetìzce " << text << " je: " << delka3_n << endl << endl;

    // volání funkce a pøedání pole pøes ukazatele a otoèení na místì
    char zadanonamiste[11] {"Robotizace"};
    cout << "Zadáno: " << zadanonamiste << " Otoèeno na místì: " << otoc_retezec_na_miste(zadanonamiste) << endl;


    // volání funkce a pøedání pole pøes ukazatele a návrat pole pøes ukazatele
    const char zadano[11] {"Robotizace"};
    char otoceno [11];
    cout << "Zadáno: " << zadano << " Otoèeno: " << otoc_retezec(zadano, otoceno) << endl << endl;


    // prohozeni promenných pomocí ukazatelù
    int x {5}, y{10};

    cout << "X: " << x << " Y: " << y << endl;
    prohod_promenne(&x, &y);
    cout << "X: " << x << " Y: " << y << endl;

    // ukazatel na promìnnou
    int n {6}, *p;

    // NELZE
    // *p = n; // NELZE - *p neni inicializovan
    /*  Tím uložíte hodnotu promìnné n na adrese, na kterou ukazuje p.
    To znamená,že hodnota promìnné n bude uložena na místì, kam ukazuje p. */

    // LZE - NEPØÍMÝ PØÍSTUP S UŽITÍM UKAZATELE
    p = &n; // Tím pøiøadíte ukazateli p adresu promìnné n. Teï p ukazuje na pamìovou adresu promìnné n.
    // &p vypíše adresu samotného ukazatele p.
    // p vypíše adresu, na kterou ukazuje ukazatel p.
    cout << "Adresa samotného ukazatele \"p\" je: " << &p << endl;
    cout << "Kdežto, Adresa na kterou ukazatel \"p\" ukazuje je: " << p << " a hodnota typu INT na této adrese je: " << *p << endl;
    cout << endl;


    // Ukazatel bez doménového typu VOID
    // Pøetypování ukazatele
    void *v;
    int cislo = 1; // Pøíklad s dereferencí ukazatele bez pøiøazení hodnoty mùže zpùsobit nedefinované chování nebo dokonce pád programu.
    v = &cislo; // !!! - Než budete chtít pracovat s ukazatelem, mìl byste mu pøiøadit platnou adresu pamìti
    cislo = *(int*)v; //Promìnnou v jsme nejprve pøetypovali na int* a pak jsme ji dereferencovali.

    // ukazatele na pole
    const int N = 10;
    int A[N] {0,1,2,3,4,5}, *pi, *pi2;

    // oba pøípady by mìly být stejné
    cout << "Adresa ukazatele \"A[N]\" je: "<< &A << " kde adresa na A[0] je: " << &A[0] << " a hodnota je: " << A[0] << endl;

    pi = A;
    cout << "Adresa ukazatele \"pi\" je: "<< &pi << " kde adresa na pi[0] je: " << pi << " a hodnota je: " << pi[0] << endl;

    pi2 = &A[0];
    cout << "Adresa ukazatele \"pi2\" je: "<< &pi2 << " kde adresa na pi2[0] je: " << pi2 << " a hodnota je: " << pi2[0] << endl;

}

