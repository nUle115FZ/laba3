#include <stdio.h>     // Библиотека для ввода-вывода
#include <stdlib.h>    // Для работы с памятью, стандартных функций и макросов
#include "stack.h"     // Заголовочный файл с реализацией стека
#include "io.h"        // Заголовочный файл для работы с вводом-выводом
#include "arguments.h" // Заголовочный файл для обработки аргументов командной строки
#include "sorting.h"   // Заголовочный файл с алгоритмом сортировки
#include <string.h>    // Для работы со строками (strlen, snprintf и другие функции)

// Главная функция программы
int main(int argc, char *argv[])
{
    Arguments args;                    // Структура для хранения аргументов командной строки
    parseArguments(argc, argv, &args); // Разбор аргументов командной строки

    Stack stack;       // Стек для хранения публикаций
    initStack(&stack); // Инициализация пустого стека

    // Проверяем, нужно ли генерировать данные
    if (args.generate)
    {
        // Генерация указанного количества случайных публикаций
        for (int i = 0; i < args.generate_count; i++)
        {
            Publication pub;                                                                 // Структура для хранения одной публикации
            snprintf(pub.title, sizeof(pub.title), "Publication %d", i + 1);                 // Генерация названия
            snprintf(pub.author_last_name, sizeof(pub.author_last_name), "Author%d", i + 1); // Генерация фамилии автора
            snprintf(pub.author_initials, sizeof(pub.author_initials), "A.B.");              // Генерация инициалов автора
            snprintf(pub.journal_name, sizeof(pub.journal_name), "Journal %d", (i % 5) + 1); // Генерация названия журнала
            pub.year = 2000 + (i % 20);                                                      // Генерация года публикации
            pub.volume = (i % 10) + 1;                                                       // Генерация тома журнала
            pub.in_rinc = (i % 2);                                                           // Генерация логического значения (входит ли в РИНЦ)
            pub.pages = 10 + (i % 50);                                                       // Генерация количества страниц
            pub.citations = (i % 100);                                                       // Генерация количества цитирований

            push(&stack, pub); // Добавление публикации в стек
        }

        // Если указан файл для вывода, сохраняем данные в CSV
        if (strlen(args.output_file) > 0)
        {
            writeToCSV(&stack, args.output_file); // Запись в CSV-файл
        }
        else
        {
            printData(&stack); // Вывод данных на экран
        }
    }
    // Проверяем, нужно ли сортировать данные
    else if (args.sort)
    {
        // Чтение данных из указанного входного файла
        if (strlen(args.input_file) > 0)
        {
            readFromCSV(&stack, args.input_file); // Чтение из CSV-файла
        }

        // Выбор типа сортировки (по возрастанию или убыванию)
        if (args.sort_type == 'A')
        {
            insertionSort(&stack, comparePublicationAsc); // Сортировка по возрастанию
        }
        else if (args.sort_type == 'D')
        {
            insertionSort(&stack, comparePublicationDesc); // Сортировка по убыванию
        }

        // Если указан файл для вывода, сохраняем отсортированные данные в CSV
        if (strlen(args.output_file) > 0)
        {
            writeToCSV(&stack, args.output_file); // Запись в CSV-файл
        }
        else
        {
            printData(&stack); // Вывод данных на экран
        }
    }
    // Проверяем, нужно ли просто вывести данные
    else if (args.print)
    {
        // Чтение данных из указанного входного файла
        if (strlen(args.input_file) > 0)
        {
            readFromCSV(&stack, args.input_file); // Чтение из CSV-файла
        }
        printData(&stack); // Печать данных на экран
    }

    clearStack(&stack); // Очистка стека (освобождение памяти)
    return 0;           // Успешное завершение программы
}