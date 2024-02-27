#include <iostream>
#include <cstdlib>
using namespace std;
int main (int argc,char* argv[])
{
    int count = 0;
    for (int i = 0; i < argc ; i++)
    {
        switch(argv[i][0])
        {
            case '1' : 
            case '3' : 
            case '5' : 
            case '7' : 
            case '9' : 
            count++;
        }
    }
    cout << count;
    //return 0;
}