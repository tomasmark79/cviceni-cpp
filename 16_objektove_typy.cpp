#include <iostream>
#include <vector>
#include <string>
#include "16_objektove_typy.h"
#include "zajimavosti.h"
#include "04_pokrocilejsi_konstrukce_a_techniky.h"

using namespace std;
// const int dim = 3;

//
// PØÍKLAD 16.18: KONSTANTNÍ NÁPIS
// Pøipomeòme si ještì jednou tøídu Napis,
// kterou jsme poprvé deklarovali voddílu 4.1.

auto vypis_konstantni_instance() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    const Napis napis("Poklona");
    napis.vypis();

}

//
// PØÍKLAD 16.17: IMAGINÁRNÍ JEDNOTKA
//
const komplex16 komplex16::i{ 0, 1 };
const komplex16 komplex16::nula{ 0, 0 };

auto vypis_imaginarni_jednotka() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;
    komplex16 z, w;
    z = w.plus(komplex16::i);
    cout << Tabs::getTabChars() << "z.re: " << z.re << "z.im: " << z.im << endl;
}

//
// PØÍKLAD 16.16: VEKTOR JAKO SLOŽKA SLOŽITÌJŠÍ TØÍDY
//

int vektor16::velikost()
{
    return delka;
}

mereni::mereni(int n) : vekt(n)
{
    Tabs::printLine("mereni::mereni(int n) : vekt(n)");
    Tabs::addTab();
}

mereni::mereni(initializer_list<double> hodnoty)
    : vekt(hodnoty)
{
    Tabs::printLine("mereni::mereni(initializer_list<double> hodnoty)");
    Tabs::addTab();
}

mereni::~mereni()
{
    Tabs::printLine("mereni::~mereni()");
    Tabs::decTab();
}

int mereni::pocet_mereni()
{
    return vekt.velikost();
}

auto vypis_vektor_jako_slozka_slozitejsi_tridy() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    mereni pocasi{ 1,2,33,44,5,6,7,8,9};
    cout << Tabs::getTabChars() << ">> mereni pocasi{1,2,33,44,5,6,7,8,9};: " << pocasi.pocet_mereni() << " hod.: ";
    for (int i{0}; i < pocasi.pocet_mereni(); i++)
        cout << pocasi.vekt.pole[i] << " ";
    cout << endl;

    mereni p1(pocasi);
    cout << Tabs::getTabChars() << ">> mereni p1(pocasi);: " << p1.pocet_mereni() << " hodnoty: ";
    for (int i{0}; i<p1.pocet_mereni(); i++)
        cout << p1.vekt.pole[i] << " ";
    cout << endl;

    mereni p2(6);
    cout << Tabs::getTabChars() << ">> mereni p2(6);: " << p2.pocet_mereni() << " hodnoty: ";
    for (int i{0}; i<p2.pocet_mereni(); i++)
        cout << p2.vekt.pole[i] << " ";
    cout << endl;

    p2 = pocasi;
    cout << Tabs::getTabChars() << ">> p2 = pocasi:; " << p2.pocet_mereni() << " hodnoty: ";
    for (int i{0}; i<p2.pocet_mereni(); i++)
        cout << p2.vekt.pole[i] << " ";
    cout << endl;
}

//
// PØÍKLAD 16.15: PØIØAZOVÁNÍ VEKTORÙ
//

vektor16& vektor16::operator=(vektor16& v)
{
    Tabs::printLine("vektor16& vektor16::operator=(vektor16& v)");
    // liší se délka Lhodnoty a Phodnoty?
    if (v.delka != delka)
    {
        delka = v.delka;
        delete[] pole;
        pole = new double[delka];
    }
    // následnì se prvky okopírují
    for (int i = 0; i < delka; i++)
    {
        pole[i] = v.pole[i];
    }

// Nakonec vrátíme aktuální instanci (tedy levý operand);
// vezmìte prosím jako fakt bez bližšího vysvìtlení, že to je nezbytné,
// aby bylo možno pøiøazení zøetìzit, tedy napsat napøíklad
// X = Y = W;
    return *this;
}


