#include <iostream>
#include <vector>
#include <string>
#include "16_objektove_typy.h"
#include "zajimavosti.h"
#include "04_pokrocilejsi_konstrukce_a_techniky.h"

using namespace std;
// const int dim = 3;

//
// P��KLAD 16.18: KONSTANTN� N�PIS
// P�ipome�me si je�t� jednou t��du Napis,
// kterou jsme poprv� deklarovali vodd�lu 4.1.

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
// P��KLAD 16.17: IMAGIN�RN� JEDNOTKA
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
// P��KLAD 16.16: VEKTOR JAKO SLO�KA SLO�IT�J�� T��DY
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
// P��KLAD 16.15: P�I�AZOV�N� VEKTOR�
//

vektor16& vektor16::operator=(vektor16& v)
{
    Tabs::printLine("vektor16& vektor16::operator=(vektor16& v)");
    // li�� se d�lka Lhodnoty a Phodnoty?
    if (v.delka != delka)
    {
        delka = v.delka;
        delete[] pole;
        pole = new double[delka];
    }
    // n�sledn� se prvky okop�ruj�
    for (int i = 0; i < delka; i++)
    {
        pole[i] = v.pole[i];
    }

// Nakonec vr�t�me aktu�ln� instanci (tedy lev� operand);
// vezm�te pros�m jako fakt bez bli���ho vysv�tlen�, �e to je nezbytn�,
// aby bylo mo�no p�i�azen� z�et�zit, tedy napsat nap��klad
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
    cout << Tabs::getTabChars() << "vektor16 w{ 1,2,3,4,5 }; d�lka: " << w.delka << " hodnota: ";
    for (int i{0}; i<w.delka; i++)
        cout << w.pole[i] << " ";
    cout << endl;

    vektor16 x{ 22, 11, 999, 7, 1, 42 };
    cout << Tabs::getTabChars() << "vektor16 x{ 22, 11, 999, 7, 1, 42 }; d�lka: " << x.delka << " hodnota: ";
    for (int i{0}; i<x.delka; i++)
        cout << x.pole[i] << " ";
    cout << endl;

    x = w;
    cout << Tabs::getTabChars() << "x = w" << endl;
    x.nastav(2, 9);
    cout << Tabs::getTabChars() <<  "x.nastav(2, 9);" << endl;

    cout << Tabs::getTabChars() << "vektor16 w; d�lka: " << w.delka << " hodnota: ";
    for (int i{0}; i<w.delka; i++)
        cout << w.pole[i] << " ";
    cout << endl;
    cout << Tabs::getTabChars() << "vektor16 x; d�lka: " << x.delka << " hodnota: ";
    for (int i{0}; i<x.delka; i++)
        cout << x.pole[i] << " ";
    cout << endl;

}



//
// P��KLAD 16.14: KOP�ROV�N� VEKTORU
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
    cout << Tabs::getTabChars() << "vektor16 w{ 1,2,3,4,5 }; d�lka: " << w.delka << " hodnota: ";
    for (int i{0}; i<w.delka; i++)
        cout << w.pole[i] << " ";
    cout << endl;

    vektor16 x(w);
    cout << Tabs::getTabChars() << "vektor16 x(w); d�lka: " << x.delka << " hodnota: ";
    for (int i{0}; i<x.delka; i++)
        cout << x.pole[i] << " ";
    cout << endl;

    x.nastav(2, 9);
    cout << Tabs::getTabChars() << "x.nastav(2, 9); d�lka: " << x.delka << " hodnota: ";
    for (int i{0}; i<x.delka; i++)
        cout << x.pole[i] << " ";
    cout << endl;

    // znova w
    cout << Tabs::getTabChars() << "vektor16 w{ 1,2,3,4,5 }; d�lka: " << w.delka << " hodnota: ";
    for (int i{0}; i<w.delka; i++)
        cout << w.pole[i] << " ";
    cout << endl;

}

//
// P��KLAD 16.13: POU�IT� DESTRUKTORU
//

