#include "arguments.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Функция для обработки аргументов командной строки
void parseArguments(int argc, char *argv[], Arguments *args)
{
    args->generate = 0;
    args->sort = 0;
    args->print = 0;
    args->input_file[0] = '\0';
    args->output_file[0] = '\0';
    args->sort_type = 'A'; // По умолчанию сортировка по возрастанию
    args->generate_count = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--generate") == 0 || strcmp(argv[i], "-g") == 0)
        {
            if (i + 1 < argc)
            {
                args->generate = 1;
                args->generate_count = atoi(argv[++i]);
            }
            else
            {
                fprintf(stderr, "Ошибка: отсутствует количество записей после --generate/-g\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(argv[i], "--sort") == 0 || strcmp(argv[i], "-s") == 0)
        {
            args->sort = 1;
        }
        else if (strcmp(argv[i], "--print") == 0 || strcmp(argv[i], "-P") == 0)
        {
            args->print = 1;
        }
        else if (strncmp(argv[i], "--in=", 5) == 0 || strncmp(argv[i], "-i", 2) == 0)
        {
            sscanf(argv[i], "--in=%255s", args->input_file);
        }
        else if (strncmp(argv[i], "--out=", 6) == 0 || strncmp(argv[i], "-o", 2) == 0)
        {
            sscanf(argv[i], "--out=%255s", args->output_file);
        }
        else if (strncmp(argv[i], "--type=", 7) == 0 || strncmp(argv[i], "-t", 2) == 0)
        {
            sscanf(argv[i], "--type=%c", &args->sort_type);
            if (args->sort_type != 'A' && args->sort_type != 'D')
            {
                fprintf(stderr, "Ошибка: недопустимый тип сортировки. Используйте 'A' или 'D'\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
