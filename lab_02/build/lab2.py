import numpy as np
import timeit as tm

x = np.random.random()
print('Значение переменной: ', x)

def f(x):
    return x**2 - x**2 + x*4 - x*5 + x + x

def time_measuring():
    try:
        print("Введите число итераций:", end=' ')
        n = int(input())
        print()
    except ValueError:
        print("Число итераций должно быть целым")
        return None
    time = tm.timeit(stmt = "f(x)", globals = globals(), number = n)
    return (n, time)

while True:
    n, time_res = time_measuring()
    if time_res == None:
        break
    else:
        print("Время выполнения", n, "итераций равно", time_res)
        print()
        flag = input("Запустить еще раз? (y/n): ")
        if flag == "n":
            break