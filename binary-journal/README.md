# Binary Journal

My program writes 10 entries to a binary file and reads them back. Each entry has 4 fields: id, name, age, and score.

The program generates random data for 10 people, saves it to journal.bin, then reads it back and displays it in a nice table. It also shows the file size in bytes.

# Бинарный Журнал

Программа записывает 10 записей в бинарный файл и читает их обратно. Каждая запись содержит 4 поля: id, name, age, score.

Программа генерирует случайные данные для 10 людей, сохраняет их в journal.bin, затем читает обратно и выводит в виде таблицы. Также показывает размер файла в байтах.

## How to Compile

```bash
g++ -static z1.cpp -o z1.exe
```

## How to Run

```bash
.\z1.exe
```

## Как компилировать

```bash
g++ -static z1.cpp -o z1.exe
```

## Как запустить

```bash
.\z1.exe
```

## Output

The program creates 10 random people with names, ages, and scores. It saves them to a binary file, then reads them back and displays in a table. File size is 640 bytes.

## Вывод

Программа создает 10 случайных людей с именами, возрастом и оценками. Сохраняет их в бинарный файл, затем читает обратно и выводит в таблицу. Размер файла 640 байт.

## Files

- z1.cpp - the code

## Файлы

- z1.cpp - код программы
