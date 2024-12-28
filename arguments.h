#ifndef ARGUMENTS_H
#define ARGUMENTS_H

// Структура для хранения аргументов командной строки
typedef struct
{
    int generate;          // Флаг генерации данных (N записей)
    int sort;              // Флаг сортировки
    int print;             // Флаг вывода данных
    char input_file[256];  // Входной файл
    char output_file[256]; // Выходной файл
    char sort_type;        // Тип сортировки ('A' - по возрастанию, 'D' - по убыванию)
    int generate_count;    // Количество записей для генерации
} Arguments;

// Функция для обработки аргументов командной строки
void parseArguments(int argc, char *argv[], Arguments *args);

#endif // ARGUMENTS_H