#ifndef DEDENI_H_INCLUDED
#define DEDENI_H_INCLUDED

//
// P��KLAD 17.1: GRAFICK� OBJEKTY � SPOLE�N� P�EDEK, PRVN� POKUS
//
auto vypis_vytvoreni_grafickeho_objektu() -> void;
auto vypis_oriznuti_objektu() -> void;
auto vypis_prirazovani_ukazatelu() -> void;
auto vypis_upravujeme_tridy_grafickych_objektu() -> void;
auto vypis_virtualni_destruktor() -> void;
auto vypis_mazeme_graficky_objekt() -> void;
auto vypis_mazeme_graficky_objekt_v_destruktoru() -> void;
auto vypis_lepsi_navrh() -> void;

// od p��kladu 17.12
// p�edek
class graficky_objekt
{
    int barva;
    bool nakreslen;
protected:
    virtual void proved_kresleni();
    virtual void proved_mazani();
public:
    graficky_objekt(int _barva);
    virtual ~graficky_objekt();
    int get_barva();
    void set_barva(int _barva);
    void nakresli(); // P��KLAD 17.8: virtual
    void smaz();
    bool je_nakreslen();
};

// potomek
class bod_potomek : public graficky_objekt
{
    int x, y;
protected:
    virtual void proved_kresleni() override;
    virtual void proved_mazani() override;
public:
    bod_potomek(int _x, int _y, int _barva);
    // ~bod_potomek();
    virtual ~bod_potomek() override;
//    int get_x();
//    int get_y();

    void set_x(int _x);
    void set_y(int _y);

};

//// potomek
//class usecka_potomek : public graficky_objekt
//{
//    int x, y, tloustka;
//public:
//
//    usecka_potomek();
//    usecka_potomek(int _x, int _y, int _tloustka, int _barva);
//    // ~usecka_potomek();
//    virtual ~usecka_potomek() override;
//    int get_x();
//    int get_y();
//    void set_x(int _x);
//    void set_y(int _y);
//    int get_tloustka();
//    void set_tloustka(int _tloustka);
//    virtual void nakresli() override;
//};



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


// plat� do p��kladu 17.10
//// p�edek
//class graficky_objekt
//{
//    int barva;
//public:
//
//    // graficky_objekt();
//    graficky_objekt(int _barva);
//    virtual ~graficky_objekt(); // P��KLAD 17.8: virtual
//    int get_barva();
//    void set_barva(int _barva);
//    virtual void nakresli(); // P��KLAD 17.8: virtual
//    void smaz();
//    virtual string kdojsem();
//};
//
//// potomek
//class bod_potomek : public graficky_objekt
//{
//    int x, y;
//public:
//
//    bod_potomek();
//    bod_potomek(int _x, int _y, int _barva);
//    // ~bod_potomek();
//    virtual ~bod_potomek() override;
//    int get_x();
//    int get_y();
//    void set_x(int _x);
//    void set_y(int _y);
//    virtual void nakresli() override;
//    virtual string kdojsem() override;
//};






















#endif // DEDENI_H_INCLUDED
