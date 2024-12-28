#include "sorting.h" // Заголовочный файл, содержащий прототипы функций сортировки
#include <string.h>  // Для работы со строками (strcmp)

// Компаратор для сортировки публикаций по возрастанию
int comparePublicationAsc(const Publication *a, const Publication *b)
{
    // Сравнивает названия публикаций в алфавитном порядке
    return strcmp(a->title, b->title);
}

// Компаратор для сортировки публикаций по убыванию
int comparePublicationDesc(const Publication *a, const Publication *b)
{
    // Сравнивает названия публикаций в обратном алфавитном порядке
    return strcmp(b->title, a->title);
}

// Реализация сортировки вставками
void insertionSort(Stack *stack, int (*comparator)(const Publication *, const Publication *))
{
    // Если в стеке меньше двух элементов, сортировка не требуется
    if (stack->size <= 1)
        return;

    Node *sorted = NULL; // Указатель на начало нового отсортированного списка

    // Переносим элементы из исходного стека в новый отсортированный список
    while (stack->top != NULL)
    {
        Node *current = stack->top;    // Берём верхний элемент из стека
        stack->top = stack->top->next; // Обновляем вершину стека

        // Если отсортированный список пуст или текущий элемент меньше первого элемента
        if (sorted == NULL || comparator(&current->data, &sorted->data) < 0)
        {
            current->next = sorted; // Вставляем текущий элемент в начало отсортированного списка
            sorted = current;
        }
        else
        {
            Node *temp = sorted;
            // Ищем место для вставки текущего элемента в отсортированном списке
            while (temp->next != NULL && comparator(&temp->next->data, &current->data) < 0)
            {
                temp = temp->next; // Переходим к следующему элементу
            }
            // Вставляем текущий элемент в найденное место
            current->next = temp->next;
            temp->next = current;
        }
    }

    // Переназначаем вершину стека на начало отсортированного списка
    stack->top = sorted;
}
