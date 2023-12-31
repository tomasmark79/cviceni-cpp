#include <iostream>
#include "14_program_a_jeho_beh.h"

using namespace std;

/*
int main();
int main(int argv);
int main(int argv, char *argc);
int main(int argv, char *argc[], char* env[]); // Nestandardní rozšíøení
*/
void fce1()
{
    std::cout << "ukonèovací práce: fce1" << std::endl;
};
void fce2()
{
    std::cout  << "ukonèovací práce: fce2" << std::endl;
};


void ukonceni_app()
{
    cout << "Ukonèuji pomozí pøíkazu exit(0), ale volá zaregistrované funkce pomocí ATEXIT vırazu." << endl;
    exit(0);
}

void sestreleni_app()
{
    cout << "Sestøeluji pomozí pøíkazu abort(), zde vše zùstané bez ošetøení." << endl;
    abort();

}
