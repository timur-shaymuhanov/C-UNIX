#include <iostream> 
#include <cmath> 
#include <time.h> 
#include <stdlib.h>

using namespace std;

double func(const int &x, const int &n) {
    clock_t start = clock();
    for(int i = 0; i < n; ++i)
    {
        float res = pow(x, 2) - pow(x, 2) + x * 4 - x * 5 + x + x;
    }; 
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время работы программы: %.5e с\n", seconds);
    return seconds;
}

int main()
{
    string flag = "y";
    while (flag == "y")
    {
        float x = rand() % 2+100;

        int n; 
        std::cout << "Введите число итераций:" << endl;
        std::cin >> n;

        if(!std::cin.good())
        {
            std::cout << "Ошибка: число итераций должно быть целым" << endl;
            return 0;
        }
        double res =  func(x, n);
        std::cout << "Запустить еще раз?: (y/n)" << endl;
        std::cin >> flag;
    }
}