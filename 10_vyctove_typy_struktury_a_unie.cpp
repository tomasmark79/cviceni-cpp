#include <iostream>
#include "10_vyctove_typy_struktury_a_unie.h"
#include <stdint.h>


using namespace std;

// slabé výètové typy
enum binarky {suda = 0B01010101, licha = 0B11010101};
enum den {pondeli=1, utery=2, streda=4, ctvrtek=8, patek=16, sobota=32, nedele=64 };
enum rocni_obdobi {jaro, leto, podzim, zima};
enum vyctove_hodnoty_nemusi_tvorit_posloupnost {jedna=1,dve=1};


class nastroj
{
public:
    pole() {}; // ... a další metody ...

private:
    enum {minimum = 10, maximum = 20};
    int nemagicke_cislo_minimum[minimum];
    int nemagicke_cislo_maximum[maximum];
};

// silné výètové typy - mohou mít stejné identifikátory
enum class rezim_otevreni { cteni, zapis=10, cteni_a_zapis };
enum class uroven_opravneni { cteni, zapis=10, spusteni, vse };

void otevri_s_rezimem(string jmeno, rezim_otevreni rezim)
{
    cout << jmeno << " " << "Režim otevøení: " << (int)rezim << endl;
};

enum class typ_kontaktu {soukromy, pracovni, jiny};
struct kontakt
{
    int id;
    char jmeno[30];
    char prijmeni[30];
    char telefon[20];
    typ_kontaktu typ;
    den chodi_v;
    int bitova_pole: 5; //Souèástí struktury mohou být také tzv. bitová pole.
};

char typy[][10] { "soukromý", "pracovní", "jiný" };


void vypis_kontaktu(const kontakt *pk)
{
    cout << pk->id << ": " << pk->jmeno << " " << pk->prijmeni
         << " (tel. " << pk->telefon << ", " << typy[(int)(pk->typ)]
         << ")" << endl;
}

union priklad
{
    int cele;
    double realne;
    unsigned char pismeno;
};


union dekoder
{
    uint32_t cislo;
    uint8_t bajty[4];
};


/* Úplná deklarace struktury je vlastnì definice, neúplná deklarace je informativní deklarace. */

/*
V programu, který modeluje telefonní sí, potøebujeme strukturu pristroj popisující telefonní pøístroj a struk-
turu majitel obsahující informace o majiteli pøístroje. Ovšem vztah mezi pøístrojem a majitelem je oboustran-
ný,  takže  každý  majitel  má  alespoò  jeden  pøístroj  a  každý  pøístroj  má  majitele. To  znamená,  že  potøebujeme,  aby
struktura  pristroj  obsahovala  ukazatel  na  strukturu  majitel  a  naopak,  aby  struktura  majitel
obsahovala ukazatel na strukturu pristroj.
Zde musíme použít neúplnou deklaraci alespoò jedné ze zmínìných struktur:
*/

struct pristroj; // Neúplná deklarace

struct majitel
{
    pristroj *telefon;
    string jmeno_majitele;
    string cislo_majitele;
};
struct pristroj
{
    majitel *vlastnik;
    string jmenopristroje;
};


void vypis_prikladu_z_teto_sekce_10()
{
    // Neúplná deklarace
    majitel *maj = new majitel;
    maj->jmeno_majitele = "Tomáš";
    maj->cislo_majitele = "777123456";
    maj->telefon = new pristroj;
    maj->telefon->jmenopristroje = "Nokia";

    cout << maj->jmeno_majitele << " " << maj->cislo_majitele << " " << maj->telefon->jmenopristroje << endl;

    // pristroj pri;
    //pri.jmenopristroje = "Tomáš"


    // anonymni union - jelikož potøebujeme pouze jednu instanci v programu pro zjištìní endianu
    // Zde unie nepøedstavuje datový typ, pouze pøikazuje pøekladaèi, aby promìnné èíslo a bajty uložil v pamìti
    // na stejné místo.
    union
    {
        uint32_t cislo;
        uint8_t bajty[4];
    };

    cislo = 0x12345678;

    // union ukazka
    dekoder info{ 0x12345678 };
    // if (info.bajty[0] == 0x12)
    if (bajty[0] == 0x12)
    {
        cout << "Velký endián" << endl;
    }
    // else if(info.bajty[0] == 0x78)
    else if(bajty[0] == 0x78)
    {
        cout << "Malý endián" << endl;
    }
    else
    {
        cout << "Tohle by nemìlo nastat nikdy" << endl;
    }

    priklad ukazka{ 124 };
    cout << "unie: " << "celé " << ukazka.cele << " reálné " << ukazka.cele << " písmeno " << ukazka.pismeno << endl;

    // struktury
    kontakt k2 = { 2, "Jan", "Brhel", "436 761 989", typ_kontaktu::soukromy };
    k2.prijmeni[3] = 'a';
    vypis_kontaktu(&k2);

    kontakt k1 = { 1, "Ivo", "Klepáè", "321 543 765", typ_kontaktu::pracovni, streda};
    string jmeno = "Tomas";
    otevri_s_rezimem (jmeno, rezim_otevreni::zapis);

    // enumeratory
    den zaviraci = nedele;
    cout << zaviraci << endl;

    rocni_obdobi zimni = zima;
    rocni_obdobi letni = leto;
    rocni_obdobi jarni = jaro;
    rocni_obdobi podzimni = podzim;

    den promitani = (den)sobota;
    cout << promitani << endl;

    cout << suda << endl;
    cout << licha << endl;

    // bitové pøíznaky
    den zavreno = (den) (pondeli | patek);
    // cout << "Zavreno: " << binarizuj(zavreno) << endl;
    den dnes = (den)utery;
    cout << "dnes je " << ((dnes & zavreno) ? "zavøeno" : "otevøeno") << endl;
    /*
        if (dnes & zavreno)
        {
            cout << "zavøeno" << endl;
        }
        else
        {
            cout << "otevøeno" << endl;
        }
    */

}

