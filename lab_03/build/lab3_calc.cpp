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
    //cout << "Input format: a + b | a - b | a ^ b; For calculating a^b b must be integer \n";
    double a = stod(argv[1]);
    double b = stod(argv[3]);
    string oper = argv[2];
    
    if (oper == "plus" or oper == "+")
    {
        cout << a << '+' << b << '=' << a + b << "\n";
    }
    else if (oper == "minus" or oper == "-")
    {
        
        cout << a << '-' << b << '=' << a - b << "\n";
    }
    else if (oper == "power" or oper == "^")
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
        cout << "Error: Incorrect operator";
    }
}