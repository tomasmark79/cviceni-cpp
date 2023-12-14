#include <iostream>
#include <limits>
#include "09_strom.h"

// konstruktor

strom::strom()
{
    // uzel(string _znak, bool _otazka, uzel *_ma, uzel *_nema) // deklarace v *.h

    /*  Konstruktor  vytvoøí  strom  podle  obrázku  9.5;  to  znamená,  že  vytvoøí  koøen,  uloží  do  nìj  text
        "rohy",  informaci,  že  jde  o  otázku,  a  dva  ukazatele  nikam.
        */
    koren = new uzel{"rohy", true, nullptr, nullptr};

    /*  Pak  vytvoøí  dva  uzly  obsahující jména  zvíøat,  informaci,
        že  nejde  o  otázku,  a  ukazatele  na  nì  uloží  do  složek  ma,  resp.  nema koøene.
        */
    koren->ma = new uzel{ "vùl", false, nullptr, nullptr };
    koren->nema = new uzel{ "žába", false, nullptr, nullptr };

    /*  Poznamenejme, že tìlo konstruktoru jsme mohli zapsat struènìji, i když ménì pøehlednì takto:
        koren =
        new uzel{"rohy", true,
        new uzel{   "vùl", false, nullptr, nullptr},
        new uzel{   "žába", false, nullptr, nullptr}
                };
    */
};

// destruktor
strom::~strom()
{
    vyprazdni(koren);
}

// jen v privátním prostoru
void strom::vyprazdni(uzel* koren)
{
    if (!koren) return;
    vyprazdni(koren->ma);
    vyprazdni(koren->nema);
    delete koren;
}

// pro úèely volání mimo privátní prostor
void strom::vyprazdni()
{
    vyprazdni(koren);
    koren = nullptr;
}

// od koøene k listu
string strom::hledej()
{
    aktualni = koren;

    // jde o otázku
    while (aktualni->otazka)
    {
        cout << "Má to " << aktualni->znak << "? ";
        string odpoved;
        cin >> odpoved;
        aktualni = odpoved[0] == 'a' ? aktualni->ma : aktualni->nema;
    }
    return aktualni->znak;
}

void strom::pridej_zvire()
{
    string zvire;
    string rozdil;
    string potvrzeni;

    do {
        // maže pøedchozí vstupní informace
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "A co to tedy je? ";
        getline(cin, zvire);
        // možnost opravy
        cout << "Jste si jistý, že je to " << zvire << "?";
        cin >> potvrzeni;
    } while (potvrzeni[0]=='n');

    do {
        cout << "Èím se liší " << zvire << " a " << aktualni->znak << "? ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, rozdil); // nìkolik slov, proto getline = ète do konce øádky

        // možnost opravy
        cout << "Jste si jistý, že má " << rozdil << "?";
        cin >> potvrzeni;
    } while (potvrzeni[0]=='n');

    cout << zvire << " má " << rozdil << "? ";
    string odpoved;
    cin >> odpoved;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (odpoved[0] == 'a')
    {
        aktualni->nema = new uzel(*aktualni);
        aktualni->ma = new uzel{ zvire, false, nullptr, nullptr };
    }
    else
    {
        aktualni->ma = new uzel(*aktualni);
        aktualni->nema = new uzel{ zvire, false, nullptr, nullptr };
    }
    aktualni->otazka = true;
    aktualni->znak = rozdil;
}

bool mam_pokracovat(string dotaz)
{
	string odpoved;
	bool rozhodnuto;
	do
	{
		cout << dotaz;
		//cout << "Odpovìzte 'ano' nebo 'ne' a stisknýte Enter: ";
		cin >> odpoved;
		rozhodnuto = (odpoved[0] == 'a') || (odpoved[0] == 'n');
	} while (!rozhodnuto);
	return odpoved[0] == 'a';
}

int hraj_hru_hadej_zvire()
{

    cout << "Hádání zvíøat!" << endl;

    cout << "Mysli si zvíøe, já se budu ptát." << endl
         << "Odpovídej prosím 'ano' nebo 'ne' (staèí 'a' nebo 'n')."
         << endl << endl;


    strom str;


    do
    {
        string zvire = str.hledej();
        cout << "Je to " << zvire << "? ";
        string odpoved;
        cin >> odpoved;
        if (odpoved[0] != 'a')
        {
            str.pridej_zvire();
        }
    }
    while (mam_pokracovat("Mám hádat další zvíøe? "));

    return 0;
}
