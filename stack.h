#ifndef STACK_H
#define STACK_H

#include "publication.h"

// Узел для связного списка
typedef struct Node
{
    Publication data;  // Данные (публикация)
    struct Node *next; // Указатель на следующий узел
} Node;

// Стек, представленный через связный список
typedef struct
{
    Node *top; // Указатель на вершину стека
    int size;  // Текущий размер стека
} Stack;

// Функции для работы со стеком
void initStack(Stack *stack);
void push(Stack *stack, Publication item);
Publication pop(Stack *stack);
Publication *peek(Stack *stack);
int getSize(Stack *stack);
Publication *getElement(Stack *stack, int index);
void clearStack(Stack *stack);

#endif // STACK_H