auto vypis_prirazovani_vektoru() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    vektor16 w{ 1,2,3,4,5 };
    cout << Tabs::getTabChars() << "vektor16 w{ 1,2,3,4,5 }; délka: " << w.delka << " hodnota: ";
    for (int i{0}; i<w.delka; i++)
        cout << w.pole[i] << " ";
    cout << endl;

    vektor16 x{ 22, 11, 999, 7, 1, 42 };
    cout << Tabs::getTabChars() << "vektor16 x{ 22, 11, 999, 7, 1, 42 }; délka: " << x.delka << " hodnota: ";
    for (int i{0}; i<x.delka; i++)
        cout << x.pole[i] << " ";
    cout << endl;

    x = w;
    cout << Tabs::getTabChars() << "x = w" << endl;
    x.nastav(2, 9);
    cout << Tabs::getTabChars() <<  "x.nastav(2, 9);" << endl;

    cout << Tabs::getTabChars() << "vektor16 w; délka: " << w.delka << " hodnota: ";
    for (int i{0}; i<w.delka; i++)
        cout << w.pole[i] << " ";
    cout << endl;
    cout << Tabs::getTabChars() << "vektor16 x; délka: " << x.delka << " hodnota: ";
    for (int i{0}; i<x.delka; i++)
        cout << x.pole[i] << " ";
    cout << endl;

}



//
// PØÍKLAD 16.14: KOPÍROVÁNÍ VEKTORU
//

void vektor16::nastav(int index, double hodnota)
{
    pole[index] = hodnota;
}

auto vypis_kopirovani_vektoru() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    vektor16 w{ 1,2,3,4,5 };
    cout << Tabs::getTabChars() << "vektor16 w{ 1,2,3,4,5 }; délka: " << w.delka << " hodnota: ";
    for (int i{0}; i<w.delka; i++)
        cout << w.pole[i] << " ";
    cout << endl;

    vektor16 x(w);
    cout << Tabs::getTabChars() << "vektor16 x(w); délka: " << x.delka << " hodnota: ";
    for (int i{0}; i<x.delka; i++)
        cout << x.pole[i] << " ";
    cout << endl;

    x.nastav(2, 9);
    cout << Tabs::getTabChars() << "x.nastav(2, 9); délka: " << x.delka << " hodnota: ";
    for (int i{0}; i<x.delka; i++)
        cout << x.pole[i] << " ";
    cout << endl;

    // znova w
    cout << Tabs::getTabChars() << "vektor16 w{ 1,2,3,4,5 }; délka: " << w.delka << " hodnota: ";
    for (int i{0}; i<w.delka; i++)
        cout << w.pole[i] << " ";
    cout << endl;

}

//
// PØÍKLAD 16.13: POUŽITÍ DESTRUKTORU
//

vektor16::~vektor16()
{
    Tabs::printLine("vektor16::~vektor16()");
    Tabs::decTab();
    delete[] pole;
}


//
// PØÍKLAD 16.12: DELEGOVÁNÍ KONSTRUKTORU - Volání jiného konstruktoru téže tøídy
//

// kopie z pøíkladu 16.09 - nahrazena v této kapitole
// K vytvoøení prázdného vektoru ovšem mùžeme využít konstruktor
// s jedním parametrem, kterému pøedáme délku seznamu inicializátorù:
// vektor16::vektor16(initializer_list<double> il) : vektor16(60)

// a tomu se øíká delegování konstruktoru
vektor16::vektor16(initializer_list<double> il)
    : vektor16( il.size() ) // tato inicializace tzv. deleguje konstruktor explicit vektor16(int n);
{
    Tabs::printLine("vektor16::vektor16(i_l)");
    Tabs::addTab();
    // delka = il.size();
    // pole = new double[delka];
    int i = 0;
    for(double x: il)
    {
        pole[i++]=x;
    }
}

