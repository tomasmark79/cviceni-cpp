#ifndef ZAJIMAVOSTI_H_INCLUDED
#define ZAJIMAVOSTI_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;




// auto print_colors() -> void;

class Tabs
{
    // v C++ staticka promìnná (složka), tøídní složka
    // Deklarace je pouze informativní u statické složky
    // Definice musí být implementovaná mimo tìlo tøídy!
public:
    static int nTabCount;

public:
    Tabs();
    ~Tabs();

    static void coutUnderScore(int n)
    {
        cout << getTabChars();
        for (int i{0}; i<n; i++)
            cout << "_";
    }

    static void reset(void)
    {
        nTabCount = 0;
    }

    static void setTabCount(int n)
    {
        nTabCount = n;
    }

    static void addTab(void)
    {
        nTabCount++;
    }

    static void decTab(void)
    {
        nTabCount--;
        if (nTabCount < 0) nTabCount = 0;
    }

    static int getTabCount(void)
    {
        return nTabCount;
    }

    static string getTabChars(void)
    {
        string temp = "";
        for (int i{0}; i<nTabCount; i++)
            temp += "\t";
            // temp += " ";
        return temp;
    }

    static void printFunctionHeader(string str)
    {
        coutUnderScore(str.length());
        cout << endl << getTabChars() << str << endl;
        coutUnderScore(str.length());
        cout << endl;
    }
    static void printLine(string str_line)
    {


        cout << getTabChars() << str_line;
        cout << endl;
    }
};

#endif // ZAJIMAVOSTI_H_INCLUDED
