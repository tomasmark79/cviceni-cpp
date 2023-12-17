#include <iostream>
#include "zajimavosti.h"
#include "17_dedeni.h"


//
// P��KLAD 17.1: GRAFICK� OBJEKTY � SPOLE�N� P�EDEK, PRVN� POKUS
//

graficky_objekt::graficky_objekt(int _barva)
{
    set_barva(_barva);
    Tabs::printLine("go(int _barva)");
    Tabs::addTab();
}
graficky_objekt::~graficky_objekt()
{
    Tabs::printLine("~go()");
    smaz(); // p�i vol�n� zdestruktoru se pozdn� vazba neuplat�uje
    Tabs::decTab();
}

// P��KLAD 17.3: KONSTRUKTOR A DESTRUKTOR T��DY bod_potomek
bod_potomek::bod_potomek(int _x, int _y, int _barva)
    :graficky_objekt(_barva) // Vol�n� konstruktor� p�edk� zapisujeme v inicializa�n� ��sti konstruktoru potomka.
{
    set_barva(_barva); // vol� metodu p�edka
    set_x(_x);
    set_y(_y);

    Tabs::printLine("bod_potomek(int _x, int _y, int _barva)");
    Tabs::addTab();
}
bod_potomek::~bod_potomek()
{
    Tabs::printLine("~bod_potomek()");
    smaz(); // opakov�n� vol�n� je zde z�m�r
    Tabs::decTab();
}

void graficky_objekt::set_barva(int _barva)
{
    this->barva = _barva;
}
int graficky_objekt::get_barva()
{
    return this->barva;
}

bool graficky_objekt::je_nakreslen()
{
    return nakreslen;
}

void graficky_objekt::nakresli()
{
    if (!nakreslen)
    {
        nakreslen = true;
        proved_kresleni();
    }
}
void graficky_objekt::smaz()
{
    if (nakreslen)
    {
        nakreslen = false;
        proved_mazani();
    }
}

void graficky_objekt::proved_kresleni()
{
    cout << Tabs::getTabChars() << "go::kresl�m [" << this->barva << "]" << endl;
}
void graficky_objekt::proved_mazani()
{
    cout << Tabs::getTabChars() << "go::smaz�n� objektu" << endl;
}
void bod_potomek::proved_kresleni()
{
    cout << Tabs::getTabChars() << "bod_potomek::kresl�m(): ( " << x << ", " << y << " ) ";
    graficky_objekt::proved_kresleni(); // nakresli i p�edka
}
void bod_potomek::proved_mazani()
{
    cout << Tabs::getTabChars() << "bod_potomek::smaz�n� objektu" << endl;
    proved_kresleni();
}
void bod_potomek::set_x(int _x)
{
    x = _x;
}
void bod_potomek::set_y(int _y)
{
    y = _y;
}

//
// P��KLAD 17.12: LEP�� N�VRH
//
auto vypis_lepsi_navrh() -> void
{
    graficky_objekt *pgo = new bod_potomek(123, 456, 789);
    pgo->nakresli(); // 1
    pgo->smaz();
    delete pgo;
}

















auto vypis_vytvoreni_grafickeho_objektu() -> void
{
    graficky_objekt g(8);
    g.nakresli();

    bod_potomek b{1, 9, 22};
    // b.nakresli();
}

//
// P��KLAD 17.5: O��ZNUT� OBJEKTU
//

auto vypis_oriznuti_objektu() -> void
{
    graficky_objekt g(241);
    bod_potomek b(201, 335, 123);

    // o�ez instance - slicing
    g = b; // p�enese se pouze zd�d�n� podobjekt, �ili prom�nn� barva
    g.nakresli();
}

//
// P��KLAD 17.6: P�I�AZOV�N� UKAZATEL�
//

auto vypis_prirazovani_ukazatelu() -> void
{


    graficky_objekt g(241);
    bod_potomek b(201, 335, 123);
    graficky_objekt *pgo = &g;
    bod_potomek *pb_potomek = &b;

    // nebo i dynamicky, ale ztrat� se ukazatel na pgo, tak�e nep�jde smazat
    // graficky_objekt *pgo =  new graficky_objekt(241);
    // bod_potomek *pb_potomek = new bod_potomek(201, 335, 123);

    // prom�nn� p�edstavuj�c� ukazatel na p�edka
    // lze p�i�adit hodnotu ukazatele na potomka
    pgo = pb_potomek;

    // p�i�azen� potomka ukazatel na p�edka
    pb_potomek = (bod_potomek*)pgo;

    pb_potomek->nakresli(); // (201, 335) [123]

    // delete pgo; // tento je zapomoenut
    // delete pb_potomek;

}

