#include <iostream>
#include <cstring>
#include <math.h>
#include <iomanip>      // std::setprecision
#include <algorithm>
#include <utility>
#include <tuple>
#include <experimental/tuple>
#include "13_funkce.h"
#include "06_zakladni_datove_typy.h" // class Bod

using namespace std;

//
// P��KLAD 13.19: LAMBDA-V�RAZ
//

auto vypis_volani_lambda_vyraz() -> void
{
    // lambda v�raz
    // Jestli�e chceme vytvo�it lambda-v�raz pro v�po�et t�et� mocniny re�ln�ho ��sla, ulo�it ho do prom�nn� a pozd�ji ho
    // pou��t, deklarujeme prom�nnou se specifikac� typu auto a inicializujeme ji:
    auto moc3_lambda = [](double x) -> double
    {
        return x*x*x;
    };

    double y = moc3_lambda(3);
    cout << y;
}

//
// P��KLAD 13.18: ZOBRAZEN� HODNOT FUNKCE
//

void zahlavi(std::string jmeno)
{
    cout << __func__ << ": " << jmeno << endl;
}

double sqr_mark(double x)
{
    return x*x;
}

static int pocet_stupnu = 20;
static char symbol = '*';

void nastav_diagram(char symbol, int pocet_stupnu)
{
    ::symbol = symbol;
    ::pocet_stupnu = pocet_stupnu;
}

// druh zobrazen�
void tabelace(double *x, double *y, int kolik, string jmeno)
{
    zahlavi(jmeno);
    cout << fixed << setprecision(2);
    for (int i = 0; i < kolik; i++)
    {
        cout << x[i] << " " << y[i] << endl;
    }
}

// druh zobrazen�
void diagram(double *x, double *y, int kolik, string jmeno)
{
    double max = *max_element(y, y + kolik);
    // I kdy� takov�to prvek neexistuje (pole y m� kolik prvk�, tak�e posledn� m� index kolik � 1),
    // je tato konstrukce spr�vn�. Standard jazyka C++ v�slovn� dovoluje pou��t adresu prvku pole
    // za posledn�m pro ur�en� konce �seku. Nesm�me v�ak manipulovat s obsahem tohoto neexistuj�c�ho prvku.

    double krok_y = max / pocet_stupnu;
    cout << "Diagram funkce " << jmeno << endl
         << "--------------------" << endl << endl;
    cout << fixed << setprecision(2);
    // Manipul�tor fixed p�edepisuje v�stup re�ln�ch ��sel ve tvaru s pevnou ��dovou ��rkou,
    // manipul�tor setprecision(n) nastavuje po�et desetinn�ch m�st.
    // O manipul�torech budeme podrobn�ji hovo�it v odd�lu 19.2.3.

    for (int k = 0; k < kolik; k++)
    {
        cout << x[k] << " ";

        int poloha = round(y[k] / krok_y);
        cout << (char)((poloha == 0) ? symbol : '|' );
        for (int i = 1; i <= pocet_stupnu; i++)
        {
            char znak = (i == poloha) ? symbol : ' ';
            cout << znak;
        }
        cout << endl;
    }
}

// zobrazen� matematick� funkce v zadan�m intervalu
void graf(mat_funkce f, zobr_funkce zobraz, double od, double po,
          int kolik, string jmeno)
{
    double krok = (po - od) / (kolik - 1);
    double *X = new double[kolik] {};
    double *Y = new double[kolik] {};
    for (int i = 0; i < kolik; i++)
    {
        X[i] = od + i*krok;
        Y[i] = f(X[i]); // vol�me funkci p�edanou ukazatelem
    }
    zobraz(X, Y, kolik, jmeno); // vol�me funkci p�edanou ukazatelem
    delete[] X;
    delete[] Y;
}


void vypis_volani_funkce_graf_pres_ukazatel()
{
    graf(sqr_mark, tabelace, 0, 1, 11, "sqr_mark");
    nastav_diagram('o', 30);
    graf(sin, diagram, 0, 3.14, 20, "sin");
    graf(cos, diagram, 0, 3.14, 20, "cos");

    // pou�it� lambda v�razu p�i p�ed�v�n� ukazatele na funkci
    graf([](double x)->double{return 1/(1+x*x);},tabelace, 0, 1, 11, "zvon");
}

//
// P��KLAD 13.17: DEKLARACE UKAZATELE NA FUNKCI
//

