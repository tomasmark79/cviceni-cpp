#include <iostream>
#include <limits>
#include "09_strom.h"

// konstruktor

strom::strom()
{
    // uzel(string _znak, bool _otazka, uzel *_ma, uzel *_nema) // deklarace v *.h

    /*  Konstruktor  vytvo��  strom  podle  obr�zku  9.5;  to  znamen�,  �e  vytvo��  ko�en,  ulo��  do  n�j  text
        "rohy",  informaci,  �e  jde  o  ot�zku,  a  dva  ukazatele  nikam.
        */
    koren = new uzel{"rohy", true, nullptr, nullptr};

    /*  Pak  vytvo��  dva  uzly  obsahuj�c� jm�na  zv��at,  informaci,
        �e  nejde  o  ot�zku,  a  ukazatele  na  n�  ulo��  do  slo�ek  ma,  resp.  nema ko�ene.
        */
    koren->ma = new uzel{ "v�l", false, nullptr, nullptr };
    koren->nema = new uzel{ "��ba", false, nullptr, nullptr };

    /*  Poznamenejme, �e t�lo konstruktoru jsme mohli zapsat stru�n�ji, i kdy� m�n� p�ehledn� takto:
        koren =
        new uzel{"rohy", true,
        new uzel{   "v�l", false, nullptr, nullptr},
        new uzel{   "��ba", false, nullptr, nullptr}
                };
    */
};

// destruktor
strom::~strom()
{
    vyprazdni(koren);
}

// jen v priv�tn�m prostoru
void strom::vyprazdni(uzel* koren)
{
    if (!koren) return;
    vyprazdni(koren->ma);
    vyprazdni(koren->nema);
    delete koren;
}

// pro ��ely vol�n� mimo priv�tn� prostor
void strom::vyprazdni()
{
    vyprazdni(koren);
    koren = nullptr;
}

// od ko�ene k listu
string strom::hledej()
{
    aktualni = koren;

    // jde o ot�zku
    while (aktualni->otazka)
    {
        cout << "M� to " << aktualni->znak << "? ";
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
        // ma�e p�edchoz� vstupn� informace
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "A co to tedy je? ";
        getline(cin, zvire);
        // mo�nost opravy
        cout << "Jste si jist�, �e je to " << zvire << "?";
        cin >> potvrzeni;
    } while (potvrzeni[0]=='n');

    do {
        cout << "��m se li�� " << zvire << " a " << aktualni->znak << "? ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, rozdil); // n�kolik slov, proto getline = �te do konce ��dky

        // mo�nost opravy
        cout << "Jste si jist�, �e m� " << rozdil << "?";
        cin >> potvrzeni;
    } while (potvrzeni[0]=='n');

    cout << zvire << " m� " << rozdil << "? ";
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
		//cout << "Odpov�zte 'ano' nebo 'ne' a stiskn�te Enter: ";
		cin >> odpoved;
		rozhodnuto = (odpoved[0] == 'a') || (odpoved[0] == 'n');
	} while (!rozhodnuto);
	return odpoved[0] == 'a';
}

int hraj_hru_hadej_zvire()
{

    cout << "H�d�n� zv��at!" << endl;

    cout << "Mysli si zv��e, j� se budu pt�t." << endl
         << "Odpov�dej pros�m 'ano' nebo 'ne' (sta�� 'a' nebo 'n')."
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
    while (mam_pokracovat("M�m h�dat dal�� zv��e? "));

    return 0;
}
