#ifndef FUNKCE_H_INCLUDED
#define FUNKCE_H_INCLUDED

//
// P��KLAD 13.18: ZOBRAZEN� HODNOT FUNKCE
//

auto vypis_volani_lambda_vyraz() -> void;

void vypis_volani_funkce_graf_pres_ukazatel();

using mat_funkce = double(*)(double);
using zobr_funkce = void(*)(double* x, double* y, int kolik, std::string jmeno);

void graf(mat_funkce f, zobr_funkce zobraz, double od, double po,
          int kolik, std::string jmeno);

auto vypis_ukazatel_na_funkci() -> void;

auto vypis_vyber_pretizene_funkce()->void;

auto vypis_vysledku_pretizeni_funkce_vypoctu_plochy_trojuhelnika()->void;

auto nepojmenovane_parametry(int n, int, char) -> void;
auto vypis_funkci_variadicke_sablony() ->void;

auto vypis_vypustky() -> void;

auto vypis_printf() -> void;
auto vypis_tisk() -> void;

auto volani_strlen_konstantni_ukazka() -> void;

void vypis_moc3();

void vypis_proverka(int i, int j);

auto vypis_zakazana_funkce() -> void;

void vypis_vysledku_ukazatelu_na_funkce_double();
auto vypis_vysledku_ukazatelu_na_funkce_double() -> void; // Nov�

// void vypis_volani_funkci();
auto vypis_volani_funkci() -> void; // Nov�


#endif // FUNKCE_H_INCLUDED