// speciální konstruktor pro použití metody operator-
vektor16::vektor16(const double *arr, int length)
    : delka(length), pole(new double[length])
{
    Tabs::printLine("vektor16::vektor16(*arr,int)");
    Tabs::addTab();
    // inicializujeme v inicializaci kontruktoru
    // delka = il.size();
    // pole = new double[delka];
    for(int i{0}; i<length; i++)
    {
        pole[i]=arr[i];
    }
}

// metoda tøídy
vektor16 vektor16::operator-(vektor16 w)
{
    Tabs::printLine("vektor16 vektor16::operator-(vektor16 w)");

    double vysledek[dim] {0};
    for(int i = 0; i < dim; i++)
    {
        vysledek[i] = this->pole[i] - w.pole[i];
        // cout << vysledek[i] << " ";
    }

    return vektor16(vysledek, dim);
    // return vektor16{vysledek, dim};
}

//
// PØÍKLAD 16.11: POLE KOMPLEXNÍCH ÈÍSEL
//
auto vypis_delegovani_konstruktoru() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    vektor16 a{123};
    cout << Tabs::getTabChars() << "vektor16 a{123}; délka: " << a.delka << " hodnota: ";
    for (int i{0}; i<a.delka; i++)
        cout << a.pole[i] << " ";
    cout << endl;

}

//
// PØÍKLAD 16.11: POLE KOMPLEXNÍCH ÈÍSEL
//
auto vypis_pole_komplexnich_cisel() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;


    // deklarace instancí
    komplex16 a(5), b(3.1, 5.2);
    cout << endl << "komplex16 a; a.re:\t" << a.re << "\ta.im:\t\t" << a.im << endl;
    cout << "komplex16 b(a); b.re:\t" << b.re << "\tb.im:\t" << b.im << endl;

    // deklarace pole
    komplex16 pole[5] {komplex16(3,7), a, a.plus(b), 8};

    cout << endl << "komplex16 pole[5]{komplex16(3,7), a, a.plus(b), 8};" << endl;
    for (int i{0}; i<5; i++)
        cout << " pole[i].im:\t" << pole[i].re << "\tpole[i].im:\t" << pole[i].im << endl;

}

//
// PØÍKLAD 16.10: EXPLICITNÍ VOLÁNÍ KONSTRUKTORU
//

komplex16::komplex16(double _re, double _im)
    : re(_re), im(_im)
{
    Tabs::printLine("komplex16::komplex16(double _re, double _im)");
    Tabs::addTab();
}


komplex16 komplex16::plus(komplex16 a)
{
    Tabs::printLine("komplex16 komplex16::plus(komplex16 a)");
    return komplex16(re + a.re, im + a.im);
}

komplex16::~komplex16()
{
    Tabs::printLine("komplex16::~komplex16()");
    Tabs::decTab();
}

auto vypis_explicitni_volani_konstruktoru() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    komplex16 a;

    // vše je kopie existující instance
    // vše je volání kopírovacího konstruktoru

    komplex16 b(a);
    komplex16 c{a};
    komplex16 d = a;

    cout << endl << "komplex16 a; a.re:\t" << a.re << " a.im:\t" << a.im << endl;
    cout << "komplex16 b(a); b.re:\t" << b.re << " b.im:\t" << b.im << endl;
    cout << "komplex16 c(a); c.re:\t" << c.re << " c.im:\t" << c.im << endl;
    cout << "komplex16 d(a); d.re:\t" << d.re << " d.im:\t" << d.im << endl;

    // vytvoøení dynamické instance
    komplex16 *p_a = new komplex16;
    cout << endl << "komplex16 p_a; p_a->re:\t\t" << p_a->re << " p_a->im:\t" << p_a->im << endl;
    delete p_a;

    komplex16 *p_b = new komplex16(1.5,1.6); // nebo složené závorky
    cout << "komplex16() p_b; p_b->re:\t" << p_b->re << " p_b->im:\t" << p_b->im << endl;
    delete p_b;
}
// nahrazeno pøíkladem 16.12
//
// PØÍKLAD 16.9: INICIALIZACE VEKTORU SEZNAMEM INICIALIZÁTORÙ
//
//vektor16::vektor16(initializer_list<double> il)
//{
//    cout << __func__ << "-il" << " | ";
//    delka = il.size();
//    pole = new double[delka];
//    int i = 0;
//    for(double x: il)
//    {
//        pole[i++]=x;
//    }
//}

