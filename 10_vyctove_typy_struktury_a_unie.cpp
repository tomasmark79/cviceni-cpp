#include <iostream>
#include "10_vyctove_typy_struktury_a_unie.h"
#include <stdint.h>


using namespace std;

// slab� v��tov� typy
enum binarky {suda = 0B01010101, licha = 0B11010101};
enum den {pondeli=1, utery=2, streda=4, ctvrtek=8, patek=16, sobota=32, nedele=64 };
enum rocni_obdobi {jaro, leto, podzim, zima};
enum vyctove_hodnoty_nemusi_tvorit_posloupnost {jedna=1,dve=1};


class nastroj
{
public:
    pole() {}; // ... a dal�� metody ...

private:
    enum {minimum = 10, maximum = 20};
    int nemagicke_cislo_minimum[minimum];
    int nemagicke_cislo_maximum[maximum];
};

// siln� v��tov� typy - mohou m�t stejn� identifik�tory
enum class rezim_otevreni { cteni, zapis=10, cteni_a_zapis };
enum class uroven_opravneni { cteni, zapis=10, spusteni, vse };

void otevri_s_rezimem(string jmeno, rezim_otevreni rezim)
{
    cout << jmeno << " " << "Re�im otev�en�: " << (int)rezim << endl;
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
    int bitova_pole: 5; //Sou��st� struktury mohou b�t tak� tzv. bitov� pole.
};

char typy[][10] { "soukrom�", "pracovn�", "jin�" };


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


/* �pln� deklarace struktury je vlastn� definice, ne�pln� deklarace je informativn� deklarace. */

/*
V programu, kter� modeluje telefonn� s�, pot�ebujeme strukturu pristroj popisuj�c� telefonn� p��stroj a struk-
turu majitel obsahuj�c� informace o majiteli p��stroje. Ov�em vztah mezi p��strojem a majitelem je oboustran-
n�,  tak�e  ka�d�  majitel  m�  alespo�  jeden  p��stroj  a  ka�d�  p��stroj  m�  majitele. To  znamen�,  �e  pot�ebujeme,  aby
struktura  pristroj  obsahovala  ukazatel  na  strukturu  majitel  a  naopak,  aby  struktura  majitel
obsahovala ukazatel na strukturu pristroj.
Zde mus�me pou��t ne�plnou deklaraci alespo� jedn� ze zm�n�n�ch struktur:
*/

struct pristroj; // Ne�pln� deklarace

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
    // Ne�pln� deklarace
    majitel *maj = new majitel;
    maj->jmeno_majitele = "Tom�";
    maj->cislo_majitele = "777123456";
    maj->telefon = new pristroj;
    maj->telefon->jmenopristroje = "Nokia";

    cout << maj->jmeno_majitele << " " << maj->cislo_majitele << " " << maj->telefon->jmenopristroje << endl;

    // pristroj pri;
    //pri.jmenopristroje = "Tom�"


    // anonymni union - jeliko� pot�ebujeme pouze jednu instanci v programu pro zji�t�n� endianu
    // Zde unie nep�edstavuje datov� typ, pouze p�ikazuje p�eklada�i, aby prom�nn� ��slo a bajty ulo�il v pam�ti
    // na stejn� m�sto.
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
        cout << "Velk� endi�n" << endl;
    }
    // else if(info.bajty[0] == 0x78)
    else if(bajty[0] == 0x78)
    {
        cout << "Mal� endi�n" << endl;
    }
    else
    {
        cout << "Tohle by nem�lo nastat nikdy" << endl;
    }

    priklad ukazka{ 124 };
    cout << "unie: " << "cel� " << ukazka.cele << " re�ln� " << ukazka.cele << " p�smeno " << ukazka.pismeno << endl;

    // struktury
    kontakt k2 = { 2, "Jan", "Brhel", "436 761 989", typ_kontaktu::soukromy };
    k2.prijmeni[3] = 'a';
    vypis_kontaktu(&k2);

    kontakt k1 = { 1, "Ivo", "Klep��", "321 543 765", typ_kontaktu::pracovni, streda};
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

    // bitov� p��znaky
    den zavreno = (den) (pondeli | patek);
    // cout << "Zavreno: " << binarizuj(zavreno) << endl;
    den dnes = (den)utery;
    cout << "dnes je " << ((dnes & zavreno) ? "zav�eno" : "otev�eno") << endl;
    /*
        if (dnes & zavreno)
        {
            cout << "zav�eno" << endl;
        }
        else
        {
            cout << "otev�eno" << endl;
        }
    */

}

