#ifndef CESTINA_H_INCLUDED
#define CESTINA_H_INCLUDED

#include <windows.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

// using std::transform;

CONSOLE_FONT_INFOEX cf_puvodni;
BOOL nastaveno = false;
UINT kodova_stranka;

void uloz_soucasne_nastaveni_konzoly()
{
    cf_puvodni.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    nastaveno = GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cf_puvodni);
    kodova_stranka = GetConsoleOutputCP();
}

void nastav_konzolu_pro_cp1250()
{
    uloz_soucasne_nastaveni_konzoly();
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 18;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Cascadia Mono");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);
    system("CHCP 1250 > NUL");
}

void nastav_rastr()
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 18;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Cascadia Mono");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);
    system("CHCP 852 > NUL");
}

void nastav_rastr_cascadia()
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 18;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Cascadia Mono");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);
    system("CHCP 65001 > NUL");
}

void obnov_puvodni_nastaveni_konzoly()
{
    if (nastaveno)
    {
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cf_puvodni);
        if (kodova_stranka == 852) system("CHCP 852 > NUL");
    }
    else
    {
        nastav_rastr();
    }
}

static const unsigned char tabulka[]
{
    129, 130, 131, 132, 133, 134, 135, 136, 137, 230, 139, 140,
    155, 166, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152,
    153, 231, 155, 156, 156, 167, 159, 160, 161, 162, 163, 164,
    165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176,
    177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 149,
    189, 150, 191, 232, 181, 194, 195, 142, 145, 198, 199, 172,
    144, 202, 203, 183, 214, 206, 210, 208, 209, 213, 224, 226,
    213, 214, 215, 252, 222, 233, 219, 220, 237, 222, 223, 234,
    160, 226, 227, 132, 146, 230, 231, 159, 130, 234, 235, 216,
    161, 238, 212, 240, 241, 229, 162, 147, 245, 246, 247, 253,
    133, 163, 251, 252, 236, 254, 255
};

char znak_Cp1250_do_Cp852(unsigned char znak)
{
    if (znak < 128)
    {
        return znak;
    }
    else
    {
        return tabulka[znak - 129];
    }
}

//Tato funkce pøeloží bez problémù bìžný èeský nebo slovenský text, nebo všechna písmena sdiakritickými
//znaménky jsou souèástí obou kódových stránek; nìkteré zvláštní znaky, jako je © nebo ®, však pøeloží
//nesprávnì, nebo nejsou souèástí kódové stránky 852. Naše funkce tam pro nì vrátí jakési zástupné znaky,
//které by nesplnily svùj úèel, aproto jsme v nápovìdì místo znaku autorských práv použili zástupné znaky
//(C).
string retezec_Cp1250_na_string_Cp852(const char *text_napovedy_1250)
{
    string vysledek;
    for (const char *p = text_napovedy_1250; *p; p++)
    {
        vysledek += znak_Cp1250_do_Cp852(*p);
    }
    return vysledek;
}

string string_Cp1250_na_string_Cp852( string text_1250 )
{
    string vysledek(text_1250.size(), ' ');
    transform(text_1250.begin(), text_1250.end(), // <algoritmh>
              vysledek.begin(), znak_Cp1250_do_Cp852);
    return vysledek;
}


double logaritmus(double x)
{
    double y;
    y = log(x);

    switch (errno) {
    case 0:
        perror(NULL);
        printf("log(%f) = %f.\n", x, y);
        return y;
    default:
        perror("Hlaseni");
        return 0;
    }
}

void test_vystup() {
    printf("Cislo 10000/3 = %f\n", 10000.0/3);
    (void) logaritmus(-5);
    (void) logaritmus(0);
}

void printf_locale_vystup() {
    printf("* Aktualne nastavene locale LC_ALL: %s\n", setlocale(LC_ALL, NULL));
    test_vystup();

    printf("* Locale LC_ALL nastaveno na: %s\n", setlocale(LC_ALL,""));
    test_vystup();

    printf("* Locale LC_NUMERIC nastaveno na %s\n", setlocale(LC_NUMERIC,"C"));
    test_vystup();
}
#endif // CESTINA_H_INCLUDED