//Za�neme n�kolika jednoduch�mi p��klady. Deklarace
// double (*faaa1)(double){};
//zav�d� ukazatel na funkci typu double s jedn�m parametrem typu double. Deklarace
double *(*faaa2)(double x);
//zav�d� ukazatel na funkci typu double* (tedy vracej�c� ukazatel na double) s jedn�m parametrem typu dou-
//ble. A je�t� se pod�vejme na n�co slo�it�j��ho. Deklarace
double(*fce1(double(*f)()))();
//zav�d� funkci, je� dostane jako parametr ukazatel na funkci typu double bez parametr� a vrac� ukazatel t�ho�
//typu. Pom��eme-li si p�i deklarac� typu, bude v�e podstatn� p�ehledn�j��:
using uknafun = double(*)();
uknafun fce2(uknafun);

// ukazka p�i�azen�
auto vypis_ukazatel_na_funkci() -> void
{
    double (*faaa1)(double); // = &sin;
    faaa1 = sin; // or faaa1 = &sin;
    cout << faaa1(3.14) << endl;
    faaa1 = nullptr;
    // cout << faaa1(3.14) << endl; // ukazatel je jiz nullptr
}

//
// P��KLAD 13.16: V�CHOZ� HODNOTY PARAMETR�
//
double z = 0;
double zpracuj(double x = 3.14, double y = z);

// kde z je zadan� prom�nn�. P�eklada� tuto deklaraci nahrad� deklarac� trojice funkc�:
//double zpracuj(double x, double y);
//inline double zpracuj(double x; {return zpracuj(x, z); }
//inline double zpracuj() {return zpracuj(3.13, z); };

//
// P��KLAD 13.15: V�B�R P�ET͎EN� FUNKCE
//

//V programu jsou deklarov�ny funkce
void fs(int x, double y)
{
    cout<<1;
}; // 1
void fs(int x, int y)
{
    cout<<2;
}; // 2
void fs()
{
    cout<<3;
}; // 3
void fs(char z)
{
    cout<<4;
}; // 4
// a �ablona
template<class T>void fs(T x)
{
    cout << 5;
}; // 5

auto vypis_vyber_pretizene_funkce()->void
{
    fs('z'); // 4
    fs(1); // 5 - pou�ije �ablonu s jedn�m form�ln�m parametrem, jeliko� neexistuje p�esn� deklarace pro toto vol�n�
    fs(1,1); // 2
    fs(1.1,1.1); // 1
    unsigned char c;
    fs(c); // 5 - pou�ije �ablonu s jedn�m form�ln�m parametrem, jeliko� neexistuje p�esn� deklarace pro toto vol�n�

    // fs(1, 0.0L); // vyvol� chybu

    fs(1, (double)5); // 1

}

//
// 13.3 P�et�ov�n� funkc�
// P��KLAD 13.13: FUNKCE PRO V�PO�ET PLOCHY TROJ�HELN�KA
//

double plocha(double zakladna, double vyska)
{
    cout << "Volan� p�et�en� funcke �. 1" << endl;
} // 1
double plocha(double a, double b, double fi)
{
    cout << "Volan� p�et�en� funcke �. 2" << endl;
} // 2
double plocha(bod A, bod B, bod C)
{
    cout << "Volan� p�et�en� funcke �. 3" << endl;
} // 3

// rozli�en�, ale, vhodn�j�� bude pou��t structuru pro rozli�en�
//double plocha(double a, double b, double fi, int)
//{
//    cout << "Volan� p�et�en� funcke �. 4" << endl;
//} // 4

struct Rozliseni {} Heron;
double plocha(double a, double b, double fi, Rozliseni)
{
    cout << "Volan� p�et�en� funcke �. 4 s rozli�en�m pomoci struktury" << endl;
} // 4

struct Rozliseni2 {} Maron;
double plocha(double a, double b, double fi, Rozliseni2)
{
    cout << "Volan� p�et�en� funcke �. 5 s rozli�en�m pomoci struktury" << endl;
} // 5

auto vypis_vysledku_pretizeni_funkce_vypoctu_plochy_trojuhelnika()->void
{
    char *pChar = new(nothrow) char; // jen tak

    double x,y,z;
    plocha(x,y);
    plocha(x,y,z);
    plocha(x,y,z, Heron);
    plocha(x,y,z, Maron);

    delete pChar;
}

