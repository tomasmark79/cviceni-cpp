#ifndef OBJEKTOVE_TYPY_H_INCLUDED
#define OBJEKTOVE_TYPY_H_INCLUDED
using namespace std;
// #include "06_zakladni_datove_typy.h"
#include <initializer_list>

auto vypis_vektoru_pres_aliasy() -> void;
auto vypis_konverzni_konstruktor() -> void;
auto vypis_explicitni_konstruktor() -> void;
auto vypis_kopirovaci_a_stehovaci_konstruktor() -> void;
auto vypis_inicializace_vektoru_seznamem_inicializatoru_nebo_i_jinak() -> void;
auto vypis_explicitni_volani_konstruktoru() -> void;
auto vypis_pole_komplexnich_cisel() -> void;
auto vypis_sprateleny_operator_plus() -> void;
auto vypis_delegovani_konstruktoru() -> void;
auto vypis_kopirovani_vektoru() -> void;
auto vypis_prirazovani_vektoru() -> void;
auto vypis_vektor_jako_slozka_slozitejsi_tridy() -> void;
auto vypis_imaginarni_jednotka() -> void;
auto vypis_konstantni_instance() -> void;



//
// PØÍKLAD 16.10: EXPLICITNÍ VOLÁNÍ KONSTRUKTORU
//
class komplex16
{
    double re, im;
public:

    komplex16(double _re = 0, double _im = 0);

    komplex16 plus(komplex16 a);

    ~komplex16();

    static const komplex16 i;
    static const komplex16 nula;


    friend auto vypis_explicitni_volani_konstruktoru() -> void;
    friend auto vypis_pole_komplexnich_cisel() -> void;
    friend auto vypis_imaginarni_jednotka() -> void;


    friend auto spratelena_definice_tridy() -> void
    {
        ;// int a = 0;
    };
    friend class vektor16;
};

//
// PØÍKLAD 16.7: EXPLICITNÍ KONSTRUKTOR
//
class vektor16
{
    int delka;
    double *pole;

public:
// konstruktory
// Inicializace pøedepsané inicializaèní èástí probìhnou ještì pøed vstupem do tìla konstruktoru,
// a to v poøadí, v jakém jsou uvedené sloky zapsány v deklaraci daného objektového typu
// (nezáleí na poøadí, v jakém je zapíšeme v inicializaèní èásti).

// Konstruktor deklarovanı s tímto modifikátorem nesmí pøekladaè pouít k implicitní konverzi
    explicit vektor16(int n); // explicit zamezí pouití r = 11 v implementaèní èásti;
    vektor16(std::initializer_list<double> il); // INICIALIZACE VEKTORU SEZNAMEM INICIALIZÁTORÙ
    vektor16(const double *arr, int length); // INICIALIZACE VEKTORU SEZNAMEM INICIALIZÁTORÙ bez std:initializer

    ~vektor16();
// kopírovací konstruktor z knihy
    vektor16(const vektor16 & w) :vektor16(w.delka)
    {
        for (int i = 0; i < this->delka; i++)
        {
            this->pole[i] = w.pole[i];
        }
    }

// V kopírovacím konstruktoru vytváøíme hlubokou kopii pole,
// aby novı objekt obsahoval novou alokovanou pamì pro data
// a nedocházelo ke sdílení dat mezi objekty.
    //vektor16(const vektor16& w);

// Kopírovací konstruktor
    /*
        vektor16(const vektor16 &other) : delka(other.delka), pole(new double[other.delka])
        {
            std::cout << "*** COPY ";
            std::copy(other.pole, other.pole + other.delka, pole);
        }
    */
// V stìhovacím konstruktoru pouíváme std::swap k vımìnì hodnot mezi pùvodním objektem
// a novım objektem. Stìhovací konstruktor mùe bıt oznaèen za noexcept, co signalizuje,
// e neprovádí ádné operace, které by mohly vyvolat vıjimku.

// Stìhovací konstruktor
    /*vektor16(vektor16 &&other) noexcept : delka(0), pole(nullptr)
    {
        std::cout << "*** MOVE ";
        std::swap(delka, other.delka);
        std::swap(pole, other.pole);
    }
    */

    friend vektor16 operator+(vektor16 u, vektor16 w);
    vektor16        operator-(vektor16 w);
    vektor16&       operator=(vektor16& v);

    void vypis();
    friend auto vypis_kopirovaci_a_stehovaci_konstruktor() -> void;
    friend auto vypis_delegovani_konstruktoru() -> void;
    friend auto vypis_explicitni_konstruktor() -> void;
    friend auto vypis_inicializace_vektoru_seznamem_inicializatoru_nebo_i_jinak() -> void;
    friend auto vypis_sprateleny_operator_plus() -> void;
    friend auto vypis_kopirovani_vektoru() -> void;
    friend auto vypis_prirazovani_vektoru() -> void;
    friend auto vypis_vektor_jako_slozka_slozitejsi_tridy() -> void;
    void nastav(int index, double hodnota);

    int velikost();
};

//
// PØÍKLAD 16.16: VEKTOR JAKO SLOKA SLOITÌJŠÍ TØÍDY
//
class mereni
{
    vektor16 vekt;
// ... a další datové sloky ...
public:
    mereni(int n);
    mereni(std::initializer_list<double> hodnoty);
    ~mereni();
    int pocet_mereni();
    friend auto vypis_vektor_jako_slozka_slozitejsi_tridy() -> void;
// ... a další metody ...
};

//
// PØÍKLAD 16.6: KONVERZNÍ KONSTRUKTOR
//

struct komplex
{
    double re, im;

// Konstruktory a pøetypování
// Konstruktory, které lze volat s jedním parametrem jiného typu ne odkaz na „jejich“ tøídu,
// mùe pøekladaè pouít k implicitním konverzím typu parametru na typ této tøídy.
// Proto je èasto oznaèujeme jako konverzní konstruktory. Poznamenejme, e konverzní konstruktor
// mùe mít i více parametrù, ale pro druhı a další musí bıt deklarovány vıchozí hodnoty.
    komplex(double _re, double _im = 99.9)
        :re(_re), im{_im}
    { }
};

double fkomplex(komplex x);


//
// PØÍKLAD 16.5: INICIALIZAÈNÍ ÈÁST KONSTRUKTORU
//

class bod16
{
    double x, y;
public:
    bod16(double x, double y);
    void set_x(double _x);
    void set_y(double _y);
// ...a další sloky...
};

class usecka16
{
    bod16 pocatek;
    bod16 konec;
public:
    usecka16(double x1, double y1, double x2, double y2);
    // ...a další sloky...
};






#endif // OBJEKTOVE_TYPY_H_INCLUDED
