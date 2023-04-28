# Лабораторная работа №1

###  UNIX знакомство: useradd, nano, chmod, docker, GIT, CI, CD

                                                                                       Выполнил студент:       Шаймуханов Тимур
                                                                                                         3 курс, z33434, 2023 г
---

## Цель

Познакомить студента с основами администрирования программных комплексов в ОС семейства UNIX, продемонстрировать особенности виртуализации и контейнеризации, продемонстрировать преимущества использования систем контроля версий (на примере GIT)

## Задача 1

#### 1.1 В папке /USR/LOCAL/ создать 2 директории: folder_max, folder_min

Команды:

```console
sudo mkdir folder_max
sudo mkdir folder_min
```

Результат:

```console
(base) timurverycool@DESKTOP-E880T0K:~$ ls -l
total 74832
...
drwxr-xr-x  2 root          root              4096 Apr 28 14:52 folder_max
drwxr-xr-x  2 root          root              4096 Apr 28 14:53 folder_min
...
```

#### 1.2 Создать 2-х пользователей: user_max_1, user_min_1

Команды:

```console
sudo adduser user_max_1
sudo adduser user_min_1
```

Результат: 

```console
(base) timurverycool@DESKTOP-E880T0K:~$ getent passwd {1000..60000}
timurverycool:x:1000:1000:,,,:/home/timurverycool:/bin/bash
user_max_1:x:1001:1003::/home/user_max_1:/bin/bash
user_min_1:x:1002:1004:,,,:/home/user_min_1:/bin/bash
```
#### 1.3 Создать 2-х группы пользователей: group_max, group_min

Команды:

```console
sudo addgroup group_max
sudo addgroup group_min
```

И соответственно добавим в них пользователей ```user_min_1``` и ```user_max_1```. Команды:

```console
sudo usermod -a -G group_max user_max_1
sudo usermod -a -G group_min user_min_1
```

Результат:

```console
(base) timurverycool@DESKTOP-E880T0K:~$ cat /etc/group
...
group_max:x:1001:user_max_1
group_min:x:1002:user_min_1
...
```

#### 1.4. Для пользователей из группы *_max дать полный доступ на директории *_max и *_min. Для пользователей группы *_min дать полный доступ только на директорию *_min

Команды:

```console
sudo chown :group_max folder_max
sudo chown :group_max folder_max
```

Результат:

```console
(base) timurverycool@DESKTOP-E880T0K:~$ ls -l
...
drwxr-xr-x  2 root          group_max         4096 Apr 28 14:52 folder_max
drwxr-xr-x  2 root          group_max         4096 Apr 28 14:53 folder_min
...
```

Команды:
sudo setfacl -m g:group_max:rwx folder_max
sudo setfacl -m g:group_max:rwx folder_min
sudo setfacl -m g:group_min:rwx folder_min

Результат:
Группа *_max обладает полным доступом к папкам *_max и *_min, т.к. является владельцем. Группа *_min обладает правом на чтение и исполнение к папке *_max и обладает
полным доступом к папке *_min

#### 1.5. Создать и исполнить (пользователем из той же категории) скрипт в директории folder_max, который пишет текущую дату/время в файл output.log в текущей директории

#### 1.6. Создать и исполнить (пользователем из той же категории) скрипт в директории folder_max, который пишет текущую дату/время в файл output.log в директории *_min

#### 1.7. Исполнить (пользователем *_min) скрипт в директории folder_max, который пишет текущую дату/время в файл output.log в директории *_min

#### 1.8. Создать и исполнить (пользователем из той же категории) скрипт в директории folder_min, который пишет текущую дату/время в файл output.log в директории *_max

#### 1.9. Вывести перечень прав доступа у папок *_min/ *_max, а также у всего содержимого внутри
