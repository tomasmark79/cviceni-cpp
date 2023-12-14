#ifndef SLOZITEJSI_PROGRAMY_H_INCLUDED
#define SLOZITEJSI_PROGRAMY_H_INCLUDED

namespace piskvorky_sw
{

bool vstup();
bool kontrola_meze();
void napoveda();
void faktorial_priprava();
int faktorial_v_namespace(int m);
int faktorial_rekurzivni_v_namespace(int m);

extern int n;
}

int faktorial(int m);
double faktorial(double m);
int faktorial_rekurzivni(int m);
void vypis_globalni_promennou();
int vstup_faktorial();
void vstup_zadej_dve_cisla_ktere_je_vetsi();

#endif // SLOZITEJSI_PROGRAMY_H_INCLUDED
