# Лабораторная работа №3

### C++ CLI / FUNCTION / LOOP / RECURSION

                                                                                  Выполнил студент:       Шаймуханов Тимур
                                                                                                    3 курс, z33434, 2023 г
---

## Цель

Познакомить студента с основными алгоритмическими конструкциями, которые будут
использоваться для создания CLI программы. Далее продемонстрировать
эффективность использования механизма рекурсии.
С++ алгоритмы: CLI Калькулятор вещественных чисел +, -, ^, . Реализация с
использованием только функций, условий, циклов, + и -. Вид команд в консоли: calc
plus / minus / power; Ханойская башня, результат корректной последовательности

## Задача 1 [С++ CLI CALC] Создать программу CALC с интерфейсом CLI

Создать программу под названием CALC, которая будет принимать на вход 3
аргумента (2 операнда и 1 оператор). Оператор может быть: +, -, ^. Реализация
операторов только с использованием функций, условий, циклов, +, - и *.

### Решение
```C++
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
```
### Результат

```console
C:\Users\Тимур>C:\Users\Тимур\C-UNIX\lab_03\build\lab3_calc.exe 5.2 plus 7.3
5.2+7.3=12.5

C:\Users\Тимур>C:\Users\Тимур\C-UNIX\lab_03\build\lab3_calc.exe 5.2 minus 7.3
5.2-7.3=-2.1

C:\Users\Тимур>C:\Users\Тимур\C-UNIX\lab_03\build\lab3_calc.exe 5.2 power 7.3
b must be integer

C:\Users\Тимур>C:\Users\Тимур\C-UNIX\lab_03\build\lab3_calc.exe 5.2 abrakadabra 7.3
Error: Incorrect operator. Choose one of 'plus', 'minus', 'power'.
```

## Задача 2 [C++ RECURSION] Решить задачу ханойской башни с использованием рекурсии

Описание: Ханойская башня является одной из популярных головоломок XIX века.
Даны три стержня, на один из которых нанизаны восемь колец, причём кольца
отличаются размером и лежат меньшее на большем. Задача состоит в том, чтобы
перенести пирамиду из восьми колец за наименьшее число ходов на другой
стержень. За один раз разрешается переносить только одно кольцо, причём нельзя
класть большее кольцо на меньшее.

Результат обнаруженной последовательности шагов записать в виде двусвязного
списка. В конце программы сделать вывод этого списка на экран. Освободить
память списка перед завершением программы.

### Решение
```C++
#include <iostream>
#include <string>
#include <list>
#include <cmath>

using namespace std;

void hanoi(int n, char source, char destination, char auxiliary, list<string> &actions) {
    if (n == 1) {
        actions.push_back("disk 1 from " + string(1, source) + " to " + string(1, destination));
        return;
    }

    hanoi(n - 1, source, auxiliary, destination, actions);
    actions.push_back("disk " + to_string(n) + " from " + string(1, source) + " to " + string(1, destination));
    hanoi(n - 1, auxiliary, destination, source, actions);

}

int main() {
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;
    list<string> actions;
    hanoi(n, 'A', 'B', 'C', actions);

    for (string step : actions) {
        cout << step << endl;
    }

    int num = pow(2, n) - 1;
    cout << "Algorithm has done " << actions.size() << " iterations | Optimal number of iterations is " << num;  
    actions.clear();
}
```


### Результат
```console
Enter the number of disks: 3
disk 1 from A to B
disk 2 from A to C
disk 1 from B to C
disk 3 from A to B
disk 1 from C to A
disk 2 from C to B
disk 1 from A to B
Algorithm has done 7 iterations | Optimal number of iterations is 7
```

## Вывод

Реализован простейший калькулятор и рекурсивный алгоритм решения задачи с Ханойскими Башнями. Ранее не имея опыта программирования на C++, познакомился со строками, списками и реализацией рекурсии на этом языке, а также с использованием скриптов с интерфейсом CLI.
