#include <iostream>
#include <limits>
#include "11_vyrazy.h"

using namespace std;

// definice pøetienıch funkcí
void f(int i){};
void f(char i){};

void vypis_volani_funkce_dle_operatoru()
{
    char c = 'a';
    f(c);

    f(+c);  // zavoláme funkci s parametrem typu int.
            // Dùvod je prostı: Operátor unární plus ve vırazu +c zpùsobil,
            // e s operandem probìhlo celoèíselné rozšíøení,
            // tedy e se typ char pøevedl na int.

    f(++c); // zavoláme funkci s parametrem typu char, nebo pøed pouitím
            // operátoru ++ neprobíhají s operandem ádné konverze.

    f(c++); // char - vezme hodnotu a a pak pøièítá

    f(-c);  // int

    //další pøíklad
    int i = -1;
    unsigned j = 0;
    cout << j+i << endl; // neoèekávanı vısledek

    // NEOÈEKÁVANİ VİSLEDEK
    int x = numeric_limits<int>::max();
    int y = 1; // pøeteèe int
    long long z = 0;
    long long soucet;

    long long soucet1 = x + y + z; // zùstane int
    long long soucet3 = x + (y + z); // (2)
    cout << soucet1 << endl << soucet3 << endl;

    cout << je_pracovni_den(pondeli) << " :" << pondeli << endl;
    cout << je_pracovni_den(utery) << " :" << utery<< endl;
    cout << je_pracovni_den(sobota) << " :" << sobota<< endl;

}

bool je_pracovni_den(den d)
{
    // return pondeli <= d <= patek; // v matice ano, v c++ nelze
    return (pondeli <= d) && (d <= patek);
}

//Pøetypování vyjádøená klíèovım slovem
//Kadı z tìchto ètyø operátorù pokrıvá èást moností „obecného“ pøetypovacího operátoru,
//o nìm jsme hovoøili v pøedchozím oddílu. Úlohy jsou mezi nì rozdìleny takto:
//Operátor const_cast umoòuje v typu konvertovaného vırazu pøidávat nebo odebírat
//modifikátory const a volatile, nic jiného. (O modifikátoru volatile se krátce zmí-
//níme v oddílu 12.3.4.)
//Operátor dynamic_cast slouí k pøetypování mezi objektovımi typy v rámci jedné hie-
//rarchie, tedy mezi instancemi pøedkù a potomkù. Lze ho také pouít k pøetypování ukazate-
//le na pøedka na ukazatel na potomka a naopak. Pøitom kontroluje, zda má toto pøetypování
//smysl.
//Operátor static_cast pouíváme pro vìtšinu bìnıch pøetypování.
//Operátor reinterpret_cast slouí k operacím, které lze nejlépe oznaèit jako „špina-
//vou práci“. Mùe jít o pøevod celého èísla na ukazatel, instance struktury jednoho typu na
//instanci jiného, nesouvisejícího typu apod.
