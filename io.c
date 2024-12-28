#include "io.h"     // Заголовочный файл с декларацией функций ввода-вывода
#include <stdio.h>  // Стандартная библиотека ввода-вывода (для работы с файлами и консолью)
#include <stdlib.h> // Для функций управления памятью и обработки ошибок
#include <string.h> // Для работы со строками (strcmp, sscanf и другие функции)

// Функция для чтения данных из CSV-файла
void readFromCSV(Stack *stack, const char *filename)
{
    FILE *file = fopen(filename, "r"); // Открываем файл для чтения
    if (!file)                         // Проверяем, удалось ли открыть файл
    {
        perror("Ошибка открытия файла для чтения"); // Выводим сообщение об ошибке, если файл не открылся
        exit(EXIT_FAILURE);                         // Завершаем программу с кодом ошибки
    }

    char line[1024];                        // Буфер для чтения строк из файла
    while (fgets(line, sizeof(line), file)) // Читаем строки из файла, пока не достигнем конца
    {
        Publication pub; // Структура для хранения данных публикации
        char rinc[4];    // Временная строка для логического значения (YES/NO)

        // Извлекаем данные из строки в структуру
        sscanf(line, "%255[^,],%127[^,],%15[^,],%127[^,],%d,%d,%3[^,],%d,%d",
               pub.title, pub.author_last_name, pub.author_initials, pub.journal_name,
               &pub.year, &pub.volume, rinc, &pub.pages, &pub.citations);

        // Преобразуем строку YES/NO в логическое значение (1/0)
        pub.in_rinc = (strcmp(rinc, "YES") == 0) ? 1 : 0;

        push(stack, pub); // Добавляем публикацию в стек
    }

    fclose(file); // Закрываем файл
}

// Функция для записи данных из стека в CSV-файл
void writeToCSV(Stack *stack, const char *filename)
{
    FILE *file = fopen(filename, "w"); // Открываем файл для записи
    if (!file)                         // Проверяем, удалось ли открыть файл
    {
        perror("Ошибка открытия файла для записи"); // Выводим сообщение об ошибке, если файл не открылся
        exit(EXIT_FAILURE);                         // Завершаем программу с кодом ошибки
    }

    // Проходим по всем элементам стека и записываем их в файл
    for (Node *current = stack->top; current != NULL; current = current->next)
    {
        Publication *pub = &current->data;            // Получаем данные текущего узла стека
        fprintf(file, "%s,%s,%s,%s,%d,%d,%s,%d,%d\n", // Записываем данные в формате CSV
                pub->title, pub->author_last_name, pub->author_initials,
                pub->journal_name, pub->year, pub->volume,
                pub->in_rinc ? "YES" : "NO", pub->pages, pub->citations);
    }

    fclose(file); // Закрываем файл
}

// Функция для вывода данных из стека в табличном формате
void printData(Stack *stack)
{
    // Печатаем заголовок таблицы
    printf("+--------------------------------+-------------------+-----+-------------------+------+-----+-----+-----+-----+\n");
    printf("| Title                          | Author Last Name  | AI  | Journal Name      | Year | Vol | RINC| Pgs | Cit |\n");
    printf("+--------------------------------+-------------------+-----+-------------------+------+-----+-----+-----+-----+\n");

    // Проходим по всем элементам стека и выводим их в табличном формате
    for (Node *current = stack->top; current != NULL; current = current->next)
    {
        Publication *pub = &current->data; // Получаем данные текущего узла стека
        printf("| %-30s | %-17s | %-3s | %-17s | %-4d | %-3d | %-3s | %-3d | %-3d |\n",
               pub->title, pub->author_last_name, pub->author_initials, pub->journal_name,
               pub->year, pub->volume, pub->in_rinc ? "YES" : "NO", pub->pages, pub->citations);
    }

    // Печатаем нижнюю границу таблицы
    printf("+--------------------------------+-------------------+-----+-------------------+------+-----+-----+-----+-----+\n");
}
