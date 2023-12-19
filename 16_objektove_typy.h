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
// P��KLAD 16.10: EXPLICITN� VOL�N� KONSTRUKTORU
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
// P��KLAD 16.7: EXPLICITN� KONSTRUKTOR
//
class vektor16
{
    int delka;
    double *pole;

public:
// konstruktory
// Inicializace p�edepsan� inicializa�n� ��st� prob�hnou je�t� p�ed vstupem do t�la konstruktoru,
// a to v po�ad�, v jak�m jsou uveden� slo�ky zaps�ny v deklaraci dan�ho objektov�ho typu
// (nez�le�� na po�ad�, v jak�m je zap�eme v inicializa�n� ��sti).

// Konstruktor deklarovan� s t�mto modifik�torem nesm� p�eklada� pou��t k implicitn� konverzi
    explicit vektor16(int n); // explicit zamez� pou�it� r = 11 v implementa�n� ��sti;
    vektor16(std::initializer_list<double> il); // INICIALIZACE VEKTORU SEZNAMEM INICIALIZ�TOR�
    vektor16(const double *arr, int length); // INICIALIZACE VEKTORU SEZNAMEM INICIALIZ�TOR� bez std:initializer

    ~vektor16();
// kop�rovac� konstruktor z knihy
    vektor16(const vektor16 & w) :vektor16(w.delka)
    {
        for (int i = 0; i < this->delka; i++)
        {
            this->pole[i] = w.pole[i];
        }
    }

// V kop�rovac�m konstruktoru vytv���me hlubokou kopii pole,
// aby nov� objekt obsahoval novou alokovanou pam� pro data
// a nedoch�zelo ke sd�len� dat mezi objekty.
    //vektor16(const vektor16& w);

// Kop�rovac� konstruktor
    /*
        vektor16(const vektor16 &other) : delka(other.delka), pole(new double[other.delka])
        {
            std::cout << "*** COPY ";
            std::copy(other.pole, other.pole + other.delka, pole);
        }
    */
// V st�hovac�m konstruktoru pou��v�me std::swap k v�m�n� hodnot mezi p�vodn�m objektem
// a nov�m objektem. St�hovac� konstruktor m��e b�t ozna�en za noexcept, co� signalizuje,
// �e neprov�d� ��dn� operace, kter� by mohly vyvolat v�jimku.

// St�hovac� konstruktor
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
// P��KLAD 16.16: VEKTOR JAKO SLO�KA SLO�IT�J�� T��DY
//
class mereni
{
    vektor16 vekt;
// ... a dal�� datov� slo�ky ...
public:
    mereni(int n);
    mereni(std::initializer_list<double> hodnoty);
    ~mereni();
    int pocet_mereni();
    friend auto vypis_vektor_jako_slozka_slozitejsi_tridy() -> void;
// ... a dal�� metody ...
};

//
// P��KLAD 16.6: KONVERZN� KONSTRUKTOR
//

struct komplex
{
    double re, im;

// Konstruktory a p�etypov�n�
// Konstruktory, kter� lze volat s jedn�m parametrem jin�ho typu ne� odkaz na �jejich� t��du,
// m��e p�eklada� pou��t k implicitn�m konverz�m typu parametru na typ t�to t��dy.
// Proto je �asto ozna�ujeme jako konverzn� konstruktory. Poznamenejme, �e konverzn� konstruktor
// m��e m�t i v�ce parametr�, ale pro druh� a dal�� mus� b�t deklarov�ny v�choz� hodnoty.
    komplex(double _re, double _im = 99.9)
        :re(_re), im{_im}
    { }
};

double fkomplex(komplex x);


//
// P��KLAD 16.5: INICIALIZA�N� ��ST KONSTRUKTORU
//

class bod16
{
    double x, y;
public:
    bod16(double x, double y);
    void set_x(double _x);
    void set_y(double _y);
// ...a dal�� slo�ky...
};

class usecka16
{
    bod16 pocatek;
    bod16 konec;
public:
    usecka16(double x1, double y1, double x2, double y2);
    // ...a dal�� slo�ky...
};






#endif // OBJEKTOVE_TYPY_H_INCLUDED
