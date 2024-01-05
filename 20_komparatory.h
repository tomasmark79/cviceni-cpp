#ifndef KOMPARATORY_H_INCLUDED
#define KOMPARATORY_H_INCLUDED

#include "20_priklad.h"

using namespace std;

bool abecedne(string lajna1, string lajna2); // Opakujeme se
bool alfabeticky(string lajna1, string lajna2);
bool lexikograficky(string lajna1, string lajna2);
bool podle_cisel(std::string lajna1, std::string lajna2);

bool walfabeticky(wstring lajna1, wstring lajna2);
bool wlexikograficky(wstring lajna1, wstring lajna2);
bool wpodle_cisel(wstring lajna1, wstring lajna2);


template<volba::u_komparator f>
bool negace(string lajna1, string lajna2)
{
    return !f(lajna1, lajna2);
}

#endif // KOMPARATORY_H_INCLUDED
