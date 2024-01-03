#include <Windows.h>
#include "20_priklad_wide.h"
#include <fcntl.h>
//
//
// tento soubor je UTF-8
//

using namespace std;

// toto je použitelné pouze pro kódování zdrojového souboru v UTF-8
wstring wvolba::text_napovedy_wide = LR"(
utf8 SORT - program pro seřazení řádek daného souboru. Použití:
sort volba < vstupní-soubor > výstupní-soubor
Možné volby:
-n nebo /n řazení podle čísel na počátcích řádek
-l nebo /l lexikografické řazení
-a nebo /a abecední řazení
)";

// azbuka v tomto řetězci způsobí automatický převod
// zdrojového souboru v Code::Blocks na UTF-8
// a rozbije tím české kódování, takže pak bude nutné použít
// jinou metodu pro české znaky, než metody pro ANSI kódování
wstring wvolba::text_napovedy_uk = LR"(
Включаем буферизацию, чтобы VS не прерывал последовательности байтов
)";

[[noreturn]]
void wvolba::wnapoveda()
{
    // přidáno cestou - není z učebnice
    // SetConsoleOutputCP(CP_UTF8); // nasatví na výstupu utf8

    // VARIANTA 1
    setlocale(LC_ALL, "Czech");
    SetConsoleOutputCP(1250);
    wcerr << text_napovedy_wide;
    wcerr << text_napovedy_wide.length() << endl;

    // VARIANTA 2
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(866);

    wcerr << text_napovedy_uk;
    // strlen
    wcerr << text_napovedy_uk.length() << endl;
    // strlen přes metodu string c_str()
    wcerr << wcslen(text_napovedy_uk.c_str()) << endl;

    // zde pozor, nefunguje dle očekávání
    cout << "На берегу пустынных волн: strlen= " << strlen("На берегу пустынных волн") << endl; // return 45
    cout << "На берегу пустынных волн: wcslen= " << wcslen(L"На берегу пустынных волн") << endl; // return 25

    wcout << L"На берегу пустынных волн: strlen= " << strlen("На берегу пустынных волн") << endl; // return 45
    wcout << L"На берегу пустынных волн: wcslen= " << wcslen(L"На берегу пустынных волн") << endl; // return 25

    exit(1);
}

map<wstring, wvolba::wu_komparator> wvolba::wtabulka_voleb
{
    {L"-l", wlexikograficky},
    {L"-n", wpodle_cisel},
    {L"-a", walfabeticky}
};

wvolba::wvolba(int argc, wchar_t *argv[])
{
    try
    {
        if (argc != 2)
        {
            throw runtime_error("!");
        }
        if (argv[1][0] == '/')
        {
            argv[1][0] = '-';
        }
        wkomparator = wtabulka_voleb.at(argv[1]);
    }
    catch (exception &e)
    {
        wnapoveda();
    }
}
wvolba::wu_komparator wvolba::wzvoleno()
{
    return wkomparator;
}

void wtridic::wzpracuj(wvolba::wu_komparator wkomparator)
{
    wnacti();
    wserad(wkomparator);
    wvypis();
}

void wtridic::wnacti()
{
    while (getline(wcin, wradka))
    {
        wsoubor.push_back(wradka);
    }
}

void wtridic::wserad(wvolba::wu_komparator wkomparator)
{
    sort(wsoubor.begin(), wsoubor.end(), wkomparator);
}

void wtridic::wvypis()
{
    for (auto lajna : wsoubor)
    {
        wcout << lajna << endl;
    }
}