//
// Mùj pøíklad pro konstruktor s parametrem char
//

/*
vektor16::vektor16(char znak)
{
    cout << __func__ << "-char" << " | ";
    delka = 1;
    pole = new double[delka]{znak};
}

//
// Mùj pøíklad pro konstruktor s parametrem double
//
vektor16::vektor16(double dbl)
{
    cout << __func__ << "-dbl" << " | ";
    delka = 1;
    pole = new double[delka]{dbl};

}
*/


//
// PØÍKLAD 16.8: ROZDÍL MEZI KOPÍROVACÍM A STÌHOVACÍM KONSTRUKTOREM
//



auto vypis_kopirovaci_a_stehovaci_konstruktor() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    vektor16 a{55};
    cout << Tabs::getTabChars() << "vektor16 a{55}; délka: " << a.delka << " hodnota: ";
    for (int i{0}; i<a.delka; i++)
        cout << a.pole[i] << " ";
    cout << endl;

    vektor16 b(a); // zavolá se kopírovací konstruktor, protože l-hodnota
    cout << Tabs::getTabChars() << "vektor16 b(a); délka: " << b.delka << " hodnota: ";
    for (int i{0}; i<b.delka; i++)
        cout << b.pole[i] << " ";
    cout << endl;




// toto jerozbité /// spravíme èasem
    vektor16 c( a + b ); // zavolá se kopírovací konstruktor, protože l-hodnota
    cout << Tabs::getTabChars() << "vektor16 c(a+b); délka: " << c.delka << " hodnota: ";
    for (int i{0}; i<c.delka; i++)
        cout << c.pole[i] << " ";
    cout << endl;

    // nìco je zde jinak - dle knihy to se má volat MOVE construktor
    // ale volá se COPY, proè?
    //vektor16 c(a+b); // zavolá se stìhovací konstruktor, nebo zde jsme kinicializaci použili výraz, který nepøedstavuje l-hodnotu
    //vektor16 d(c-b);

}

//
// PØÍKLAD 16.7: EXPLICITNÍ KONSTRUKTOR
//
//Konstruktor s jedním parametrem typu int
// zkonstruuje vektor o zadané délce a naplní ho nulami
vektor16::vektor16(int n)
    : delka(n), pole( new double[n] {})
{
    Tabs::printLine("vektor16::vektor16(int n)");
    Tabs::addTab();
}

