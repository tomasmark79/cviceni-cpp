#include <iostream>
#include <limits>
#include "11_vyrazy.h"

using namespace std;

// definice p�eti�en�ch funkc�
void f(int i){};
void f(char i){};

void vypis_volani_funkce_dle_operatoru()
{
    char c = 'a';
    f(c);

    f(+c);  // zavol�me funkci s parametrem typu int.
            // D�vod je prost�: Oper�tor un�rn� plus ve v�razu +c zp�sobil,
            // �e s operandem prob�hlo celo��seln� roz���en�,
            // tedy �e se typ char p�evedl na int.

    f(++c); // zavol�me funkci s parametrem typu char, nebo� p�ed pou�it�m
            // oper�toru ++ neprob�haj� s operandem ��dn� konverze.

    f(c++); // char - vezme hodnotu a a� pak p�i��t�

    f(-c);  // int

    //dal�� p��klad
    int i = -1;
    unsigned j = 0;
    cout << j+i << endl; // neo�ek�van� v�sledek

    // NEO�EK�VAN� V�SLEDEK
    int x = numeric_limits<int>::max();
    int y = 1; // p�ete�e int
    long long z = 0;
    long long soucet;

    long long soucet1 = x + y + z; // z�stane int
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

//P�etypov�n� vyj�d�en� kl��ov�m slovem
//Ka�d� z t�chto �ty� oper�tor� pokr�v� ��st mo�nost� �obecn�ho� p�etypovac�ho oper�toru,
//o n�m� jsme hovo�ili v p�edchoz�m odd�lu. �lohy jsou mezi n� rozd�leny takto:
//Oper�tor const_cast umo��uje v typu konvertovan�ho v�razu p�id�vat nebo odeb�rat
//modifik�tory const a volatile, nic jin�ho. (O modifik�toru volatile se kr�tce zm�-
//n�me v odd�lu 12.3.4.)
//Oper�tor dynamic_cast slou�� k p�etypov�n� mezi objektov�mi typy v r�mci jedn� hie-
//rarchie, tedy mezi instancemi p�edk� a potomk�. Lze ho tak� pou��t k p�etypov�n� ukazate-
//le na p�edka na ukazatel na potomka a naopak. P�itom kontroluje, zda m� toto p�etypov�n�
//smysl.
//Oper�tor static_cast pou��v�me pro v�t�inu b�n�ch p�etypov�n�.
//Oper�tor reinterpret_cast slou�� k operac�m, kter� lze nejl�pe ozna�it jako ��pina-
//vou pr�ci�. M��e j�t o p�evod cel�ho ��sla na ukazatel, instance struktury jednoho typu na
//instanci jin�ho, nesouvisej�c�ho typu apod.
