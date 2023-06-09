#include <iostream>
#include <cmath>
#include <time.h>
#include <thread>
#include <mutex>

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
    float f1[n];
    float f2[n];
    float f3[n];
    mutex m;
    clock_t start = clock();

    thread t1([&f1, &x, &n, &m]()
    {
    for (int i = 0; i < n; i++){
        m.lock();
        f1[i] = func1(x);
        m.unlock();
    }
    });

    thread t2([&f2, &x, &n, &m]()
    {
    for (int i = 0; i < n; i++){
        m.lock();
        f2[i] = func2(x);
        m.unlock();
    }
    });

    for (int i = 0; i<n; i++){
        f3[i] = f1[i] + f2[i] - f1[i];
    }

    t1.join();
    t2.join();
    
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
    cout << "Execution time of " << n << " multithreaded calculations: " << t/n_exps <<" sec \n";

    n = 100000;
    for (int i = 0; i<n_exps; i++){
        t += time(x, n);
    }
    cout << "Execution time of " << n << " multithreaded calculations: " << t/n_exps <<" sec \n";
}