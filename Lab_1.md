# Лабораторная работа №1

###  UNIX знакомство: useradd, nano, chmod, docker, GIT, CI, CD

                                                                                       Выполнил студент:       Шаймуханов Тимур
                                                                                                         3 курс, z33434, 2023 г
---

## Цель

Познакомить студента с основами администрирования программных комплексов в ОС семейства UNIX, продемонстрировать особенности виртуализации и контейнеризации, продемонстрировать преимущества использования систем контроля версий (на примере GIT)

## Задача 1

#### 1.1 В папке /USR/LOCAL/ создать 2 директории: folder_max, folder_min

Сначала идем в нужную папку:

```console
cd /usr/local/
```

Там создаем папки

Команды:

```console
sudo mkdir folder_max
sudo mkdir folder_min
```

Результат:

```console
(base) timurverycool@DESKTOP-E880T0K:/usr/local/$ ls -l
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
(base) timurverycool@DESKTOP-E880T0K:/usr/local/$ ls -l
...
drwxr-xr-x  2 root          group_max         4096 Apr 28 14:52 folder_max
drwxr-xr-x  2 root          group_max         4096 Apr 28 14:53 folder_min
...
```

Команды:

```console
sudo setfacl -m g:group_max:rwx folder_max
sudo setfacl -m g:group_max:rwx folder_min
sudo setfacl -m g:group_min:rwx folder_min
```

Результат:

Группа *_max обладает полным доступом к папкам *_max и *_min, т.к. является владельцем. Группа *_min обладает правом на чтение и исполнение к папке *_max и обладает
полным доступом к папке *_min

#### 1.5. Создать и исполнить (пользователем из той же категории) скрипт в директории folder_max, который пишет текущую дату/время в файл output.log в текущей директории

Для начала переключаемся на нужного пользователя

```console
timurverycool@DESKTOP-E880T0K:~$ su - user_max_1
Password:
user_max_1@DESKTOP-E880T0K:~$
```

Идем в нужную папку

```console
user_max_1@DESKTOP-E880T0K:~$ cd /usr/local/folder_max/
```

Там создаем файл ```script_max``` командой:

```console
touch script_max
```
Теперь открываем файл:

```console
nano script_max
```

Прописываем сам скрипт

```console
#!/bin/bash
date | tee output.log
```
Запускаем файл командами:

```console
chmod g=rwx script_max
./script_max
```

Результаты:

В папке ```folder_max``` появились файлы ```script_max``` и ```output.log```:

```console
user_max_1@DESKTOP-E880T0K:/usr/local/folder_max$ ls -l
total 8
-rw-rw-r-- 1 user_max_1 user_max_1 29 Apr 28 20:49 output.log
-rwxrwxr-x 1 user_max_1 user_max_1 35 Apr 28 20:35 script_max
```

С помощью команды: ```nano output.log``` открываем ```output.log``` и видим там таймкод:

```console
Fri Apr 28 20:49:56 MSK 2023
```

#### 1.6. Создать и исполнить (пользователем из той же категории) скрипт в директории folder_max, который пишет текущую дату/время в файл output.log в директории *_min

Там создаем файл ```script_min``` командой:

```console
touch script_max
```
Теперь открываем файл:

```console
nano script_min
```

Прописываем сам скрипт

```console
#!/bin/bash
date | tee /usr/local/folder_min/output.log
```

Запускаем файл командами:

```console
chmod a=rwx script_min
./script_max
```

Результаты:

В папке ```folder_max``` появились файл ```script_min```:

```console
user_max_1@DESKTOP-E880T0K:/usr/local/folder_max$ ls -l
total 8
-rw-rw-r-- 1 user_max_1 user_max_1 29 Apr 28 20:49 output.log
-rwxrwxr-x 1 user_max_1 user_max_1 35 Apr 28 20:35 script_max
-rwxrwxrwx 1 user_max_1 user_max_1 56 Apr 28 21:11 script_min
```

Идем в ```/usr/local/folder_min``` и видим, что там появился файл ```output.log```:

```console
user_max_1@DESKTOP-E880T0K:/usr/local/folder_min$ ls -l
total 4
-rw-rw-r-- 1 user_max_1 user_max_1 29 Apr 28 21:11 output.log
```

