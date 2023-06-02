#include <iostream>
#include <string>
#include <cmath>

using namespace std;

double pow(double a, double b)
{
    double res = 1;
    for (int i = 0; i < b; i++)
    {
        res *= a;
    }
    return res;
}

int main(int argc, char* argv[])
{
    double a = stod(argv[1]);
    double b = stod(argv[3]);
    string oper = argv[2];
    
    if (oper == "plus")
    {
        cout << a << '+' << b << '=' << a + b << "\n";
    }
    else if (oper == "minus")
    {
        
        cout << a << '-' << b << '=' << a - b << "\n";
    }
    else if (oper == "power")
    {
        if (floor(b) == b)
        {
            cout << a << '^' << b << '=' << pow(a, b) << "\n";
        }
        else
        {
            cout << "b must be integer \n";
        }
    }
    else
    {    
        cout << "Error: Incorrect operator. Choose one of 'plus', 'minus', 'power'. \n";
    }
}