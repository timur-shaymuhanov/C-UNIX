#include <iostream>
#include <cmath>
#include <time.h>

using namespace std;

double func1(const double &x){
    double res = x*x - x*x + pow(x, 4) - pow(x,5) + x + x;
    return res;
}

double func2(const double &x){
    double res = x + x;
    return res;
}

double func3(const double &func1, const double &func2){
    double res = func1 + func2 - func1;
    return res;
}

double time(const double &x, const int &n){
    clock_t start = clock();
    for (int i = 0; i < n; i++){
        double f1 = func1(x);
        double f2 = func2(x);
        double f3 = func3(f1, f2);
    }
    clock_t end = clock();
    double sec = (double)(end - start) / CLOCKS_PER_SEC;
    return sec;
}

int main() {

    int n_exps = 100;
    double x = 2.39;
    int n = 10000;
    double t;
    
    for (int i = 0; i<n_exps; i++){
        t += time(x, n);
    }
    


    cout << "Argument: " << x << "\n";
    cout << "Execution time of " << n << " sequential calculations: " << t/n_exps <<" sec \n";

    n = 100000;
    for (int i = 0; i<n_exps; i++){
        t += time(x, n);
    }
    cout << "Execution time of " << n << " sequential calculations: " << t/n_exps <<" sec \n";
}