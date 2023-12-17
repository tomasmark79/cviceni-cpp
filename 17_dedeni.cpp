#include <iostream>
#include "zajimavosti.h"
#include "17_dedeni.h"


//
// PØÍKLAD 17.1: GRAFICKÉ OBJEKTY – SPOLEÈNİ PØEDEK, PRVNÍ POKUS
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
    smaz(); // pøi volání zdestruktoru se pozdní vazba neuplatòuje
    Tabs::decTab();
}

// PØÍKLAD 17.3: KONSTRUKTOR A DESTRUKTOR TØÍDY bod_potomek
bod_potomek::bod_potomek(int _x, int _y, int _barva)
    :graficky_objekt(_barva) // Volání konstruktorù pøedkù zapisujeme v inicializaèní èásti konstruktoru potomka.
{
    set_barva(_barva); // volá metodu pøedka
    set_x(_x);
    set_y(_y);

    Tabs::printLine("bod_potomek(int _x, int _y, int _barva)");
    Tabs::addTab();
}
bod_potomek::~bod_potomek()
{
    Tabs::printLine("~bod_potomek()");
    smaz(); // opakování volání je zde zámìr
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
    cout << Tabs::getTabChars() << "go::kreslím [" << this->barva << "]" << endl;
}
void graficky_objekt::proved_mazani()
{
    cout << Tabs::getTabChars() << "go::smazání objektu" << endl;
}
void bod_potomek::proved_kresleni()
{
    cout << Tabs::getTabChars() << "bod_potomek::kreslím(): ( " << x << ", " << y << " ) ";
    graficky_objekt::proved_kresleni(); // nakresli i pøedka
}
void bod_potomek::proved_mazani()
{
    cout << Tabs::getTabChars() << "bod_potomek::smazání objektu" << endl;
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
// PØÍKLAD 17.12: LEPŠÍ NÁVRH
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
// PØÍKLAD 17.5: OØÍZNUTÍ OBJEKTU
//

auto vypis_oriznuti_objektu() -> void
{
    graficky_objekt g(241);
    bod_potomek b(201, 335, 123);

    // oøez instance - slicing
    g = b; // pøenese se pouze zdìdìnı podobjekt, èili promìnná barva
    g.nakresli();
}

//
// PØÍKLAD 17.6: PØIØAZOVÁNÍ UKAZATELÙ
//

auto vypis_prirazovani_ukazatelu() -> void
{


    graficky_objekt g(241);
    bod_potomek b(201, 335, 123);
    graficky_objekt *pgo = &g;
    bod_potomek *pb_potomek = &b;

    // nebo i dynamicky, ale ztratí se ukazatel na pgo, take nepùjde smazat
    // graficky_objekt *pgo =  new graficky_objekt(241);
    // bod_potomek *pb_potomek = new bod_potomek(201, 335, 123);

    // promìnné pøedstavující ukazatel na pøedka
    // lze pøiøadit hodnotu ukazatele na potomka
    pgo = pb_potomek;

    // pøiøazení potomka ukazatel na pøedka
    pb_potomek = (bod_potomek*)pgo;

    pb_potomek->nakresli(); // (201, 335) [123]

    // delete pgo; // tento je zapomoenut
    // delete pb_potomek;

}

//
// PØÍKLAD 17.7: JE TO BOD, ALE KRESLÍ SE OBECNİ GRAFICKİ OBJEKT
//
//
// PØÍKLAD 17.8: UPRAVUJEME TØIDY GRAFICKİCH OBJEKTÙ
//
// pøidáno virtual do deklarace tøídy
// virtual ~graficky_objekt(); // PØÍKLAD 17.8: virtual
// virtual void nakresli(); // PØÍKLAD 17.8: virtual
// virtual void nakresli(); // PØÍKLAD 17.8: virtual

// pøi pøiøazování ukazatelù se informace z instancí neztrácejí
auto vypis_upravujeme_tridy_grafickych_objektu() -> void
{
    // potøebujeme, aby program za bìhu zjistil, jakého typu je instance,
    // na kterou tento ukazatel ukazuje a podle toho zavolal
    // odpovídající metodu
    // jinımi slovy, potøebujeme, aby pouil pozdní vazbu
    //              tzv. late binding
    // Implementace pozdní vazby: virtuální metody
    // Metodu, pro kterou má pøekladaè pouít pozdní vazbu, deklarujeme jako virtuální.

    graficky_objekt g(241);
    bod_potomek b(201, 335, 123);

    // Máme-li ukazatel
    graficky_objekt *pg;

    // pøiøadíme-li mu adresu instance tøídy bod
    pg = &b;

    // a zkusíme-li tento bod nakreslit pøíkazem
    pg->nakresli();

    // budeme zklamáni, nebo program nakreslí obecnı grafickı objekt
    // tedy vypíše [123]


    /*
        usecka_potomek u(100, 200, 300, 400);
        u.set_tloustka( 16 );
        cout << Tabs::getTabChars() << u.get_tloustka();
        u.nakresli();
    */
}


//
// PØÍKLAD 17.9: VIRTUÁLNÍ DESTRUKTOR
//
auto vypis_virtualni_destruktor() -> void
{
    // grafickı objekt inicializujeme novım potomkem bod
    graficky_objekt *pgo = new bod_potomek(201, 335, 123);
    delete pgo;
    // bez virtual volá ~graficky_objekt();
    // s virtual volá virtual ~bod_potomek() override;
}

//
// PØÍKLAD 17.10: MAEME GRAFICKİ OBJEKT
//
auto vypis_mazeme_graficky_objekt() -> void
{
    graficky_objekt *pgo = new bod_potomek(201, 335, 123);
    pgo->nakresli();
    pgo->smaz();
    // V tìle metody smaz() voláme virtuální metodu nakresli() bez kvalifikace,
    // take se uplatní pozdní vazba a program zavolá metodu odpovídající
    // skuteènému typu instance.
}


//
// PØÍKLAD 17.11: MAEME GRAFICKİ OBJEKT V DESTRUKTORU
//
// volání virtuálních metod v konstruktoru a v destruktoru se vyhıbáme
auto vypis_mazeme_graficky_objekt_v_destruktoru() -> void
{
    graficky_objekt *pgo = new bod_potomek(201, 335, 123);
    delete pgo;
}
















//usecka_potomek::usecka_potomek(int _x, int _y, int _barva, int _tloustka)
//    :graficky_objekt(_barva) // Volání konstruktorù pøedkù zapisujeme v inicializaèní èásti konstruktoru potomka.
//{
//    set_barva(_barva); // volá metodu pøedka
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
//    // smaz(); // opakování volání je zde zámìr
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

// PØÍKLAD 17.4: OSTATNÍ METODY TØÍDY bod_potomek