//
// P��KLAD 13.12: NEPOJMENOVAN� PARAMETRY
//
auto nepojmenovane_parametry(int n, int, char) -> void
{
    // parametry 2 a 3 nelze ve funkci pou��t
    return;
}
auto vypis_nepojmenovane_parametry() -> void
{

    nepojmenovane_parametry(1,2,'A');
}

//
// P��KLAD 13.11: VARIADICK� �ABLONA - Jedn� se o velmi pokro�il� t�ma
//
// Jinou mo�nost, jak deklarovat funkci s prom�nn�m po�tem parametr�, p�edstavuj� �ablony
// funkc� s prom�nn�m po�tem �ablonov�ch parametr� (tzv. variadick� �ablony).

// Zav�d� funkci Max() s prom�nn�m po�tem parametr� celo��seln�ch typ�
// pro ur�en� nejv�t�� z p�edan�ch hodnot.

template<typename T1, typename ... Typy>
decltype(auto) MujMax(T1 n, Typy...arg)
{
    // P�istup k prvn�mu parametru (n)
    cout << "Prvn� parametr: " << n << endl;

    // P�istup k ostatn�m parametr�m pomoc� skl�d�n� v�raz� (fold expression)
    ( (cout << "Dal�� parametr: " << arg << endl), ...);

    // M��ete tak� prov�d�t operace s parametry
    decltype(auto) suma = (n + ... + arg);
    cout << "Sou�et parametr�: " << suma << endl;

    return n;
}
// Kdy� p�eklada� naraz� na p��kaz
auto vypis_funkci_variadicke_sablony() ->void
{
    double x = 1;
    decltype(auto) y = MujMax(1, 'A', x, 1);
    cout << "V�sledek funkce: " << y << endl;
}

//
// P��KLAD 13.10: FUNKCE PRINTF()
// int printf(const char *format, ...); // (ellipsis).

auto vypis_printf() -> void
{
    printf("\nprintf - Nazdar, bazar\n");
    int i{1},y{2};
    double cena{9.90};
    // int printf(const char *format, ...);
    printf("Po�et: %i, ypsilon: %i, cena: %f\n", i, y, cena);
}




//P�i p�ed�v�n� v�pustkou prob�hnou s celo��seln�mi parametry celo��seln� roz���en� (tak�e
//znakov� typy, v��tov� typy, typy short a unsigned short se roz���� na int, p��p. na unsigned int).

//Hodnoty typu float se p�i p�ed�v�n� v�pustkou roz���� na typ double.

//Uvedeme-li zde hodnotu objektov�ho typu, p�ed� se �bitov� kopie�
//(nepou�ije se tzv. kop�rovac� konstruktor).

//Proto se p�ed�v�n� objektov�ch typ� v�pustkou vyh�b�me.
//P�eklada� nekontroluje typy p�edan�ch hodnot.
//Zad�me-li nap��klad m�sto cel�ho ��sla ��slo re�ln�, m��e b�t v�sledek naprosto nesmysln�.

template<typename ... TypyParametru>
decltype(auto) vypustky(TypyParametru...arg)
{
    // Create std::tuple z p�edan�ch hodnot
    std::tuple<TypyParametru...> hodnoty(arg...);

   // print all the values from std::tuple
    std::experimental::fundamentals_v1::apply([](const auto&... args)
    {
        ((std::cout << args << " "), ...);
    }, hodnoty);

    std::cout << std::endl;
}

auto vypis_vypustky() -> void
{
    int a{0},b{0},c{1};
    double x{5},y{6},z{7};
    vypustky(a,b,c,x,y,z);
}


//
// P��KLAD 13.9: V�CHOZ� HODNOTY PARAMETR
//
// stdout vs stderr - pou��vat dle opodstatn�n� v�stupu, m� smysl pro v�stup do souboru
// kdy stdout se do souboru tiskne, a stderr nap�. ne

auto tisk_bez_impl_hodnoty (int hodnota, string jmeno, ostream& proud) -> void
{
    proud << "Hodnota bez impl: "  << jmeno << " : " << hodnota << endl;
}

auto tisk (int hodnota, std::string jmeno = "V�choz� jm�no", std::ostream& proud = std::cerr)
    -> void
{
    proud << "Hodnota: "  << jmeno << " : " << hodnota << endl;
}

