#include "arguments.h" // Заголовочный файл, где объявлена структура Arguments
#include <string.h>    // Для работы со строками (strcmp, strncmp, sscanf)
#include <stdio.h>     // Для вывода ошибок и сообщений
#include <stdlib.h>    // Для функций atoi и exit

// Функция для обработки аргументов командной строки
void parseArguments(int argc, char *argv[], Arguments *args)
{
    // Инициализируем все поля структуры Arguments значениями по умолчанию
    args->generate = 0;          // По умолчанию генерация данных отключена
    args->sort = 0;              // По умолчанию сортировка отключена
    args->print = 0;             // По умолчанию вывод отключен
    args->input_file[0] = '\0';  // Пустая строка для входного файла
    args->output_file[0] = '\0'; // Пустая строка для выходного файла
    args->sort_type = 'A';       // Сортировка по возрастанию ('A') по умолчанию
    args->generate_count = 0;    // Количество записей для генерации (0 по умолчанию)

    // Обрабатываем все аргументы, начиная с первого после имени программы
    for (int i = 1; i < argc; i++)
    {
        // Проверяем аргумент --generate или -g
        if (strcmp(argv[i], "--generate") == 0 || strcmp(argv[i], "-g") == 0)
        {
            if (i + 1 < argc) // Проверяем, есть ли следующий аргумент (количество записей)
            {
                args->generate = 1;                     // Устанавливаем флаг генерации
                args->generate_count = atoi(argv[++i]); // Преобразуем количество записей в число
            }
            else
            {
                // Если количество записей отсутствует, выводим ошибку и завершаем программу
                fprintf(stderr, "Ошибка: отсутствует количество записей после --generate/-g\n");
                exit(EXIT_FAILURE); // Прерываем выполнение программы
            }
        }
        // Проверяем аргумент --sort или -s
        else if (strcmp(argv[i], "--sort") == 0 || strcmp(argv[i], "-s") == 0)
        {
            args->sort = 1; // Устанавливаем флаг сортировки
        }
        // Проверяем аргумент --print или -P
        else if (strcmp(argv[i], "--print") == 0 || strcmp(argv[i], "-P") == 0)
        {
            args->print = 1; // Устанавливаем флаг вывода
        }
        // Проверяем аргумент для входного файла --in=<имя> или -i <имя>
        else if (strncmp(argv[i], "--in=", 5) == 0 || strncmp(argv[i], "-i", 2) == 0)
        {
            sscanf(argv[i], "--in=%255s", args->input_file); // Извлекаем имя входного файла
        }
        // Проверяем аргумент для выходного файла --out=<имя> или -o <имя>
        else if (strncmp(argv[i], "--out=", 6) == 0 || strncmp(argv[i], "-o", 2) == 0)
        {
            sscanf(argv[i], "--out=%255s", args->output_file); // Извлекаем имя выходного файла
        }
        // Проверяем аргумент для типа сортировки --type=<тип> или -t <тип>
        else if (strncmp(argv[i], "--type=", 7) == 0 || strncmp(argv[i], "-t", 2) == 0)
        {
            sscanf(argv[i], "--type=%c", &args->sort_type);       // Извлекаем тип сортировки
            if (args->sort_type != 'A' && args->sort_type != 'D') // Проверяем, допустим ли тип
            {
                // Если тип некорректный, выводим ошибку и завершаем выполнение
                fprintf(stderr, "Ошибка: недопустимый тип сортировки. Используйте 'A' или 'D'\n");
                exit(EXIT_FAILURE); // Прерываем выполнение программы
            }
        }
    }
}
