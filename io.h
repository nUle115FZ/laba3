#ifndef IO_H
#define IO_H

#include "stack.h"

// Функции для работы с вводом-выводом
void readFromCSV(Stack *stack, const char *filename);
void writeToCSV(Stack *stack, const char *filename);
void printData(Stack *stack);

#endif // IO_H