//
// P��KLAD 17.7: JE TO BOD, ALE KRESL� SE OBECN� GRAFICK� OBJEKT
//
//
// P��KLAD 17.8: UPRAVUJEME T�IDY GRAFICK�CH OBJEKT�
//
// p�id�no virtual do deklarace t��dy
// virtual ~graficky_objekt(); // P��KLAD 17.8: virtual
// virtual void nakresli(); // P��KLAD 17.8: virtual
// virtual void nakresli(); // P��KLAD 17.8: virtual

// p�i p�i�azov�n� ukazatel� se informace z instanc� neztr�cej�
auto vypis_upravujeme_tridy_grafickych_objektu() -> void
{
    // pot�ebujeme, aby program za b�hu zjistil, jak�ho typu je instance,
    // na kterou tento ukazatel ukazuje a podle toho zavolal
    // odpov�daj�c� metodu
    // jin�mi slovy, pot�ebujeme, aby pou�il pozdn� vazbu
    //              tzv. late binding
    // Implementace pozdn� vazby: virtu�ln� metody
    // Metodu, pro kterou m� p�eklada� pou��t pozdn� vazbu, deklarujeme jako virtu�ln�.

    graficky_objekt g(241);
    bod_potomek b(201, 335, 123);

    // M�me-li ukazatel
    graficky_objekt *pg;

    // p�i�ad�me-li mu adresu instance t��dy bod
    pg = &b;

    // a zkus�me-li tento bod nakreslit p��kazem
    pg->nakresli();

    // budeme zklam�ni, nebo� program nakresl� obecn� grafick� objekt
    // tedy vyp�e [123]


    /*
        usecka_potomek u(100, 200, 300, 400);
        u.set_tloustka( 16 );
        cout << Tabs::getTabChars() << u.get_tloustka();
        u.nakresli();
    */
}


//
// P��KLAD 17.9: VIRTU�LN� DESTRUKTOR
//
auto vypis_virtualni_destruktor() -> void
{
    // grafick� objekt inicializujeme nov�m potomkem bod
    graficky_objekt *pgo = new bod_potomek(201, 335, 123);
    delete pgo;
    // bez virtual vol� ~graficky_objekt();
    // s virtual vol� virtual ~bod_potomek() override;
}

//
// P��KLAD 17.10: MA�EME GRAFICK� OBJEKT
//
auto vypis_mazeme_graficky_objekt() -> void
{
    graficky_objekt *pgo = new bod_potomek(201, 335, 123);
    pgo->nakresli();
    pgo->smaz();
    // V t�le metody smaz() vol�me virtu�ln� metodu nakresli() bez kvalifikace,
    // tak�e se uplatn� pozdn� vazba a program zavol� metodu odpov�daj�c�
    // skute�n�mu typu instance.
}


//
// P��KLAD 17.11: MA�EME GRAFICK� OBJEKT V DESTRUKTORU
//
// vol�n� virtu�ln�ch metod v konstruktoru a v destruktoru se vyh�b�me
auto vypis_mazeme_graficky_objekt_v_destruktoru() -> void
{
    graficky_objekt *pgo = new bod_potomek(201, 335, 123);
    delete pgo;
}
















//usecka_potomek::usecka_potomek(int _x, int _y, int _barva, int _tloustka)
//    :graficky_objekt(_barva) // Vol�n� konstruktor� p�edk� zapisujeme v inicializa�n� ��sti konstruktoru potomka.
//{
//    set_barva(_barva); // vol� metodu p�edka
//    set_tloustka(_tloustka);
//
//    set_x(_x);
//    set_y(_y);
//
//    Tabs::printLine("usecka_potomek(int _x, int _y, int _barva, int _tloustka);");
//    Tabs::addTab();
//}
//
//usecka_potomek::~usecka_potomek()
//{
//
//    Tabs::printLine("~usecka_potomek()");
//
//
//    // smaz(); // opakov�n� vol�n� je zde z�m�r
//
//
//    Tabs::decTab();
//}
//
//void usecka_potomek::set_tloustka(int _tloustka)
//{
//    tloustka = _tloustka;
//}
//
//int usecka_potomek::get_tloustka()
//{
//    return tloustka;
//}
//
//auto usecka_potomek::nakresli() -> void
//{
//    cout << Tabs::getTabChars() << "usecka_potomek::nakresli(): ( x: " << x << ", y: " << y << ", tloustka: " << tloustka << " )" << endl;
//    graficky_objekt::nakresli();
//    // cout << Tabs::getTabChars() << "[" << get_barva() << "]" << endl;
//}
//
//void usecka_potomek::set_x(int _x)
//{
//    x = _x;
//}
//void usecka_potomek::set_y(int _y)
//{
//    y = _y;
//}

// P��KLAD 17.4: OSTATN� METODY T��DY bod_potomek