auto vypis_tisk() -> void
{
    int pomocna{4};
    tisk(1);
    tisk(2, "Jirka");
    tisk(3, "Igor", cout);
    tisk(pomocna,"pomocn�");
    tisk(5); // Tentokr�t jsme vynechali posledn� dva parametry, tak�e p�eklada� za n� dosadit �et�zec "x" a proud cerr.

    tisk_bez_impl_hodnoty(1, "mus� b�t", cout);
    tisk_bez_impl_hodnoty(2, "Jirka", cerr);

    /*
        tisk_bez_impl_hodnoty(3, "Igor", cout);
        tisk_bez_impl_hodnoty(pomocna,"pomocn�");
        tisk_bez_impl_hodnoty(5); // Tentokr�t jsme vynechali posledn� dva parametry, tak�e p�eklada� za n� dosadit �et�zec "x" a proud cerr.
    */
}

//
// P��KLAD 13.8: PARAMETR P�EDAN� UKAZATELEM NA KONSTANTU
//
// Typick�m p��padem parametru p�edan�ho ukazatelem na konstantu m��e b�t knihovn� funkce
auto strlen_konstantni_ukazka(const char * str) -> size_t
{
    return strlen(str);
}
// deklarovan� v hlavi�kov�m souboru <string.h>,
// je� slou�� ke zji�t�n� d�lky nulou ukon�en�ho �et�zce typu char.
// Jej�m form�ln�m parametrem je ukazatel na konstantu typu char.
// !!! Skute�n�m parametrem m��e b�t jak�koli � i nekonstantn� � nulou ukon�en� �et�zec typu char.
auto volani_strlen_konstantni_ukazka() -> void
{
    char txt[] {"Ahoj"};
    // char *pTxt = txt; // to sam� jako v��e
    cout << endl << "strlen: " << strlen_konstantni_ukazka(txt) << endl;
}

//
// P��KLAD 13.7: HODNOTA FORM�LN�HO PARAMETRU
// Funkce 225
// P�i p�ed�v�n� odkazem p�edstavuje form�ln� parametr jin� jm�no pro skute�n� parametr, tak�e
// ve�ker� operace s form�ln�m parametrem prob�hnou se skute�n�m parametrem.

/*
Je-li form�ln�m parametrem pole, neuv�d�me v jeho specifikaci rozsah prvn�ho indexu. P�ipo-
me�me si, �e deklarace form�ln�ho parametru p�edstavuj�c�ho pole typu T m� stejn� v�znam
jako deklarace form�ln�ho parametru typu T*. To znamen�, �e nap��klad deklarace
void f(int A[]);
znamen� tot� co deklarace
void f(int *A);
Tak� deklarace
void g(int B[][2])
m� zcela stejn� v�znam jako deklarace
void g(int (*B)[2]);
*/


//
// P��KLAD 13.6: KONSTANTN� FUNKCE
//
// int moc3(int n) // nelze n�sledn� pou��t v z�chytu
constexpr int moc3(int n) // ok
{
    return n*n*n;
}

// deklarovat pole o 53, tedy o 125 prvc�ch
// Proto�e jsme t�to funkci p�edali jako parametr liter�l typu int,
// dok�e vypo��tat v�sledek p�eklada� a v�sledkem je konstanta s hodnotou 125.

int A[moc3(5)] {}; // definice konstanty pomoci konstantn� funkce constexpr moc3

void vypis_moc3()
{
    for (int i{0}; i<(moc3(5)); i++)
        cout << A[i] + i << " ";

    cout << endl;
}

//
// P��KLAD 13.5: UPOZORN�N� NA CHYBU V
//
void vypis_proverka(int i, int j)
{
    if (i == j)
    {
        cout << "Funkce " << __func__
             << ": upozorn�n� - rovnost parametr� ("
             << i << ")" << endl;
// ... a dal�� zpracov�n� ...
    }
}

//
// Zak�zan� funkce
// P��KLAD 13.4: ZAK�ZAN� FUNKCE
// Je-li t�lo funkce tvo�eno z�pisem = delete;  jde o tzv. zak�zanou funkci (deleted function).
//

// elegantn� �e�en� jak zamezit pou�it� funkce s jin�m tipem form�ln�ho parametru
template<typename T> void zpracuj(T x) = delete;
auto zpracuj(long long x) -> void
{
    // ...t�lo nen� d�le�it�...
    // pokud se tato funkce zavol� se spr�vn�m parametrem, vykon� se
    // pokud se tato funkce zavol� nap�. s argumentem int,
    // �ablona vytvo�� novou instanci funkce zpracuj<int>()
    // jen�e tato instance je zak�zan� definic� = delete
    // a p�eklada� to nedovol�
}

