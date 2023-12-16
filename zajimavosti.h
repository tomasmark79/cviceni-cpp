#ifndef ZAJIMAVOSTI_H_INCLUDED
#define ZAJIMAVOSTI_H_INCLUDED

#include <cstring>
using namespace std;

auto print_colors() -> void;

class Tabs
{
    // v C++ staticka prom�nn� (slo�ka), t��dn� slo�ka
    // Deklarace je pouze informativn� u statick� slo�ky
    // Definice mus� b�t implementovan� mimo t�lo t��dy!
    static int nTabCount;

public:
    Tabs();
    ~Tabs();

    static auto coutUnderScore(int n) -> void
    {
        cout << getTabChars();
        for (int i{0}; i<n; i++)
            cout << "_";
    }

    static auto reset(void) -> void
    {
        nTabCount = 0;
    }

    static auto setTabCount(int n) -> void
    {
        nTabCount = n;
    }

    static auto addTab(void) -> void
    {
        nTabCount++;
    }

    static auto decTab(void) -> void
    {
        nTabCount--;
        if (nTabCount < 0) nTabCount = 0;
    }

    static auto getTabCount(void) -> int
    {
        return nTabCount;
    }

    static auto getTabChars(void) -> string
    {
        string temp = "";
        for (int i{0}; i<nTabCount; i++)
            temp += "\t";
            // temp += " ";
        return temp;
    };

    static auto printFunctionHeader(string str) -> void
    {
        coutUnderScore(str.length());
        cout << endl << getTabChars() << str << endl;
        coutUnderScore(str.length());
        cout << endl;
    }
    static auto printLine(string str_line) -> void
    {
        cout << getTabChars() << str_line;
        cout << endl;
    }

};

#endif // ZAJIMAVOSTI_H_INCLUDED
