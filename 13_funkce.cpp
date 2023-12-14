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
// PØÍKLAD 13.19: LAMBDA-VÝRAZ
//

auto vypis_volani_lambda_vyraz() -> void
{
    // lambda výraz
    // Jestliže chceme vytvoøit lambda-výraz pro výpoèet tøetí mocniny reálného èísla, uložit ho do promìnné a pozdìji ho
    // použít, deklarujeme promìnnou se specifikací typu auto a inicializujeme ji:
    auto moc3_lambda = [](double x) -> double
    {
        return x*x*x;
    };

    double y = moc3_lambda(3);
    cout << y;
}

//
// PØÍKLAD 13.18: ZOBRAZENÍ HODNOT FUNKCE
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

// druh zobrazení
void tabelace(double *x, double *y, int kolik, string jmeno)
{
    zahlavi(jmeno);
    cout << fixed << setprecision(2);
    for (int i = 0; i < kolik; i++)
    {
        cout << x[i] << " " << y[i] << endl;
    }
}

// druh zobrazení
void diagram(double *x, double *y, int kolik, string jmeno)
{
    double max = *max_element(y, y + kolik);
    // I když takovýto prvek neexistuje (pole y má kolik prvkù, takže poslední má index kolik – 1),
    // je tato konstrukce správná. Standard jazyka C++ výslovnì dovoluje použít adresu prvku pole
    // za posledním pro urèení konce úseku. Nesmíme však manipulovat s obsahem tohoto neexistujícího prvku.

    double krok_y = max / pocet_stupnu;
    cout << "Diagram funkce " << jmeno << endl
         << "--------------------" << endl << endl;
    cout << fixed << setprecision(2);
    // Manipulátor fixed pøedepisuje výstup reálných èísel ve tvaru s pevnou øádovou èárkou,
    // manipulátor setprecision(n) nastavuje poèet desetinných míst.
    // O manipulátorech budeme podrobnìji hovoøit v oddílu 19.2.3.

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

// zobrazení matematické funkce v zadaném intervalu
void graf(mat_funkce f, zobr_funkce zobraz, double od, double po,
          int kolik, string jmeno)
{
    double krok = (po - od) / (kolik - 1);
    double *X = new double[kolik] {};
    double *Y = new double[kolik] {};
    for (int i = 0; i < kolik; i++)
    {
        X[i] = od + i*krok;
        Y[i] = f(X[i]); // voláme funkci pøedanou ukazatelem
    }
    zobraz(X, Y, kolik, jmeno); // voláme funkci pøedanou ukazatelem
    delete[] X;
    delete[] Y;
}


void vypis_volani_funkce_graf_pres_ukazatel()
{
    graf(sqr_mark, tabelace, 0, 1, 11, "sqr_mark");
    nastav_diagram('o', 30);
    graf(sin, diagram, 0, 3.14, 20, "sin");
    graf(cos, diagram, 0, 3.14, 20, "cos");

    // použití lambda výrazu pøi pøedávání ukazatele na funkci
    graf([](double x)->double{return 1/(1+x*x);},tabelace, 0, 1, 11, "zvon");
}

//
// PØÍKLAD 13.17: DEKLARACE UKAZATELE NA FUNKCI
//

//Zaèneme nìkolika jednoduchými pøíklady. Deklarace
// double (*faaa1)(double){};
//zavádí ukazatel na funkci typu double s jedním parametrem typu double. Deklarace
double *(*faaa2)(double x);
//zavádí ukazatel na funkci typu double* (tedy vracející ukazatel na double) s jedním parametrem typu dou-
//ble. A ještì se podívejme na nìco složitìjšího. Deklarace
double(*fce1(double(*f)()))();
//zavádí funkci, jež dostane jako parametr ukazatel na funkci typu double bez parametrù a vrací ukazatel téhož
//typu. Pomùžeme-li si pøi deklarací typu, bude vše podstatnì pøehlednìjší:
using uknafun = double(*)();
uknafun fce2(uknafun);

// ukazka pøiøazení
auto vypis_ukazatel_na_funkci() -> void
{
    double (*faaa1)(double); // = &sin;
    faaa1 = sin; // or faaa1 = &sin;
    cout << faaa1(3.14) << endl;
    faaa1 = nullptr;
    // cout << faaa1(3.14) << endl; // ukazatel je jiz nullptr
}

//
// PØÍKLAD 13.16: VÝCHOZÍ HODNOTY PARAMETRÙ
//
double z = 0;
double zpracuj(double x = 3.14, double y = z);

// kde z je zadaná promìnná. Pøekladaè tuto deklaraci nahradí deklarací trojice funkcí:
//double zpracuj(double x, double y);
//inline double zpracuj(double x; {return zpracuj(x, z); }
//inline double zpracuj() {return zpracuj(3.13, z); };

//
// PØÍKLAD 13.15: VÝBÌR PØETÍŽENÉ FUNKCE
//

//V programu jsou deklarovány funkce
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
// a šablona
template<class T>void fs(T x)
{
    cout << 5;
}; // 5

auto vypis_vyber_pretizene_funkce()->void
{
    fs('z'); // 4
    fs(1); // 5 - použije šablonu s jedním formálním parametrem, jelikož neexistuje pøesná deklarace pro toto volání
    fs(1,1); // 2
    fs(1.1,1.1); // 1
    unsigned char c;
    fs(c); // 5 - použije šablonu s jedním formálním parametrem, jelikož neexistuje pøesná deklarace pro toto volání

    // fs(1, 0.0L); // vyvolá chybu

    fs(1, (double)5); // 1

}

//
// 13.3 Pøetìžování funkcí
// PØÍKLAD 13.13: FUNKCE PRO VÝPOÈET PLOCHY TROJÚHELNÍKA
//

double plocha(double zakladna, double vyska)
{
    cout << "Volaná pøetížená funcke è. 1" << endl;
} // 1
double plocha(double a, double b, double fi)
{
    cout << "Volaná pøetížená funcke è. 2" << endl;
} // 2
double plocha(bod A, bod B, bod C)
{
    cout << "Volaná pøetížená funcke è. 3" << endl;
} // 3

// rozlišení, ale, vhodnìjší bude použít structuru pro rozlišení
//double plocha(double a, double b, double fi, int)
//{
//    cout << "Volaná pøetížená funcke è. 4" << endl;
//} // 4

struct Rozliseni {} Heron;
double plocha(double a, double b, double fi, Rozliseni)
{
    cout << "Volaná pøetížená funcke è. 4 s rozlišením pomoci struktury" << endl;
} // 4

struct Rozliseni2 {} Maron;
double plocha(double a, double b, double fi, Rozliseni2)
{
    cout << "Volaná pøetížená funcke è. 5 s rozlišením pomoci struktury" << endl;
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
// PØÍKLAD 13.12: NEPOJMENOVANÉ PARAMETRY
//
auto nepojmenovane_parametry(int n, int, char) -> void
{
    // parametry 2 a 3 nelze ve funkci použít
    return;
}
auto vypis_nepojmenovane_parametry() -> void
{

    nepojmenovane_parametry(1,2,'A');
}

//
// PØÍKLAD 13.11: VARIADICKÁ ŠABLONA - Jedná se o velmi pokroèilé téma
//
// Jinou možnost, jak deklarovat funkci s promìnným poètem parametrù, pøedstavují šablony
// funkcí s promìnným poètem šablonových parametrù (tzv. variadické šablony).

// Zavádí funkci Max() s promìnným poètem parametrù celoèíselných typù
// pro urèení nejvìtší z pøedaných hodnot.

template<typename T1, typename ... Typy>
decltype(auto) MujMax(T1 n, Typy...arg)
{
    // Pøistup k prvnímu parametru (n)
    cout << "První parametr: " << n << endl;

    // Pøistup k ostatním parametrùm pomocí skládání výrazù (fold expression)
    ( (cout << "Další parametr: " << arg << endl), ...);

    // Mùžete také provádìt operace s parametry
    decltype(auto) suma = (n + ... + arg);
    cout << "Souèet parametrù: " << suma << endl;

    return n;
}
// Když pøekladaè narazí na pøíkaz
auto vypis_funkci_variadicke_sablony() ->void
{
    double x = 1;
    decltype(auto) y = MujMax(1, 'A', x, 1);
    cout << "Výsledek funkce: " << y << endl;
}

//
// PØÍKLAD 13.10: FUNKCE PRINTF()
// int printf(const char *format, ...); // (ellipsis).

auto vypis_printf() -> void
{
    printf("\nprintf - Nazdar, bazar\n");
    int i{1},y{2};
    double cena{9.90};
    // int printf(const char *format, ...);
    printf("Poèet: %i, ypsilon: %i, cena: %f\n", i, y, cena);
}




//Pøi pøedávání výpustkou probìhnou s celoèíselnými parametry celoèíselná rozšíøení (takže
//znakové typy, výètové typy, typy short a unsigned short se rozšíøí na int, pøíp. na unsigned int).

//Hodnoty typu float se pøi pøedávání výpustkou rozšíøí na typ double.

//Uvedeme-li zde hodnotu objektového typu, pøedá se „bitová kopie“
//(nepoužije se tzv. kopírovací konstruktor).

//Proto se pøedávání objektových typù výpustkou vyhýbáme.
//Pøekladaè nekontroluje typy pøedaných hodnot.
//Zadáme-li napøíklad místo celého èísla èíslo reálné, mùže být výsledek naprosto nesmyslný.

template<typename ... TypyParametru>
decltype(auto) vypustky(TypyParametru...arg)
{
    // Create std::tuple z pøedaných hodnot
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
// PØÍKLAD 13.9: VÝCHOZÍ HODNOTY PARAMETR
//
// stdout vs stderr - používat dle opodstatnìní výstupu, má smysl pro výstup do souboru
// kdy stdout se do souboru tiskne, a stderr napø. ne

auto tisk_bez_impl_hodnoty (int hodnota, string jmeno, ostream& proud) -> void
{
    proud << "Hodnota bez impl: "  << jmeno << " : " << hodnota << endl;
}

auto tisk (int hodnota, std::string jmeno = "Výchozí jméno", std::ostream& proud = std::cerr)
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
    tisk(pomocna,"pomocná");
    tisk(5); // Tentokrát jsme vynechali poslední dva parametry, takže pøekladaè za nì dosadit øetìzec "x" a proud cerr.

    tisk_bez_impl_hodnoty(1, "musí být", cout);
    tisk_bez_impl_hodnoty(2, "Jirka", cerr);

    /*
        tisk_bez_impl_hodnoty(3, "Igor", cout);
        tisk_bez_impl_hodnoty(pomocna,"pomocná");
        tisk_bez_impl_hodnoty(5); // Tentokrát jsme vynechali poslední dva parametry, takže pøekladaè za nì dosadit øetìzec "x" a proud cerr.
    */
}

//
// PØÍKLAD 13.8: PARAMETR PØEDANÝ UKAZATELEM NA KONSTANTU
//
// Typickým pøípadem parametru pøedaného ukazatelem na konstantu mùže být knihovní funkce
auto strlen_konstantni_ukazka(const char * str) -> size_t
{
    return strlen(str);
}
// deklarovaná v hlavièkovém souboru <string.h>,
// jež slouží ke zjištìní délky nulou ukonèeného øetìzce typu char.
// Jejím formálním parametrem je ukazatel na konstantu typu char.
// !!! Skuteèným parametrem mùže být jakýkoli – i nekonstantní – nulou ukonèený øetìzec typu char.
auto volani_strlen_konstantni_ukazka() -> void
{
    char txt[] {"Ahoj"};
    // char *pTxt = txt; // to samé jako výše
    cout << endl << "strlen: " << strlen_konstantni_ukazka(txt) << endl;
}

//
// PØÍKLAD 13.7: HODNOTA FORMÁLNÍHO PARAMETRU
// Funkce 225
// Pøi pøedávání odkazem pøedstavuje formální parametr jiné jméno pro skuteèný parametr, takže
// veškeré operace s formálním parametrem probìhnou se skuteèným parametrem.

/*
Je-li formálním parametrem pole, neuvádíme v jeho specifikaci rozsah prvního indexu. Pøipo-
meòme si, že deklarace formálního parametru pøedstavujícího pole typu T má stejný význam
jako deklarace formálního parametru typu T*. To znamená, že napøíklad deklarace
void f(int A[]);
znamená totéž co deklarace
void f(int *A);
Také deklarace
void g(int B[][2])
má zcela stejný význam jako deklarace
void g(int (*B)[2]);
*/


//
// PØÍKLAD 13.6: KONSTANTNÍ FUNKCE
//
// int moc3(int n) // nelze následnì použít v záchytu
constexpr int moc3(int n) // ok
{
    return n*n*n;
}

// deklarovat pole o 53, tedy o 125 prvcích
// Protože jsme této funkci pøedali jako parametr literál typu int,
// dokáže vypoèítat výsledek pøekladaè a výsledkem je konstanta s hodnotou 125.

int A[moc3(5)] {}; // definice konstanty pomoci konstantní funkce constexpr moc3

void vypis_moc3()
{
    for (int i{0}; i<(moc3(5)); i++)
        cout << A[i] + i << " ";

    cout << endl;
}

//
// PØÍKLAD 13.5: UPOZORNÌNÍ NA CHYBU V
//
void vypis_proverka(int i, int j)
{
    if (i == j)
    {
        cout << "Funkce " << __func__
             << ": upozornìní - rovnost parametrù ("
             << i << ")" << endl;
// ... a další zpracování ...
    }
}

//
// Zakázané funkce
// PØÍKLAD 13.4: ZAKÁZANÉ FUNKCE
// Je-li tìlo funkce tvoøeno zápisem = delete;  jde o tzv. zakázanou funkci (deleted function).
//

// elegantní øešení jak zamezit použití funkce s jiným tipem formálního parametru
template<typename T> void zpracuj(T x) = delete;
auto zpracuj(long long x) -> void
{
    // ...tìlo není dùležité...
    // pokud se tato funkce zavolá se správným parametrem, vykoná se
    // pokud se tato funkce zavolá napø. s argumentem int,
    // šablona vytvoøí novou instanci funkce zpracuj<int>()
    // jenže tato instance je zakázaná definicí = delete
    // a pøekladaè to nedovolí
}

auto vypis_zakazana_funkce() -> void
{
    long long lcislo = 68;
    zpracuj(lcislo);
    cout << lcislo << endl;
    // zpracuj(68); // zakazana, nepùjde zkompilovat
}

//
// PØÍKLAD 13.3: NOVÝ TVAR HLAVIÈKY FUNKCE
//
// Funkce mùže vracet hodnotu jakéhokoli datového typu kromì pole a funkce. Mùže však vracet
// ukazatel na pole, ukazatel na funkci, referenci na pole a referenci na funkci. (Funkcemi, které
// vracejí reference, se zde nebudeme podrobnìji zabývat.)

//
// PØÍKLAD 13.2: SLOŽITÌJŠÍ HLAVIÈKA
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


// Celkovì tedy funkce getFunction pøijímá ukazatel na funkci,
// která bere double a vrací double,
// a sama vrací ukazatel na funkci, která též bere double a vrací double.

double ( *getFunction ( double (*f) (double) ) ) (double); // klasická hlavièka
auto getFunction(double(*f)(double)) -> double(*)(double) // nová hlavièka
{
    return f;
}

// Poznamenejme, že podstatnì pøehlednìjší bude, když spoleèný typ výsledku a parametru nejprve pojmenujeme:
// using ufun = double(*)(double);
// Hlavièka funkce funk() pak bude mít tvar
// ufun funk(ufun f);
using ufun = double(*)(double);
ufun getFunction(ufun f);

auto vypis_vysledku_ukazatelu_na_funkce_double() -> void
{
    double(*vysledek)(double) = getFunction(odmocnina); // = double (*f) (double) )
    cout << vysledek(9) << endl; // Vypíše 3.0

    double(*result)(double) = getFunction(square);
    cout << result(2.0) << endl; // Vypíše 4.0

    result = getFunction(cube);
    cout << result(2.0) << endl; // Vypíše 8.0
}

//
// PØÍKLAD 13.1: KLASICKÝ TVAR HLAVIÈKY FUNKCE
//

// Funkce typu int (tedy vracející int) s jedním parametrem typu int
static int funkceint(int n)
{
    return 0;
};

// Funkce typu char * s jedním parametrem typu char
static char *g(char *in)
{
    cout << "Pøed úpravou: " << in << endl;
    in[0] = 'B';
    return &in[0];
}

// Funkce vracející referenci na double s parametrem typu long
static double &h(long *in)
{
    cout << "Pøed úpravou: " << *in << endl;
    *in = 99;
    cout << "Po úpravì: " << *in << endl;
    return (double&)*in;
};

// Funkce bez parametrù vracející ukazatel na pole typu int o3 prvcích
static int ( *f() )[3]
{
    int *pole_ukazatelu = new int[3];
    int (*i)[3] = reinterpret_cast<int(*)[3]>(pole_ukazatelu);
    for (int y{0}; y<3; y++)
    (*i)[y] = 10+y;
    for (int y{0}; y<3; y++)
        cout << "vracím: " << (*i)[y] << endl;
    return i;
};

void vypis_volani_funkci()
{
    // volání funkce, která je jako ukazatel
    char vstup[16] {"Ahoj"};
    char *pChar = g(&vstup[0]);
    if (pChar != nullptr)
        cout << "Po úpravì: " <<pChar<< endl;
    else
        cout << "pChar == nullptr" << endl;

    // volání funkce, která vrací referenci
    long vstup_long = 50;
    double realnecislo = h(&vstup_long);

    int ((*vracene_pole_int)[3]);
    vracene_pole_int = f();

    // funkce bez parametrù vracející ukazatel na pole typu int o 3 prvcích
    for (int y{0}; y<3; y++)
        cout << "vracím: " << (*vracene_pole_int)[y] << endl;
}
