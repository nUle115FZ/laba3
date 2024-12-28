#ifndef PUBLICATION_H
#define PUBLICATION_H
// Структура, описывающая публикацию
typedef struct
{
    char title[256];            // Название публикации
    char author_last_name[128]; // Фамилия первого автора
    char author_initials[16];   // Инициалы первого автора
    char journal_name[128];     // Название журнала
    int year;                   // Год публикации
    int volume;                 // Том журнала
    int in_rinc;                // Входит ли в РИНЦ (1 = YES, 0 = NO)
    int pages;                  // Количество страниц
    int citations;              // Количество цитирований
} Publication;

#endif // PUBLICATION_H