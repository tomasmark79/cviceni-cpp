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

/* Pr�ce s pam�t� 161
P��KLAD 9.5: OTO�EN� �ET�ZCE NA M�ST�
Tak� funkci pro oto�en� �et�zce na m�st� m��eme implementovat s vyu�it�m adresov� aritmetiky. Pod�vejme se na
zdrojov� k�d:
*/
// nen� nutn� pou��vat, jedn� se sp�e o folkl�r C++ ke kter�mu tato funkce neodmysliteln� pat��
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

/* Pod�vejme se na mo�nou implementaci funkce pro ur�en� d�lky znakov�ho �et�zce zalo�enou na pou�it� adresov�
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
char texty[][delka_zprav] = { "Chyb� adresa", "Nespr�vn� PS�",
                              "Neexistuje obec", "Nespr�vn� ulice", "Nespr�vn� ��slo domu",
                              "Adres�t nezn�m�"
                            };
*/
// deklarace s inicializaci pomoci ukazatele
char *chybove_texty[] =
{
    "Chyb� adresa", "Nespr�vn� PS�","Neexistuje obec", "Nespr�vn� ulice", "Nespr�vn� ��slo domu",
    "Adres�t nezn�m�", "AbrakaDabra Ope Se Za Mi"
};
char *chyba_chyby = "Nezn�m� chyba";

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

// To znamen�, �e nap��klad ukazatel na jednorozm�rn� pole typu int o 6 prvc�ch m��eme deklarovat z�pisem:
// int i[6] {1,2,3,4,5}, (*pi)[6];
// pi = i;
// pi = i;

//    cout << "Hodnota neobjektov� prom�nn� o velikosti jenoho pole na adrese " << &pi << " je " << ((int*)*pi[0]) << endl;