auto vypis_zakazana_funkce() -> void
{
    long long lcislo = 68;
    zpracuj(lcislo);
    cout << lcislo << endl;
    // zpracuj(68); // zakazana, nep�jde zkompilovat
}

//
// P��KLAD 13.3: NOV� TVAR HLAVI�KY FUNKCE
//
// Funkce m��e vracet hodnotu jak�hokoli datov�ho typu krom� pole a funkce. M��e v�ak vracet
// ukazatel na pole, ukazatel na funkci, referenci na pole a referenci na funkci. (Funkcemi, kter�
// vracej� reference, se zde nebudeme podrobn�ji zab�vat.)

//
// P��KLAD 13.2: SLO�IT�J�� HLAVI�KA
//

auto odmocnina(double d) -> double
{
    return sqrt(d);
}

double square(double x)
{
    return x * x;
}

double cube(double x)
{
    return x * x * x;
}


// Celkov� tedy funkce getFunction p�ij�m� ukazatel na funkci,
// kter� bere double a vrac� double,
// a sama vrac� ukazatel na funkci, kter� t� bere double a vrac� double.

double ( *getFunction ( double (*f) (double) ) ) (double); // klasick� hlavi�ka
auto getFunction(double(*f)(double)) -> double(*)(double) // nov� hlavi�ka
{
    return f;
}

// Poznamenejme, �e podstatn� p�ehledn�j�� bude, kdy� spole�n� typ v�sledku a parametru nejprve pojmenujeme:
// using ufun = double(*)(double);
// Hlavi�ka funkce funk() pak bude m�t tvar
// ufun funk(ufun f);
using ufun = double(*)(double);
ufun getFunction(ufun f);

auto vypis_vysledku_ukazatelu_na_funkce_double() -> void
{
    double(*vysledek)(double) = getFunction(odmocnina); // = double (*f) (double) )
    cout << vysledek(9) << endl; // Vyp�e 3.0

    double(*result)(double) = getFunction(square);
    cout << result(2.0) << endl; // Vyp�e 4.0

    result = getFunction(cube);
    cout << result(2.0) << endl; // Vyp�e 8.0
}

//
// P��KLAD 13.1: KLASICK� TVAR HLAVI�KY FUNKCE
//

// Funkce typu int (tedy vracej�c� int) s jedn�m parametrem typu int
static int funkceint(int n)
{
    return 0;
};

// Funkce typu char * s jedn�m parametrem typu char
static char *g(char *in)
{
    cout << "P�ed �pravou: " << in << endl;
    in[0] = 'B';
    return &in[0];
}

// Funkce vracej�c� referenci na double s parametrem typu long
static double &h(long *in)
{
    cout << "P�ed �pravou: " << *in << endl;
    *in = 99;
    cout << "Po �prav�: " << *in << endl;
    return (double&)*in;
};

// Funkce bez parametr� vracej�c� ukazatel na pole typu int o3 prvc�ch
static int ( *f() )[3]
{
    int *pole_ukazatelu = new int[3];
    int (*i)[3] = reinterpret_cast<int(*)[3]>(pole_ukazatelu);
    for (int y{0}; y<3; y++)
    (*i)[y] = 10+y;
    for (int y{0}; y<3; y++)
        cout << "vrac�m: " << (*i)[y] << endl;
    return i;
};

void vypis_volani_funkci()
{
    // vol�n� funkce, kter� je jako ukazatel
    char vstup[16] {"Ahoj"};
    char *pChar = g(&vstup[0]);
    if (pChar != nullptr)
        cout << "Po �prav�: " <<pChar<< endl;
    else
        cout << "pChar == nullptr" << endl;

    // vol�n� funkce, kter� vrac� referenci
    long vstup_long = 50;
    double realnecislo = h(&vstup_long);

    int ((*vracene_pole_int)[3]);
    vracene_pole_int = f();

    // funkce bez parametr� vracej�c� ukazatel na pole typu int o 3 prvc�ch
    for (int y{0}; y<3; y++)
        cout << "vrac�m: " << (*vracene_pole_int)[y] << endl;
}
