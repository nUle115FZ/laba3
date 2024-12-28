#include "sorting.h"
#include <string.h>

// Компаратор для сортировки по возрастанию
int comparePublicationAsc(const Publication *a, const Publication *b)
{
    return strcmp(a->title, b->title); // Сортировка по названию публикации
}

// Компаратор для сортировки по убыванию
int comparePublicationDesc(const Publication *a, const Publication *b)
{
    return strcmp(b->title, a->title); // Сортировка по названию публикации
}

// Реализация сортировки вставками
void insertionSort(Stack *stack, int (*comparator)(const Publication *, const Publication *))
{
    if (stack->size <= 1)
        return; // Если стек пустой или имеет один элемент, сортировка не требуется

    Node *sorted = NULL; // Новый отсортированный список

    while (stack->top != NULL)
    {
        Node *current = stack->top;
        stack->top = stack->top->next;

        if (sorted == NULL || comparator(&current->data, &sorted->data) < 0)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            Node *temp = sorted;
            while (temp->next != NULL && comparator(&temp->next->data, &current->data) < 0)
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    stack->top = sorted;
}
