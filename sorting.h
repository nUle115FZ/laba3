#ifndef SORTING_H
#define SORTING_H

#include "stack.h"

// Компараторы для сортировки
int comparePublicationAsc(const Publication *a, const Publication *b);
int comparePublicationDesc(const Publication *a, const Publication *b);

// Сортировка вставками с использованием компаратора
void insertionSort(Stack *stack, int (*comparator)(const Publication *, const Publication *));

#endif // SORTING_H
