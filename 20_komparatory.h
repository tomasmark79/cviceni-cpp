#ifndef KOMPARATORY_H_INCLUDED
#define KOMPARATORY_H_INCLUDED

#include "20_priklad.h"

using namespace std;
bool alfabeticky_api(const std::string& lajna1, const std::string& lajna2);
bool alfabeticky(string lajna1, string lajna2);
bool lexikograficky(string lajna1, string lajna2);
bool podle_cisel(string lajna1, string lajna2);

bool walfabeticky(wstring lajna1, wstring lajna2);
bool wlexikograficky(wstring lajna1, wstring lajna2);
bool wpodle_cisel(wstring lajna1, wstring lajna2);

#endif // KOMPARATORY_H_INCLUDED
