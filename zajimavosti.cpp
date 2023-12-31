#include "zajimavosti.h"
// #include <stdio.h>
#include <iostream>

using namespace std;


Tabs::Tabs()
{

}
Tabs::~Tabs()
{
}


void aput( char* c, char bg_col, char fg_col )
{
    int bg, fg;
    if( bg_col > 7 ) bg = 100 + bg_col-8;
    else             bg =  40 + bg_col;
    if( fg_col > 7 ) fg =  90 + fg_col-8;
    else             fg =  30 + fg_col;
    printf( "\033[%i;%im%s\033[0;0m", fg, bg, c );
}
void print_colors()
{
    int bg, fg;
    for( fg = 0; fg <  8; fg += 1 ) aput("    ", fg, 0);
    cout << endl;
    for( fg = 8; fg < 16; fg += 1 ) aput("    ", fg, 0);
    cout << endl;
    cout << endl;
    for( bg = 0; bg < 16; bg += 1 )
    {
        for( fg = 0; fg < 16; fg += 1 )
        {
            aput( "10", bg, fg );
        }
        cout << endl;
    }
}

