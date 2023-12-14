#include "03_slozitejsi_programy.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace piskvorky_sw;

namespace piskvorky_sw
{

const int horni_mez_vstupu = 12;
const int dolni_mez_vstupu = 0;

int n;
int hodnota_faktorialu[horni_mez_vstupu+1] {1};

bool vstup()
{
    cout << "Zadej cel� ��slo: ";
    cin >> n;
    if(!cin)
    {
        cout << "Zadan� hodnota nep�edstavuje ��slo" << endl;
        return false;
    }
    return true;
}

bool kontrola_meze()
{
    return (n >= dolni_mez_vstupu) && (n <= horni_mez_vstupu);
}

void napoveda()
{
    cout << "Faktori�l zadan� hodnoty nelze spo��tat" << endl;
    cout << "Zadan� hodnota mus� b�t cel� ��slo mezi "
         << dolni_mez_vstupu << " a " << horni_mez_vstupu << endl;
}

void faktorial_priprava()
{
    int i = 1;
    while(i <= horni_mez_vstupu)
    {
        hodnota_faktorialu[i] = i*hodnota_faktorialu[i-1];
        i++;
    }
}

/* p�es pole */
int faktorial_v_namespace(int n)
{
    if(hodnota_faktorialu[1] == 0)
    {
        faktorial_priprava();
    }
    return hodnota_faktorialu[n];
}

int faktorial_rekurzivni_v_namespace(int m)
{
    if(m == 0)
    {
        return 1;
    }
    else
    {
        return m * faktorial_rekurzivni_v_namespace(m - 1);
    }
}
}

// int i = 8, j(9), k = {10}, m{11};
// extern int n;
int globalni_a = 9;

int faktorial(int m)
{
    int s = {1};
    while(m > 1)
    {
        s = s*m--;
    }
    return s;
}

// p�et�en� na typ double
double faktorial(double m)
{
    double s = {1};
    while(m > 1)
    {
        s *= m--;
    }
    return s;
}

int faktorial_rekurzivni(int m)
{
    if(m == 0)
    {
        return 1;
    }
    else
    {
        return m * faktorial_rekurzivni_v_namespace(m - 1);
    }
}

void vypis_globalni_promennou()
{
    int globalni_a = 6;
    cout << globalni_a << " " << ::globalni_a << endl;

    int n;
    cout << "Zadej cel� ��slo: ";
    // cin >> n;
    // if(n >= 0) /* ...d�le zdrojov� k�d stejn� jako p�edt�m... */
    while (cin >> n, n > 0)
    {
        cout << "Jeho faktori�l je " << piskvorky_sw::faktorial_v_namespace(n) << endl;
    }
//    else
//    {
//        cout << "Faktori�l z�porn�ho ��sla neexistuje" << endl;
//    }
}

int vstup_faktorial()
{
    if(vstup() && kontrola_meze())
    {
        cout << "Jeho faktori�l je z namespace" << piskvorky_sw::faktorial_v_namespace << endl;
        cout << "Jeho faktori�l je " << ::faktorial(n) << endl;
        cout << "Jeho faktori�l je z namespace" << ::piskvorky_sw::faktorial_rekurzivni_v_namespace(n) << endl;
        cout << "Jeho faktori�l je " << ::faktorial_rekurzivni(n) << endl;
        return 0;
    }
    else
    {
        napoveda();
    }
    return 1;
}

void vstup_zadej_dve_cisla_ktere_je_vetsi()
{
    cout << "Zadej dv� cel� ��sla: ";
    int m, n, vysledek;
    cin >> m >> n;
    if(m > n)
    {
        vysledek = m;
    }
    else
    {
        vysledek = n;
    }
    cout << "V�t�� je " << vysledek << endl;
}