Затем с помощью команды ```nano output.log``` открываем его и видим там таймкод:

```console
Fri Apr 28 21:11:43 MSK 2023
```

#### 1.7. Исполнить (пользователем *_min) скрипт в директории folder_max, который пишет текущую дату/время в файл output.log в директории *_min

Переключаем пользователя

```console
su - user_min_1
```

Затем идем в папку ```folder_max``` с помощью команды:

```console
cd /usr/local/folder_max
```

И пытаемся запустить файл ```script_min``` командой ```./script_min``` 

Результаты:

Получаем сообщение 

```console
tee: /usr/local/folder_min/output.log: Permission denied
Fri Apr 28 21:28:04 MSK 2023
```

Для проверки зайдем в ```/usr/local/folder_min/output.log``` с помощью команды ```nano``` (перейдя в нужную папку через ```cd```). Видим только старый таймкод 

```console
Fri Apr 28 21:11:43 MSK 2023
```

и сообщение внизу ```[ File 'output.log' is unwritable ]```


#### 1.8. Создать и исполнить (пользователем из той же категории) скрипт в директории folder_min, который пишет текущую дату/время в файл output.log в директории *_max

Там создаем файл ```script_min``` командой:

```console
touch script_min
```
Теперь открываем файл:

```console
nano script_min
```

Прописываем сам скрипт

```console
#!/bin/bash
date | tee /usr/local/folder_max/output.log
```

Запускаем файл командами:

```console
chmod a=rwx script_min
./script_min
```

Результаты:

Получаем сообщение 

```console
user_min_1@DESKTOP-E880T0K:/usr/local/folder_min$ ./script_min
tee: /usr/local/folder_max/output.log: Permission denied
Fri Apr 28 21:40:55 MSK 2023
```

так как у пользователя ```user_min``` нет прав на папку ```folder_max```. Удостоверимся, проверив файл ```/usr/local/folder_max/output.log``` с помощью команды ```nano output.log```. Видим только старый таймкод:

```console
Fri Apr 28 20:49:56 MSK 2023
```

и сообщение внизу ```[ File 'output.log' is unwritable ]```

#### 1.9. Вывести перечень прав доступа у папок *_min/ *_max, а также у всего содержимого внутри

Для перечня прав доступа используем команду ```ls -l``` в соответствующей директории

Результаты:

В папке ```/usr/local/folder_max```:

```console
user_min_1@DESKTOP-E880T0K:/usr/local/folder_max$ ls -l
total 12
-rw-rw-r-- 1 user_max_1 user_max_1 29 Apr 28 20:49 output.log
-rwxrwxr-x 1 user_max_1 user_max_1 35 Apr 28 20:35 script_max
-rwxrwxrwx 1 user_max_1 user_max_1 56 Apr 28 21:11 script_min
```

В папке ```/usr/local/folder_min```:

```console
user_min_1@DESKTOP-E880T0K:/usr/local/folder_min$ ls -l
total 8
-rw-rw-r-- 1 user_max_1 user_max_1 29 Apr 28 21:11 output.log
-rwxrwxr-x 1 user_min_1 user_min_1 56 Apr 28 21:34 script_min
```

В папке ```/usr/local/```:

```console
user_min_1@DESKTOP-E880T0K:/usr/local$ ls -l
...
drwxrwxr-x+ 2 root group_max 4096 Apr 28 21:11 folder_max
drwxrwxr-x+ 2 root group_max 4096 Apr 28 21:34 folder_min
...
```



## Задача 2

2.1. Создать скрипт, который пишет текущую дату/время в файл output.log в
текущей директории

Создадим файл скрипт в ```/usr/local``` с помощью ```touch script_2```. Открываем его командой ```nano script_2``` и пишем:

```console
#!/bin/bash
date >> output.log
```

В результате в ```/usr/local``` появляются файлы ```script_2``` и ```output.log```, в последнем записана текущая дата.

2.2. Собрать образ со скриптами выше и с пакетом nano (docker build)



2.3. Запустить образ (docker run)

2.4. Выполнить скрипт, который подложили при сборке образа

2.5. Вывести список пользователей в собранном образе
