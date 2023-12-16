#ifndef DEDENI_H_INCLUDED
#define DEDENI_H_INCLUDED

//
// P��KLAD 17.1: GRAFICK� OBJEKTY � SPOLE�N� P�EDEK, PRVN� POKUS
//
auto vypis_vytvoreni_grafickeho_objektu() -> void ;
auto vypis_oriznuti_objektu() -> void;
auto vypis_prirazovani_ukazatelu() -> void;
auto vypis_virtualni_metody() -> void;

class graficky_objekt
{
    int barva;
public:
    // graficky_objekt();
    graficky_objekt(int _barva);
    ~graficky_objekt();
    int get_barva();
    void set_barva(int _barva);
    void nakresli();
    void smaz();
};

class bod_potomek : public graficky_objekt
{
    int x, y;
public:
    bod_potomek();
    bod_potomek(int _x, int _y, int _barva);
    ~bod_potomek();
    int get_x();
    int get_y();
    void set_x(int _x);
    void set_y(int _y);
    void nakresli();
    void smaz();
};


//
// 17.1.2 Jak vypad� odvozen� t��da
//

// deklarace t��dy - p��stup ke zd�d�n�m slo�k�m
// ---------------------------------------------

// class bod_potomek : public graficky_objekt
    // public: public = public, protected = protected, private = nebudou p��mo dostupn�, ale metody potomka mohou pro p��stup vyu��t metody p�edka

// class bod_potomek : protected graficky_objekt
    // public = protected, protected = protected a private nebudou p��mo dostupn�, ale metody potomka mohou pro p��stup vyu��t metody p�edka

// class bod_potomek : private graficky_objekt
    // public = private, protected = private, private = nebudou p��mo dostupn�, ale metody potomka mohou pro p��stup vyu��t metody p�edka

// class bod_potomek :  ***** graficky_objekt
    // ***** dosad� private:

// struct bod_potomek :  ***** graficky_objekt
    // ***** dosad� public:

//
// P��KLAD 17.2: T��DA BOD je potomkem t��dy graficky_objekt
//


























#endif // DEDENI_H_INCLUDED
