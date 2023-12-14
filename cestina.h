#ifndef CESTINA_H_INCLUDED
#define CESTINA_H_INCLUDED

#include <windows.h>
#include <string.h>
#include <stdlib.h>

void zarid_cestinu()
{
    CONSOLE_FONT_INFOEX cfi;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    system("CHCP 1250 > NUL");

}

void zarid_cestinu_1250()
{
    CONSOLE_FONT_INFOEX cfi;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    system("CHCP 1250 > NUL");

}

#endif // CESTINA_H_INCLUDED
