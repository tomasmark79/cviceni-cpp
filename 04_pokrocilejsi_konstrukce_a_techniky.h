#ifndef POKROCILEJSI_KONSTRUKCE_A_TECHNIKY_H_INCLUDED
#define POKROCILEJSI_KONSTRUKCE_A_TECHNIKY_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>

class Napis
{
   public:
      Napis(std::string txt);   // Konstruktor
      Napis();             // Implicitní konstruktor
      ~Napis();            // Destruktor
      std::string text() { return _text; } // Pøístupové metody

    // pozn. z 13.1.3 Rùzné modifikátory
    // inline =
    // Volání takové funkce není pøíliš efektivní, nebo operace, které jsou potøebné pro pøedání pa-
    // rametrù, skok do funkce a návrat z ní, mohou zabrat více èasu než vlastní tìlo funkce. Proto
    // nabízí jazyk C++ specifikátor inline, který oznaèuje vloženou funkci (inline function).
    // Vložené funkce používáme stejnì jako ostatní funkce, pøekladaè by toto volání však mìl
    // pøeložit jinak: místo skoku do podprogramu by mìl na místo volání vložit tìlo funkce, tedy pøí-
    // kazy, které vypoètou výsledek. V pøípadì metody text() by tedy mìl na místo volání vložit
    // pøímo datovou složku _text aktuální instance.
      inline void text(std::string txt) { _text = txt; }


      // void vypis() const; // Výpis na konzolu
      auto vypis() const -> void ;
      static int pocet_napisu();

   protected:

   private:
      std::string _text; // Soukromá datová složka
      static int pocet;       // Poèet existujících nápisù

};

void vypis_pocet_napisu();
void vypis_mnoho_verzi_teze_tridy();

// V oddílu 4.1 jsme si øekli, že deklaraci tøídy ukládáme do hlavièkového souboru
// a definice metod, které nejsou zapsány v tìle tøídy, ukládáme do implementaèního souboru.
// V pøípadì šablon objektových typù implementaèní soubor nevytváøíme a do hlavièkového souboru ukládáme
// jak šablonu tøídy, tak i šablony jejích metod

// Šablona Dvojice
template<typename T1, typename T2>
class Dvojice
{
public:
    Dvojice(T1 arg_prvni, T2 arg_druha); //Konstruktor s argumenty
    Dvojice()
    {
        n_instanci++;
    }; // Konstruktor implicitní
    ~Dvojice(); // Konstruktor implicitní

    static int get_pocet_instanci(void);

    T1 get_prvni(void); // metoda get
    T2 get_druha(void); // metoda get

    void set_prvni(T1 _prvni); // metoda
    void set_druha(T2 _druha); // metoda

private:
    T1 priv_prvni_slozka; // soukromá datová složka
    T2 priv_druha_slozka; // soukromá datová složka

    static int n_instanci;
};

template<class T1, class T2>
int Dvojice<T1, T2>::n_instanci = 0;

// definice šablony set metody Prvni
template<class T1, class T2>
void Dvojice<T1, T2>::set_prvni(T1 arg_prvni)
{
    priv_prvni_slozka = arg_prvni;
}

// definice šablony set metody Druha
template<class T1, class T2>
void Dvojice<T1, T2>::set_druha(T2 arg_druha)
{
    priv_druha_slozka= arg_druha;
}

// definice šablony get metody Prvni
template<class T1, class T2>
T1 Dvojice<T1, T2>::get_prvni(void)
{
    return priv_prvni_slozka;
}

// definice šablony get metody Druha
template<class T1, class T2>
T2 Dvojice<T1, T2>::get_druha(void)
{
    return priv_druha_slozka;
}

//definice šablony konstruktoru toídy
template<typename T1, typename T2>
Dvojice<T1, T2>::Dvojice(T1 arg_prvni, T2 arg_druha)
{
    set_prvni(arg_prvni);
    set_druha(arg_druha);
    n_instanci++;
}

//definice šablony destruktoru toídy
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
    double pole[dim]; // složky vektoru

public:
    // Výchozí hodnoty parametrù mùžeme uvést jen v jedné deklaraci (nejlépe v první).
    // Jestliže pøi volání jeden parametr vynecháme, musíme vynechat i parametry, které za ním následují
    vektor(double x = 0, double y = 0, double z = 0);
    vektor(double _pole[]);
    // vektor();

    // pøítel pøidán z kapitoly 16.1
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
