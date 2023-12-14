#ifndef VYRAZY_H_INCLUDED
#define VYRAZY_H_INCLUDED

void vypis_volani_funkce_dle_operatoru();

// deklarace pøetížení
void f(int i);
void f(char i);

enum den { pondeli, utery, streda, ctvrtek, patek, sobota, nedele };

bool je_pracovni_den(den d);

#endif // VYRAZY_H_INCLUDED