// Vynech�me-li z�vorky, dostaneme deklaraci pole ukazatel�. To znamen�, �e nap��klad deklarace:
//  int * pi2[6]; // zav�d� pole 6 ukazatel� na int.


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
    /*Chceme-li zavolat funkci s parametrem p�edstavuj�c�m referenci na r-hodnotu a pot�ebujeme-li j� p�itom p�edat
    l-hodnotu, vyu�ijeme knihovn� funkce move() deklarovanou v hlavi�kov�m souboru <utility>, nap��-
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

    // p�ed�v�n� parametr� odkazem se hod�, kdy� pot�ebujeme, aby funkce m�nila sv� parametry
    int an {1}, bn{2};
    prohod_promenne_pomoci_reference(an, bn); //
    cout << "an " << an << " bn " << bn << endl;
    swap<int>(an,bn); //
    cout << "an " << an << " bn " << bn << endl;

    // odkazovan� prom�nn� &
    int absint = 8;
    int &ref_absint = absint;
    ref_absint = 45;
    int *p_absint = &ref_absint;
    cout << ref_absint << " adresa " << p_absint << endl;

    // dynamick� pole
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

    // dynamick� pole v�cerozm�rn�
    // int(*pppp)[2][3][4] = new int[3][2][3][4];
    // ukazatel na dvourozm�rn� pole s inicializac�
    //  ukazatel=[]                0 1   0 1   0 1
    int(*ppp)[2] = new(nothrow) int[3][2] { {1,2},{3,4},{5,6} };
    //                            0     1     2
    cout << ppp[1][1] << endl;
    delete [] ppp;

    // dvourozm�rn� pole
    int(*qq)[2] = new(nothrow) int[1][2] { {1,2}, {3,4} };
    cout << qq[0][0] << endl;
    delete [] qq; // Oper�tor delete nem�n� obsah ukazatele


    char * pozdr {"Dobr� den"};
    cout << pozdr << endl << endl;

    cout << "sizeof texty = " << sizeof(chybove_texty) << " char* sizeof = " << sizeof(char*) << endl;
    cout << "pod�l = " << sizeof(chybove_texty)/sizeof(char*) << endl << endl;

    int pocet_zprav = sizeof(chybove_texty) / sizeof(char*);
    vypis_chyboveho_textu_dle_parametru(1);
    vypis_chyboveho_textu_dle_parametru(2);
    vypis_chyboveho_textu_dle_parametru(pocet_zprav);

    cout << endl;

    // 9.2.3 Adresov� aritmetika
    // delka3
    char text[20] {"abcdefg"};
    size_t delka3_n = delka_retezce_adresova_aritmetika(text);
    cout << "Adresov� aritmetika: " << endl << "D�lka �et�zce " << text << " je: " << delka3_n << endl << endl;

    // vol�n� funkce a p�ed�n� pole p�es ukazatele a oto�en� na m�st�
    char zadanonamiste[11] {"Robotizace"};
    cout << "Zad�no: " << zadanonamiste << " Oto�eno na m�st�: " << otoc_retezec_na_miste(zadanonamiste) << endl;


    // vol�n� funkce a p�ed�n� pole p�es ukazatele a n�vrat pole p�es ukazatele
    const char zadano[11] {"Robotizace"};
    char otoceno [11];
    cout << "Zad�no: " << zadano << " Oto�eno: " << otoc_retezec(zadano, otoceno) << endl << endl;


    // prohozeni promenn�ch pomoc� ukazatel�
    int x {5}, y{10};

    cout << "X: " << x << " Y: " << y << endl;
    prohod_promenne(&x, &y);
    cout << "X: " << x << " Y: " << y << endl;

    // ukazatel na prom�nnou
    int n {6}, *p;

    // NELZE
    // *p = n; // NELZE - *p neni inicializovan
    /*  T�m ulo��te hodnotu prom�nn� n na adrese, na kterou ukazuje p.
    To znamen�,�e hodnota prom�nn� n bude ulo�ena na m�st�, kam ukazuje p. */

    // LZE - NEP��M� P��STUP S U�IT�M UKAZATELE
    p = &n; // T�m p�i�ad�te ukazateli p adresu prom�nn� n. Te� p ukazuje na pam�ovou adresu prom�nn� n.
    // &p vyp�e adresu samotn�ho ukazatele p.
    // p vyp�e adresu, na kterou ukazuje ukazatel p.
    cout << "Adresa samotn�ho ukazatele \"p\" je: " << &p << endl;
    cout << "Kde�to, Adresa na kterou ukazatel \"p\" ukazuje je: " << p << " a hodnota typu INT na t�to adrese je: " << *p << endl;
    cout << endl;


    // Ukazatel bez dom�nov�ho typu VOID
    // P�etypov�n� ukazatele
    void *v;
    int cislo = 1; // P��klad s dereferenc� ukazatele bez p�i�azen� hodnoty m��e zp�sobit nedefinovan� chov�n� nebo dokonce p�d programu.
    v = &cislo; // !!! - Ne� budete cht�t pracovat s ukazatelem, m�l byste mu p�i�adit platnou adresu pam�ti
    cislo = *(int*)v; //Prom�nnou v jsme nejprve p�etypovali na int* a pak jsme ji dereferencovali.

    // ukazatele na pole
    const int N = 10;
    int A[N] {0,1,2,3,4,5}, *pi, *pi2;

    // oba p��pady by m�ly b�t stejn�
    cout << "Adresa ukazatele \"A[N]\" je: "<< &A << " kde adresa na A[0] je: " << &A[0] << " a hodnota je: " << A[0] << endl;

    pi = A;
    cout << "Adresa ukazatele \"pi\" je: "<< &pi << " kde adresa na pi[0] je: " << pi << " a hodnota je: " << pi[0] << endl;

    pi2 = &A[0];
    cout << "Adresa ukazatele \"pi2\" je: "<< &pi2 << " kde adresa na pi2[0] je: " << pi2 << " a hodnota je: " << pi2[0] << endl;

}

