#include <iostream>
#include <cstdlib>
#include <windows.h>
using namespace std;
int main ()
{
    int x = system("quiz19.exe 12 343 54 2 54");
    cout << x;
    return 0;
}