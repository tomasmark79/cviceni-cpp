#ifndef POKROCILEJSI_KONSTRUKCE_A_TECHNIKY_H_INCLUDED
#define POKROCILEJSI_KONSTRUKCE_A_TECHNIKY_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>

class Napis
{
   public:
      Napis(std::string txt);   // Konstruktor
      Napis();             // Implicitn� konstruktor
      ~Napis();            // Destruktor
      std::string text() { return _text; } // P��stupov� metody

    // pozn. z 13.1.3 R�zn� modifik�tory
    // inline =
    // Vol�n� takov� funkce nen� p��li� efektivn�, nebo� operace, kter� jsou pot�ebn� pro p�ed�n� pa-
    // rametr�, skok do funkce a n�vrat z n�, mohou zabrat v�ce �asu ne� vlastn� t�lo funkce. Proto
    // nab�z� jazyk C++ specifik�tor inline, kter� ozna�uje vlo�enou funkci (inline function).
    // Vlo�en� funkce pou��v�me stejn� jako ostatn� funkce, p�eklada� by toto vol�n� v�ak m�l
    // p�elo�it jinak: m�sto skoku do podprogramu by m�l na m�sto vol�n� vlo�it t�lo funkce, tedy p��-
    // kazy, kter� vypo�tou v�sledek. V p��pad� metody text() by tedy m�l na m�sto vol�n� vlo�it
    // p��mo datovou slo�ku _text aktu�ln� instance.
      inline void text(std::string txt) { _text = txt; }


      // void vypis() const; // V�pis na konzolu
      auto vypis() const -> void ;
      static int pocet_napisu();

   protected:

   private:
      std::string _text; // Soukrom� datov� slo�ka
      static int pocet;       // Po�et existuj�c�ch n�pis�

};

void vypis_pocet_napisu();
void vypis_mnoho_verzi_teze_tridy();

// V odd�lu 4.1 jsme si �ekli, �e deklaraci t��dy ukl�d�me do hlavi�kov�ho souboru
// a definice metod, kter� nejsou zaps�ny v t�le t��dy, ukl�d�me do implementa�n�ho souboru.
// V p��pad� �ablon objektov�ch typ� implementa�n� soubor nevytv���me a do hlavi�kov�ho souboru ukl�d�me
// jak �ablonu t��dy, tak i �ablony jej�ch metod

// �ablona Dvojice
template<typename T1, typename T2>
class Dvojice
{
public:
    Dvojice(T1 arg_prvni, T2 arg_druha); //Konstruktor s argumenty
    Dvojice()
    {
        n_instanci++;
    }; // Konstruktor implicitn�
    ~Dvojice(); // Konstruktor implicitn�

    static int get_pocet_instanci(void);

    T1 get_prvni(void); // metoda get
    T2 get_druha(void); // metoda get

    void set_prvni(T1 _prvni); // metoda
    void set_druha(T2 _druha); // metoda

private:
    T1 priv_prvni_slozka; // soukrom� datov� slo�ka
    T2 priv_druha_slozka; // soukrom� datov� slo�ka

    static int n_instanci;
};

template<class T1, class T2>
int Dvojice<T1, T2>::n_instanci = 0;

// definice �ablony set metody Prvni
template<class T1, class T2>
void Dvojice<T1, T2>::set_prvni(T1 arg_prvni)
{
    priv_prvni_slozka = arg_prvni;
}

// definice �ablony set metody Druha
template<class T1, class T2>
void Dvojice<T1, T2>::set_druha(T2 arg_druha)
{
    priv_druha_slozka= arg_druha;
}

// definice �ablony get metody Prvni
template<class T1, class T2>
T1 Dvojice<T1, T2>::get_prvni(void)
{
    return priv_prvni_slozka;
}

// definice �ablony get metody Druha
template<class T1, class T2>
T2 Dvojice<T1, T2>::get_druha(void)
{
    return priv_druha_slozka;
}

//definice �ablony konstruktoru to�dy
template<typename T1, typename T2>
Dvojice<T1, T2>::Dvojice(T1 arg_prvni, T2 arg_druha)
{
    set_prvni(arg_prvni);
    set_druha(arg_druha);
    n_instanci++;
}

//definice �ablony destruktoru to�dy
template<typename T1, typename T2>
Dvojice<T1, T2>::~Dvojice(void)
{
    // n_instanci--;
}

template<typename T1, typename T2>
int Dvojice<T1, T2>::get_pocet_instanci(void)
{
    return n_instanci;
}


const int dim = 3;
void vypis_vektor();
class vektor
{
// private: je automaticky dosazeno
    double pole[dim]; // slo�ky vektoru

public:
    // V�choz� hodnoty parametr� m��eme uv�st jen v jedn� deklaraci (nejl�pe v prvn�).
    // Jestli�e p�i vol�n� jeden parametr vynech�me, mus�me vynechat i parametry, kter� za n�m n�sleduj�
    vektor(double x = 0, double y = 0, double z = 0);
    vektor(double _pole[]);
    // vektor();

    // p��tel p�id�n z kapitoly 16.1
    // friend vektor operator+(vektor u, vektor w);

    // vektor plus(vektor w);
    vektor operator+(vektor w);
    vektor operator-(vektor w);
    vektor operator*(vektor w);

    void vypis();

    int get_1(void)
    {
        return pole[0];

    };
};

void vypis_zaokrouhleni();

#endif // POKROCILEJSI_KONSTRUKCE_A_TECHNIKY_H_INCLUDED