vektor16::~vektor16()
{
    Tabs::printLine("vektor16::~vektor16()");
    Tabs::decTab();
    delete[] pole;
}


//
// P��KLAD 16.12: DELEGOV�N� KONSTRUKTORU - Vol�n� jin�ho konstruktoru t�e t��dy
//

// kopie z p��kladu 16.09 - nahrazena v t�to kapitole
// K vytvo�en� pr�zdn�ho vektoru ov�em m��eme vyu��t konstruktor
// s jedn�m parametrem, kter�mu p�ed�me d�lku seznamu inicializ�tor�:
// vektor16::vektor16(initializer_list<double> il) : vektor16(60)

// a tomu se ��k� delegov�n� konstruktoru
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

// speci�ln� konstruktor pro pou�it� metody operator-
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

// metoda t��dy
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
// P��KLAD 16.11: POLE KOMPLEXN�CH ��SEL
//
auto vypis_delegovani_konstruktoru() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    vektor16 a{123};
    cout << Tabs::getTabChars() << "vektor16 a{123}; d�lka: " << a.delka << " hodnota: ";
    for (int i{0}; i<a.delka; i++)
        cout << a.pole[i] << " ";
    cout << endl;

}

//
// P��KLAD 16.11: POLE KOMPLEXN�CH ��SEL
//
auto vypis_pole_komplexnich_cisel() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;


    // deklarace instanc�
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
// P��KLAD 16.10: EXPLICITN� VOL�N� KONSTRUKTORU
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

    // v�e je kopie existuj�c� instance
    // v�e je vol�n� kop�rovac�ho konstruktoru

    komplex16 b(a);
    komplex16 c{a};
    komplex16 d = a;

    cout << endl << "komplex16 a; a.re:\t" << a.re << " a.im:\t" << a.im << endl;
    cout << "komplex16 b(a); b.re:\t" << b.re << " b.im:\t" << b.im << endl;
    cout << "komplex16 c(a); c.re:\t" << c.re << " c.im:\t" << c.im << endl;
    cout << "komplex16 d(a); d.re:\t" << d.re << " d.im:\t" << d.im << endl;

    // vytvo�en� dynamick� instance
    komplex16 *p_a = new komplex16;
    cout << endl << "komplex16 p_a; p_a->re:\t\t" << p_a->re << " p_a->im:\t" << p_a->im << endl;
    delete p_a;

    komplex16 *p_b = new komplex16(1.5,1.6); // nebo slo�en� z�vorky
    cout << "komplex16() p_b; p_b->re:\t" << p_b->re << " p_b->im:\t" << p_b->im << endl;
    delete p_b;
}
// nahrazeno p��kladem 16.12
//
// P��KLAD 16.9: INICIALIZACE VEKTORU SEZNAMEM INICIALIZ�TOR�
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
// M�j p��klad pro konstruktor s parametrem char
//

/*
vektor16::vektor16(char znak)
{
    cout << __func__ << "-char" << " | ";
    delka = 1;
    pole = new double[delka]{znak};
}

//
// M�j p��klad pro konstruktor s parametrem double
//
vektor16::vektor16(double dbl)
{
    cout << __func__ << "-dbl" << " | ";
    delka = 1;
    pole = new double[delka]{dbl};

}
*/


//
// P��KLAD 16.8: ROZD�L MEZI KOP�ROVAC�M A ST�HOVAC�M KONSTRUKTOREM
//



auto vypis_kopirovaci_a_stehovaci_konstruktor() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    vektor16 a{55};
    cout << Tabs::getTabChars() << "vektor16 a{55}; d�lka: " << a.delka << " hodnota: ";
    for (int i{0}; i<a.delka; i++)
        cout << a.pole[i] << " ";
    cout << endl;

    vektor16 b(a); // zavol� se kop�rovac� konstruktor, proto�e l-hodnota
    cout << Tabs::getTabChars() << "vektor16 b(a); d�lka: " << b.delka << " hodnota: ";
    for (int i{0}; i<b.delka; i++)
        cout << b.pole[i] << " ";
    cout << endl;




