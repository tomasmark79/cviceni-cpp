#ifndef ZAKLADNI_A_BAREVNE_GRAFICKE_OBJEKTY_H_INCLUDED
#define ZAKLADNI_A_BAREVNE_GRAFICKE_OBJEKTY_H_INCLUDED
#include <vector>

using std::vector;

auto zakladni_a_barevne_graficke_objekty_staticky() -> void;
auto zakladni_a_barevne_graficke_objekty_dynamicky() -> void;

class barva
{
    int rgb;
public:
    barva(int _rgb)
    {
        rgb = _rgb;
    };
    ~barva() {};
    void set_barva(int _rgb)
    {
        rgb=_rgb;
    };
    int get_barva()
    {
        return rgb;
    };
    void pouzij();
};

class graficky_objekt
{
    bool nakresleno;
protected:
    virtual graficky_objekt* klon() = 0; //abs
    virtual void proved_kresleni() = 0; //abs
    virtual void proved_mazani() = 0; //abs
public:
    graficky_objekt()
    {
        set_nakresleno(false);
    }
    virtual ~graficky_objekt() {}

    void nakresli(); // metoda existuje jen zde
    void smaz(); // metoda existuje jen zde

    void set_nakresleno(bool stav)
    {
        nakresleno = stav;
    };
    bool get_nakresleno()
    {
        return nakresleno;
    };

    friend class obrazek; // dodáno mnou
};

class zakladni_bod : public graficky_objekt
{
    int x, y;
protected:
    virtual zakladni_bod* klon() override
    {
        return new zakladni_bod(*this);
    };
    virtual void proved_kresleni() override;
    virtual void proved_mazani() override {};
public:
    zakladni_bod (int _x, int _y);
    virtual ~zakladni_bod() override {smaz();};
    int get_x();
    int get_y();
    void set_x(int _x)
    {
        x=_x;
    };
    void set_y(int _y)
    {
        y=_y;
    };
    friend class zakladni_usecka;
};

class zakladni_usecka : public graficky_objekt
{
    zakladni_bod pocatek, konec;
protected:
    virtual zakladni_usecka* klon() override
    {
        return new zakladni_usecka(*this);
    };
    virtual void proved_kresleni() override;
    virtual void proved_mazani() override { proved_kresleni(); };
public:
    zakladni_usecka(zakladni_bod _pocatek, zakladni_bod _konec);
    zakladni_usecka(int x1, int y1, int x2, int y2);
    ~zakladni_usecka() {smaz();};
    zakladni_bod get_pocatek();
    zakladni_bod get_konec();
    void set_pocatek(zakladni_bod _pocatek);
    void set_konec(zakladni_bod _konec);
};

class bod : public zakladni_bod
{
    barva barva_bodu;
protected:
    virtual bod* klon() override
    {
        return new bod(*this);
    };
    virtual void proved_kresleni() override;
    virtual void proved_mazani() override { proved_kresleni(); };
public:
    bod(int _x, int _y, barva _barva);
    ~bod() {smaz();};
    void set_barva(barva _barva)
    {
        barva_bodu = _barva;
    };
    barva get_barva()
    {
        return barva_bodu;
    };
};

class usecka : public zakladni_usecka
{
    barva barva_usecky;
protected:
    virtual usecka* klon() override
    {
        return new usecka(*this);
    };
    virtual void proved_kresleni() override;
    virtual void proved_mazani() override { proved_kresleni(); };
public:
    usecka(int x1, int y1, int x2, int y2, barva _barva);
    usecka(zakladni_bod pocatek, zakladni_bod konec, barva _barva);
    ~usecka() {smaz();}
    zakladni_bod get_pocatek();
    zakladni_bod get_konec();
    void set_pocatek(zakladni_bod _pocatek);
    void set_konec(zakladni_bod _konec);
    void set_barva(barva _barva)
    {
        barva_usecky = _barva;
    };
    barva get_barva()
    {
        return barva_usecky;
    };
};

class obrazek : public graficky_objekt
{
    vector<graficky_objekt*> kresba;
protected:
    virtual obrazek* klon() override
    {
        return new obrazek(*this);
    };
    virtual void proved_kresleni() override;
    virtual void proved_mazani() override;
public:
    obrazek();
    obrazek(obrazek& obr);
    ~obrazek();
    void pridej(graficky_objekt &go);
};


// deklarace tøídy - pøístup ke zdìdìným složkám
// ---------------------------------------------

// class bod_potomek : public graficky_objekt
// public: public = public, protected = protected, private = nebudou pøímo dostupné, ale metody potomka mohou pro pøístup využít metody pøedka

// class bod_potomek : protected graficky_objekt
// public = protected, protected = protected a private nebudou pøímo dostupné, ale metody potomka mohou pro pøístup využít metody pøedka

// class bod_potomek : private graficky_objekt
// public = private, protected = private, private = nebudou pøímo dostupné, ale metody potomka mohou pro pøístup využít metody pøedka

// class bod_potomek :  ***** graficky_objekt
// ***** dosadí private:

// struct bod_potomek :  ***** graficky_objekt
// ***** dosadí public:


#endif // ZAKLADNI_A_BAREVNE_GRAFICKE_OBJEKTY_H_INCLUDED
