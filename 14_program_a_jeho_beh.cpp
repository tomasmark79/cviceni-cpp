#include <iostream>
#include "14_program_a_jeho_beh.h"

using namespace std;
/*
int main();
int main(int argv);
int main(int argv, char *argc);
int main(int argv, char *argc[], char* env[]); // Nestandardn� roz���en�
*/

auto ukonceni_app() -> void
{
    cout << "Ukon�uji pomoz� p��kazu exit(0), ale vol� zaregistrovan� funkce pomoc� ATEXIT v�razu." << endl;
    exit(0);
}

auto sestreleni_app() -> void
{
    cout << "Sest�eluji pomoz� p��kazu abort(), zde v�e z�stan� bez o�et�en�." << endl;
    abort();
}