// toto jerozbit� /// sprav�me �asem
    vektor16 c( a + b ); // zavol� se kop�rovac� konstruktor, proto�e l-hodnota
    cout << Tabs::getTabChars() << "vektor16 c(a+b); d�lka: " << c.delka << " hodnota: ";
    for (int i{0}; i<c.delka; i++)
        cout << c.pole[i] << " ";
    cout << endl;

    // n�co je zde jinak - dle knihy to se m� volat MOVE construktor
    // ale vol� se COPY, pro�?
    //vektor16 c(a+b); // zavol� se st�hovac� konstruktor, nebo� zde jsme kinicializaci pou�ili v�raz, kter� nep�edstavuje l-hodnotu
    //vektor16 d(c-b);

}

//
// P��KLAD 16.7: EXPLICITN� KONSTRUKTOR
//
//Konstruktor s jedn�m parametrem typu int
// zkonstruuje vektor o zadan� d�lce a napln� ho nulami
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
    cout << Tabs::getTabChars() << "vektor16 w{1,2,3,4,5}; d�lka: " << w.delka << " hodnota: ";
    for (int i{0}; i<w.delka; i++)
        cout << w.pole[i] << " ";
    cout << endl;

    vektor16 z{6};
    cout << Tabs::getTabChars() << "vektor16 z{6}; d�lka: " << z.delka << " hodnota: ";
    for (int i{0}; i<z.delka; i++)
        cout << z.pole[i] << " ";
    cout << endl;

    vektor16 x{};
    cout << Tabs::getTabChars() << "vektor16 x{}; d�lka: " << x.delka << " hodnota: ";
    for (int i{0}; i<x.delka; i++)
        cout << x.pole[i] << " ";
    cout << endl;

    vektor16 y(6);
    cout << Tabs::getTabChars() <<  "vektor16 y(6); d�lka: " << y.delka << " hodnota: ";
    for (int i{0}; i<y.delka; i++)
        cout << y.pole[i] << " ";
    cout << endl;

    vektor16 a('A'); // vr�ti velikost pole o 65 prvc�ch
    cout << Tabs::getTabChars() << "vektor16 a('A'); d�lka: " << a.delka << " hodnota: ";
    for (int i{0}; i<a.delka; i++)
        cout << a.pole[i] << " ";
    cout << endl;

    // inicializuje se seznam toti�
    vektor16 b(1.1);
    cout << Tabs::getTabChars() << "vektor16 b(1.1); d�lka: " << b.delka << " hodnota: ";
    for (int i{0}; i<b.delka; i++) // double hodnota je nep�esn�, tak�e m��e zlobit v cyklech
        cout << b.pole[i] << " ";
    cout << endl;

    // inicializuje se seznam toti�
    vektor16 c((double)5.3);
    cout << Tabs::getTabChars() << "vektor16 c(5.3); d�lka: " << c.delka << " hodnota: ";
    for (int i{0}; i<c.delka; i++)
        cout << c.pole[i] << " ";
    cout << endl;

    vektor16 r{1,2,32};
    cout << Tabs::getTabChars() << "vektor16 r{0}; d�lka: " << r.delka << " hodnota: ";// << ((r.pole) ? r.pole[0] : 99);
    for (int i{0}; i<r.delka; i++)
        cout << r.pole[i] << " ";
    cout << endl;

    // tento v�raz zde nem��eme pou��t
    // ****** r = 11; // zamez�me pomoci explicit

    // v p��pad�, �e bychom opravdu cht�li, tak pou�ijeme takto
    // ***** v = (vektor)11;


    // Pozor, to je deklarace funkce!
    // vektor16 THIS_IS_NOT_DECLARATION_OF_OBJECT_INSTANCE_BUT_DECLARATION_OF_FUNCTION_RETURNING_vektor16();
    // neznamen� deklaraci instance, ale deklaraci funkce vracej�c� T. bACHA!


}

