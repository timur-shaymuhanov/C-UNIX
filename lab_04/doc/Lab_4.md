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

    double x = 2.39;
    int n = 10000;
    double t = time(x, n);

    cout << "Argument: " << x << "\n";
    cout << "Execution time of " << n << " sequential calculations: " << t <<" sec \n";

    n = 100000;
    t = time(x, n);
    cout << "Execution time of " << n << " sequential calculations: " << t <<" sec \n";
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

    double x = 2.39;
    int n = 10000;
    double t = time(x, n);

    cout << "Argument: " << x << "\n";
    cout << "Execution time of " << n << " multitreaded calculations: " << t <<" sec \n";

    n = 100000;
    t = time(x, n);
    cout << "Execution time of " << n << " multitreaded calculations: " << t <<" sec \n";
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
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <sys/wait.h>
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
    float f1[n];
    float f2[n];
    float f3[n];
    clock_t start = clock();

    int pf1[2], pf2[2];
        pipe(pf2);
        pipe(pf1);
        pid_t pid_f1 = fork();
        if (pid_f1 == 0) {
            int f1[n];
            for (int i = 0; i <= n; i++) {
                f1[i] = func1(x);
                write(pf1[1], f1, sizeof(n));
            }
            return 0;
        } else if (pid_f1 == -1) {
            cerr << "Multiprocessing failed.";
            return 1;
        }

        pid_t pid_f2 = fork();
        if (pid_f2 == 0) {
            int f2[n];
            for (int i = 0; i <= n; i++) {
                f2[i] = func2(x);
                write(pf2[1], f2, sizeof(n));
            }
            return 0;
        } else if (pid_f2 == -1) {
            cerr << "Multiprocessing failed.";
            return 1;
        }

        int res1[n];
        int res2[n];
        read(pf1[0], res1, sizeof(res1));
        read(pf2[0], res2, sizeof(res2));
        for (int i = 0; i <= n; i++) {
            f3[i] = func3(res1[i], res2[i]);
        }

        kill(pid_f1, 0);
        kill(pid_f2, 0);
    
    clock_t end = clock();
    double sec = (double)(end - start) / CLOCKS_PER_SEC;
    return sec;
}

int main() {

    double x = 2.39;
    int n = 10000;
    double t = time(x, n);

    cout << "Argument: " << x << "\n";
    cout << "Execution time of " << n << " multi-process calculations: " << t <<" sec \n";

    n = 100000;
    t = time(x, n);
    cout << "Execution time of " << n << " multi-process calculations: " << t <<" sec \n";
}
```


### Результат
```console
Argument: 2.39
Execution time of 10000 multi-process calculations: 0.000433 sec
Execution time of 100000 multi-process calculations: 0.001614 sec
```
## Вывод
Реализовано распарралеливание вычислений с помощью создания дополнительных потоков и процессов, что является для меня новым опытом. Эксперименты показали, что на объемах ~10<sup>4</sup>-10<sup>5</sup> вычислений (в случае С++) многопоточные вычисления производятся медленее последовательных (вероятно, временные затраты на создание потоков не окупаются параллельным ускорением), однако реализация на нескольких процессах демонстрирует преимущество перед последовательным вариантом уже на объеме ~10<sup>5</sup>, а на объеме ~10<sup>4</sup> показывает примерно тот же результат.