auto vypis_inicializace_vektoru_seznamem_inicializatoru_nebo_i_jinak() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    vektor16 w{1,2,3,4,5};
    cout << Tabs::getTabChars() << "vektor16 w{1,2,3,4,5}; délka: " << w.delka << " hodnota: ";
    for (int i{0}; i<w.delka; i++)
        cout << w.pole[i] << " ";
    cout << endl;

    vektor16 z{6};
    cout << Tabs::getTabChars() << "vektor16 z{6}; délka: " << z.delka << " hodnota: ";
    for (int i{0}; i<z.delka; i++)
        cout << z.pole[i] << " ";
    cout << endl;

    vektor16 x{};
    cout << Tabs::getTabChars() << "vektor16 x{}; délka: " << x.delka << " hodnota: ";
    for (int i{0}; i<x.delka; i++)
        cout << x.pole[i] << " ";
    cout << endl;

    vektor16 y(6);
    cout << Tabs::getTabChars() <<  "vektor16 y(6); délka: " << y.delka << " hodnota: ";
    for (int i{0}; i<y.delka; i++)
        cout << y.pole[i] << " ";
    cout << endl;

    vektor16 a('A'); // vráti velikost pole o 65 prvcích
    cout << Tabs::getTabChars() << "vektor16 a('A'); délka: " << a.delka << " hodnota: ";
    for (int i{0}; i<a.delka; i++)
        cout << a.pole[i] << " ";
    cout << endl;

    // inicializuje se seznam totiž
    vektor16 b(1.1);
    cout << Tabs::getTabChars() << "vektor16 b(1.1); délka: " << b.delka << " hodnota: ";
    for (int i{0}; i<b.delka; i++) // double hodnota je nepøesná, takže mùže zlobit v cyklech
        cout << b.pole[i] << " ";
    cout << endl;

    // inicializuje se seznam totiž
    vektor16 c((double)5.3);
    cout << Tabs::getTabChars() << "vektor16 c(5.3); délka: " << c.delka << " hodnota: ";
    for (int i{0}; i<c.delka; i++)
        cout << c.pole[i] << " ";
    cout << endl;

    vektor16 r{1,2,32};
    cout << Tabs::getTabChars() << "vektor16 r{0}; délka: " << r.delka << " hodnota: ";// << ((r.pole) ? r.pole[0] : 99);
    for (int i{0}; i<r.delka; i++)
        cout << r.pole[i] << " ";
    cout << endl;

    // tento výraz zde nemùžeme použít
    // ****** r = 11; // zamezíme pomoci explicit

    // v pøípadì, že bychom opravdu chtìli, tak použijeme takto
    // ***** v = (vektor)11;


    // Pozor, to je deklarace funkce!
    // vektor16 THIS_IS_NOT_DECLARATION_OF_OBJECT_INSTANCE_BUT_DECLARATION_OF_FUNCTION_RETURNING_vektor16();
    // neznamená deklaraci instance, ale deklaraci funkce vracející T. bACHA!


}

auto vypis_explicitni_konstruktor() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    // deklarace instance
    vektor16 v(9);
    cout << Tabs::getTabChars() << "délka: " << v.delka << " hodnota: ";
    for (int i{0}; i<v.delka; i++)
        cout << v.pole[i] << " ";
    cout << endl;

    // nyní pøiøazení - všechno špatnì ale
    // v = 11; // !!!
    // použije pøekladaè konstruktor ke konverzi èísla 11 na vektor o 11 prvcích
    // a ten pøiøadí instanci v.
    // To je ovšem nìco, co jsme témìø jistì nechtìli.
    // Proto deklarujeme tento konstruktor jako explicitní:
    // Navíc uvedené pøiøazení zpùsobí chybu pøi práci s dynamicky alokovanou pamìtí,
    // jež povede s velkou pravdìpodobností ke zhroucení programu;
    // budeme se tím zabývat v oddílu
    // cout << "v = 11: " <<  v.delka << " pole: " << endl;
    // chyba je správnì a explixitní konstruktor nedovolí pøiøazení hodnoty rovnítkem
    // C:\Projects\_CppMaster\KnihovnaProgramatoraCpp\16_objektove_typy.cpp|29|error: no match for 'operator=' (operand types are 'vektor16' and 'int')|

    // Kdybychom zde konverzi opravdu požadovali, což ????? - museli bychom napsat napøíklad
    // v = (vektor16)11;
    // cout << "v = (vektor16)11: " <<  v.delka << " pole: " << endl;
}

//
// PØÍKLAD 16.6: KONVERZNÍ KONSTRUKTOR
//
// použití konstruktoru k explicitnímu pøetypování

double fkomplex(komplex x)
{
    cout << "x.re: " << x.re << " x.im: " << x.im << endl << "souèet: ";
    return x.re + x.im;
}

auto vypis_konverzni_konstruktor() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    cout << "fkomplex(11):" << endl << fkomplex(1.2) << endl << endl;
    cout << "fkomplex({0}):" << endl << fkomplex({1.2}) << endl << endl;
    cout << "fkomplex({0,5}):" << endl << fkomplex({1.2,88.8}) << endl << endl;
    cout << endl;
}
//
// PØÍKLAD 16.5: INICIALIZAÈNÍ ÈÁST KONSTRUKTORU
//
// konstruktor implementace - musí být vždy v CPP souboru
// jedná se o inicializaèní èást konstruktoru
// syntaxe to dovoluje, ale mohli by nastat pozdìjší problémy

