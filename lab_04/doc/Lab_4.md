# Лабораторная работа №4

### C++ PROCESSES / THREADS

                                                                                  Выполнил студент:       Шаймуханов Тимур
                                                                                                    3 курс, z33434, 2023 г
---

## Цель

Познакомить студента с принципами параллельных вычислений. Составить несколько
программ в простейшими вычислительными действиями, чтобы освоить принципы
параллельных вычислений (когда одни алгоритмы зависят / не зависят от других).

## Задача 1 [С++ SEQUENCE] Последовательные вычисления

Требуется последовательно выполнить вычисления по формуле 1, вычисления по
формуле 2, после чего выполнить вычисления по формуле 3, которые выглядят
следующим образом: результат вычислений 1 + результат вычислений 2 –
результат вычислений 1
Выполнить последовательно на 10 000 итераций и 100 000 итераций

Формула 1: f(x) = x ^2- x ^2+ x *4 - x *5 + x + x

Формула 2: f(x) = x + x

Вывести длительность выполнения всех 10 000 итераций и 100 000 итераций в сек.

### Решение
```C++
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
```
### Результат

```console
Argument: 2.39
Execution time of 10000 sequential calculations: 0.00044 sec
Execution time of 100000 sequential calculations: 0.00481 sec 
```

## Задача 2 [C++ THREADS] Параллельные вычисления через потоки

Требуется параллельно (насколько возможно с помощью потоков) выполнить
вычисления по формуле 1, вычисления по формуле 2, после чего выполнить
вычисления по формуле 3, которые выглядят следующим образом: результат
вычислений 1 + результат вычислений 2 – результат вычислений 1
Выполнить последовательно на 10 000 итераций и 100 000 итераций

Формула 1: f(x) = x ^2- x ^2+ x *4- x *5+ x + x

Формула 2: f(x) = x + x

Вывести длительность выполнения всех 10 000 итераций и 100 000 итераций в сек.
в разбивке по шагам вычислений 1, 2 и 3

### Решение
```C++
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
```


### Результат
```console
Argument: 2.39
Execution time of 10000 multithreaded calculations: 0.00369 sec
Execution time of 100000 multithreaded calculations: 0.01763 sec 
```

## Задача 3 [C++ PROCESS] Параллельные вычисления через процессы

Требуется параллельно (насколько возможно с помощью процессов) выполнить
вычисления по формуле 1, вычисления по формуле 2, после чего выполнить
вычисления по формуле 3, которые выглядят следующим образом: результат
вычислений 1 + результат вычислений 2 – результат вычислений 1
Выполнить последовательно на 10 000 итераций и 100 000 итераций

Формула 1: f(x) = x ^2- x ^2+ x *4- x *5+ x + x

Формула 2: f(x) = x + x

Вывести длительность выполнения всех 10 000 итераций и 100 000 итераций в сек.
в разбивке по шагам вычислений 1, 2 и 3

### Решение
```C++

```


### Результат
```console

```
## Вывод
Реализован простейший калькулятор и рекурсивный алгоритм решения задачи с Ханойскими Башнями. Ранее не имея опыта программирования на C++, познакомился со строками, списками и реализацией рекурсии на этом языке, а также с использованием скриптов с интерфейсом CLI.
