#include <iostream>
#include "06_zakladni_datove_typy.h"
#include <limits>
#include <cmath>

using namespace std;

char prevod_na_velke_znaky(char c)
{
    if ((c >= 'a') && (c <= 'z'))
    {
        c = c - 'a' + 'A';
    }
    return c;
}

string binarizuj(int m)
{
    if (m == 0)
    {
        return "0";
    }

    string vysledek; // Bude obsahovat výsledek
    bool zaporne = m < 0; // Zapamatuj si znaménko m
    m = abs(m); // Dále pracujeme s absolutní hodnotou
    char znak[2] { '0', '1' }; // Pole obsahující èíslice

    while (m) // Totéž co while(m != 0) {...
    {
        // Vypoèti èíslici a pøipoj ji
        vysledek = znak[m % 2] + vysledek; // k výsledku
        m /= 2; // Odtrhni poslední èíslici
    }

    if (zaporne) // Bylo-li m < O, pøipoj minus
    {
        vysledek = '-' + vysledek;
    }
    return vysledek; // a vra výsledek
}

int vypis_zaokrouhlovaci_chyby()
{
    cout << "Výpis èísel od 0 do 0,9 po jedné desetinì: " << endl;
    const double delta = 0.1;
    double x = 0.0;
    double y = 0.0;

//while (x < 1.0)
    double eps = numeric_limits<double>::epsilon();
    while (x < 1 - numeric_limits<double>::epsilon())
    {
        cout << x << endl;
        x += delta;
        y = x - numeric_limits<double>::epsilon();
    }
    return 0;
}

void vypis_zaokrouhlovaci_priklady()
{

    vypis_zaokrouhlovaci_chyby();

    cout << "Binarne:" << binarizuj(-65535) << endl;

    // tisk int
    cout << "Hello world!" << endl;
    int cislo{0};
    cout << numeric_limits<short>::max() << endl;

    // tisk hex
    short x;
    x = 0x12345678; // Totéž co x = 305419896
    cout << "0x" << hex << x << endl; // zahodí se první 2 bajty
    cout << prevod_na_velke_znaky('a') << endl;

    // tisk char
    // dva druhy implementace 1 byte
    basic_string<char> _text_char_no_template{"Ja jsem 1. byte char"};
    string _text_char_from_template{"Ja jsem 1. byte char"};
    cout << _text_char_no_template << " & " << _text_char_from_template << endl;

    // tisk wchar
    // dva druhy implementace 2 byte
    basic_string<wchar_t> _text_wchar_no_template{L"Ja jsem 2 bytes wchar_t"};
    wstring _text_wchar_from_template{L"Ja jsem 2 bytes wchar_t"};
    wcout << _text_wchar_no_template << L" & " << _text_wchar_from_template << endl;

    // tisk char8 - od C++20
    // dva druhy implementace 2 byte
    //   basic_string<char8_t> _text_char16t_no_template{u"char8t text"};
    //   for (char8_t c : _text_char8t_no_template) {
    //      wcout << static_cast<wchar_t>(c);
    //   }
    //   wcout << endl;
    //   char8_t _text_char8t_from_template {u'a'};
    //   wcout << L"Znak a: " << _text_char8t_from_template << endl;

    // tisk char16t
    // dva druhy implementace 2 byte
    basic_string<char16_t> _text_char16t_no_template{u"char16t text"};
    for (char16_t c : _text_char16t_no_template)
    {
        wcout << static_cast<wchar_t>(c);
    }
    wcout << endl;
    char16_t _text_char16t_from_template {u'a'};
    wcout << L"Znak a: " << _text_char16t_from_template << endl;

    // tisk char32t
    // dva druhy implementace 4 byte
    basic_string<char32_t> _text_char32t_no_template{U"char32t text"};
    for (char32_t c : _text_char32t_no_template)
    {
        wcout << static_cast<wchar_t>(c);
    }
    wcout << endl;
    // 4 bajty
    char32_t _text_char32t_from_template {U'a'};
    wcout << L"Znak a: " << _text_char32t_from_template << endl;
}

double sqr(double x)
{
    return x*x;
}

double vzdalenost(bod06 A, bod06 B)
{
    return std::sqrt(sqr(A.x - B.x) + sqr(A.y + B.y));
}

double plocha_trojuhelnika(bod06 A, bod06 B, bod06 C)
{
    double a = vzdalenost(A, B);
    double b = vzdalenost(B, C);
    double c = vzdalenost(C, A);
    double s = (a + b + c) / 2;
    return sqrt(s*(s - a)*(s - b)*(s - c));
}

double obvod_trojuhelnika(bod06 A, bod06 B, bod06 C)
{
    double a = vzdalenost(A, B);
    double b = vzdalenost(B, C);
    double c = vzdalenost(C, A);
    return a+b+c;
}

int vypis_plochy_a_obvodu_trojuhelnika()
{
    cout << "Vypocet plochy trojuhelnika" << endl;

    bod06 A{ 0,1 }, B{ 2,3 }, C{ 4,5 };

    cout << "Plocha daného trojúhelníka je " << plocha_trojuhelnika(A, B, C) << endl;
    cout << "Obvod daného trojúhelníka je " << obvod_trojuhelnika(A, B, C) << endl;
    return 0;
}

void vypis_minimummaximum()
{
    cout << "Hello world!" << endl;

    {
        int k{0},i{15},j{66};
        k = maximum<>(i, j);
        cout << k << endl;
        double c{0},d{15},e{66};
        c = maximum<>(d, e);
        cout << c << endl;
    }
    {
        double k{0},i{15},j{66};
        k = minimum<double>(i, (int)j); // kdy sablona nevi, uvedeme typ v lomenych zavorkach
        cout << k << endl;


        double c{0},d{15},e{66};
        c = minimum<>(d, e);
        cout << c << endl;
    }
}