// konstruktor tøídy bod16

/*
bod16::bod16(double _x, double _y)
    : x(_x), y(_y)
{ }
*/

// výše zmínìný konstruktor s inicializací se doporuèuje nahradit
// níže vypsanými metodami a konstruktorem s jejich voláním
void bod16::set_x(double _x)
{
    x = _x;
}

void bod16::set_y(double _y)
{
    y = _y;
}

bod16::bod16(double _x, double _y)
{
    set_x(_x);
    set_y(_y);
}

usecka::usecka(double x1, double y1, double x2, double y2)
    : pocatek{x1, y1}, konec{x2,y2}
{
    // tìlo zde není dùležité
}

//
// 16.1.5 Datové typy deklarované ve tøídì (vnoøené typy)
// PØÍKLAD 16.4: DATOVÝ TYP DEKLAROVANÝ UVNITØ TØÍDY
// šablona je uvedena v hlavièkovém souboru <vector>
// template< class T, class Allocator = std::allocator<T> > class vector;
//

// Vnoøené datové typy se èasto používají ušablonových tøíd
// ke zveøejnìní typù parametrù nebo typù od nich odvozených.

using texty = vector<string>;
texty vstup, zpracovani;

// deklarace nové promìnné typu odvozeného z value_type odvozeného z tøídy vector
texty::value_type povidani;
texty::value_type::value_type znak;

using cisla = vector<int>;
cisla mojeCisla;

auto vypis_vektoru_pres_aliasy() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    // povidani je typ, který je odvozený od tøídy vector<int>
    povidani = "já jsem nová promìnná typu odvozená z value_type,která je odvozená z tøídy standardní knihovny vector";
    znak = 'a';

    // vstup je již instance na vector
    vstup.push_back("první");
    vstup.push_back("druhý");
    vstup.push_back("tøetí");

    for (const auto& prvek : vstup)
    {
        cout << prvek << " ";
    }
    cout << endl;

    for (int i{0}; i < 16; i++)
        mojeCisla.push_back(i);

    for (const int &prvek : mojeCisla)
    {
        cout << prvek << " ";
    }
    cout << endl;
    cout << "povidani: " << povidani << endl;
    cout << "znak: " << znak << endl;
}

//
// PØÍKLAD 16.1: OPERÁTOR JAKO SPØÁTELENÁ FUNKCE
//
auto vypis_sprateleny_operator_plus() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    vektor16 a{5,6,3};
    cout << Tabs::getTabChars() << "vektor16 a{5,6,3};: ";
    for (int i{0}; i<dim; i++)
        cout << a.pole[i] << " ";
    cout << endl;

    vektor16 b{7,8,1};
    cout << Tabs::getTabChars() << "vektor16 b{7,8,1}; ";
    for (int i{0}; i<dim; i++)
        cout << b.pole[i] << " ";
    cout << endl;

    vektor16 c = a + b;
    cout << Tabs::getTabChars() << "vektor16 c = a + b; ";
    for (int i{0}; i<dim; i++)
        cout << c.pole[i] << " ";
    cout << endl;

    vektor16 d = a - b;
    cout << Tabs::getTabChars() << "vektor16 d = a - b; ";
    for (int i{0}; i<dim; i++)
        cout << d.pole[i] << " ";
    cout << endl;




}


// spøátelená funkce
vektor16 operator+(vektor16 u, vektor16 w)
{
    Tabs::printLine("vektor16 operator+(vektor16 u, vektor16 w)");

    double vysledek[dim] {0};
    for(int i = 0; i < dim; i++)
    {
        vysledek[i] = u.pole[i] + w.pole[i];
        // cout << vysledek[i] << " ";
    }

    // return vektor16(vysledek, dim);
    return vektor16{vysledek, dim};
}