auto vypis_explicitni_konstruktor() -> void
{
    Tabs::reset();
    cout << endl;
    Tabs::printLine(__func__);
    cout << endl;

    // deklarace instance
    vektor16 v(9);
    cout << Tabs::getTabChars() << "d�lka: " << v.delka << " hodnota: ";
    for (int i{0}; i<v.delka; i++)
        cout << v.pole[i] << " ";
    cout << endl;

    // nyn� p�i�azen� - v�echno �patn� ale
    // v = 11; // !!!
    // pou�ije p�eklada� konstruktor ke konverzi ��sla 11 na vektor o 11 prvc�ch
    // a ten p�i�ad� instanci v.
    // To je ov�em n�co, co jsme t�m�� jist� necht�li.
    // Proto deklarujeme tento konstruktor jako explicitn�:
    // Nav�c uveden� p�i�azen� zp�sob� chybu p�i pr�ci s dynamicky alokovanou pam�t�,
    // je� povede s velkou pravd�podobnost� ke zhroucen� programu;
    // budeme se t�m zab�vat v odd�lu
    // cout << "v = 11: " <<  v.delka << " pole: " << endl;
    // chyba je spr�vn� a explixitn� konstruktor nedovol� p�i�azen� hodnoty rovn�tkem
    // C:\Projects\_CppMaster\KnihovnaProgramatoraCpp\16_objektove_typy.cpp|29|error: no match for 'operator=' (operand types are 'vektor16' and 'int')|

    // Kdybychom zde konverzi opravdu po�adovali, co� ????? - museli bychom napsat nap��klad
    // v = (vektor16)11;
    // cout << "v = (vektor16)11: " <<  v.delka << " pole: " << endl;
}

//
// P��KLAD 16.6: KONVERZN� KONSTRUKTOR
//
// pou�it� konstruktoru k explicitn�mu p�etypov�n�

double fkomplex(komplex x)
{
    cout << "x.re: " << x.re << " x.im: " << x.im << endl << "sou�et: ";
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
// P��KLAD 16.5: INICIALIZA�N� ��ST KONSTRUKTORU
//
// konstruktor implementace - mus� b�t v�dy v CPP souboru
// jedn� se o inicializa�n� ��st konstruktoru
// syntaxe to dovoluje, ale mohli by nastat pozd�j�� probl�my

// konstruktor t��dy bod16

/*
bod16::bod16(double _x, double _y)
    : x(_x), y(_y)
{ }
*/

// v��e zm�n�n� konstruktor s inicializac� se doporu�uje nahradit
// n�e vypsan�mi metodami a konstruktorem s jejich vol�n�m
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
    // t�lo zde nen� d�le�it�
}

//
// 16.1.5 Datov� typy deklarovan� ve t��d� (vno�en� typy)
// P��KLAD 16.4: DATOV� TYP DEKLAROVAN� UVNIT� T��DY
// �ablona je uvedena v hlavi�kov�m souboru <vector>
// template< class T, class Allocator = std::allocator<T> > class vector;
//

// Vno�en� datov� typy se �asto pou��vaj� u�ablonov�ch t��d
// ke zve�ejn�n� typ� parametr� nebo typ� od nich odvozen�ch.

using texty = vector<string>;
texty vstup, zpracovani;

// deklarace nov� prom�nn� typu odvozen�ho z value_type odvozen�ho z t��dy vector
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

    // povidani je typ, kter� je odvozen� od t��dy vector<int>
    povidani = "j� jsem nov� prom�nn� typu odvozen� z value_type,kter� je odvozen� z t��dy standardn� knihovny vector";
    znak = 'a';

    // vstup je ji� instance na vector
    vstup.push_back("prvn�");
    vstup.push_back("druh�");
    vstup.push_back("t�et�");

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
// P��KLAD 16.1: OPER�TOR JAKO SP��TELEN� FUNKCE
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


// sp��telen� funkce
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
