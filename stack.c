#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

// Инициализация стека
void initStack(Stack *stack)
{
    stack->top = NULL;
    stack->size = 0;
}

// Добавление элемента в стек
void push(Stack *stack, Publication item)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    newNode->data = item;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

// Удаление элемента из стека
Publication pop(Stack *stack)
{
    if (stack->size == 0)
    {
        perror("Попытка удалить элемент из пустого стека");
        exit(EXIT_FAILURE);
    }
    Node *temp = stack->top;
    Publication item = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return item;
}

// Получение верхнего элемента стека
Publication *peek(Stack *stack)
{
    if (stack->size == 0)
    {
        perror("Попытка посмотреть элемент в пустом стеке");
        exit(EXIT_FAILURE);
    }
    return &stack->top->data;
}

// Получение текущего размера стека
int getSize(Stack *stack)
{
    return stack->size;
}

// Получение элемента по индексу
Publication *getElement(Stack *stack, int index)
{
    if (index < 0 || index >= stack->size)
    {
        return NULL;
    }

    Node *current = stack->top;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return &current->data;
}

// Очистка стека
void clearStack(Stack *stack)
{
    while (stack->size > 0)
    {
        pop(stack);
    }
}