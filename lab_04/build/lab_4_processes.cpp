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
        //back to parent process
        int res1[n];
        int res2[n];
        int f3[n];
        read(pf1[0], res1, sizeof(res1));
        read(pf2[0], res2, sizeof(res2));
        for (int i = 0; i <= n; i++) {
            f3[i] = func3(res1[i], res2[i]);
        }

        //end of the main evaluation
        kill(pid_f1, 0);
        kill(pid_f2, 0);
    
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
    cout << "Execution time of " << n << " multi-process calculations: " << t/n_exps <<" sec \n";

    n = 100000;
    for (int i = 0; i<n_exps; i++){
        t += time(x, n);
    }
    cout << "Execution time of " << n << " multi-process calculations: " << t/n_exps <<" sec \n";
}