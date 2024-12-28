#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Чтение данных из CSV-файла
void readFromCSV(Stack *stack, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Ошибка открытия файла для чтения");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        Publication pub;
        char rinc[4];
        sscanf(line, "%255[^,],%127[^,],%15[^,],%127[^,],%d,%d,%3[^,],%d,%d",
               pub.title, pub.author_last_name, pub.author_initials, pub.journal_name,
               &pub.year, &pub.volume, rinc, &pub.pages, &pub.citations);

        pub.in_rinc = (strcmp(rinc, "YES") == 0) ? 1 : 0;
        push(stack, pub);
    }

    fclose(file);
}

// Запись данных в CSV-файл
void writeToCSV(Stack *stack, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Ошибка открытия файла для записи");
        exit(EXIT_FAILURE);
    }

    for (Node *current = stack->top; current != NULL; current = current->next)
    {
        Publication *pub = &current->data;
        fprintf(file, "%s,%s,%s,%s,%d,%d,%s,%d,%d\n",
                pub->title, pub->author_last_name, pub->author_initials,
                pub->journal_name, pub->year, pub->volume,
                pub->in_rinc ? "YES" : "NO", pub->pages, pub->citations);
    }

    fclose(file);
}

// Печать данных в табличном формате
void printData(Stack *stack)
{
    printf("+--------------------------------+-------------------+-----+-------------------+------+-----+-----+-----+-----+\n");
    printf("| Title                          | Author Last Name  | AI  | Journal Name      | Year | Vol | RINC| Pgs | Cit |\n");
    printf("+--------------------------------+-------------------+-----+-------------------+------+-----+-----+-----+-----+\n");

    for (Node *current = stack->top; current != NULL; current = current->next)
    {
        Publication *pub = &current->data;
        printf("| %-30s | %-17s | %-3s | %-17s | %-4d | %-3d | %-3s | %-3d | %-3d |\n",
               pub->title, pub->author_last_name, pub->author_initials, pub->journal_name,
               pub->year, pub->volume, pub->in_rinc ? "YES" : "NO", pub->pages, pub->citations);
    }

    printf("+--------------------------------+-------------------+-----+-------------------+------+-----+-----+-----+-----+\n");
}