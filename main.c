#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "io.h"
#include "arguments.h"
#include "sorting.h"
#include <string.h>

int main(int argc, char *argv[])
{
    Arguments args;
    parseArguments(argc, argv, &args);

    Stack stack;
    initStack(&stack);

    if (args.generate)
    {
        for (int i = 0; i < args.generate_count; i++)
        {
            Publication pub;
            snprintf(pub.title, sizeof(pub.title), "Publication %d", i + 1);
            snprintf(pub.author_last_name, sizeof(pub.author_last_name), "Author%d", i + 1);
            snprintf(pub.author_initials, sizeof(pub.author_initials), "A.B.");
            snprintf(pub.journal_name, sizeof(pub.journal_name), "Journal %d", (i % 5) + 1);
            pub.year = 2000 + (i % 20);
            pub.volume = (i % 10) + 1;
            pub.in_rinc = (i % 2);
            pub.pages = 10 + (i % 50);
            pub.citations = (i % 100);

            push(&stack, pub);
        }

        if (strlen(args.output_file) > 0)
        {
            writeToCSV(&stack, args.output_file);
        }
        else
        {
            printData(&stack);
        }
    }
    else if (args.sort)
    {
        if (strlen(args.input_file) > 0)
        {
            readFromCSV(&stack, args.input_file);
        }

        if (args.sort_type == 'A')
        {
            insertionSort(&stack, comparePublicationAsc);
        }
        else if (args.sort_type == 'D')
        {
            insertionSort(&stack, comparePublicationDesc);
        }

        if (strlen(args.output_file) > 0)
        {
            writeToCSV(&stack, args.output_file);
        }
        else
        {
            printData(&stack);
        }
    }
    else if (args.print)
    {
        if (strlen(args.input_file) > 0)
        {
            readFromCSV(&stack, args.input_file);
        }
        printData(&stack);
    }

    clearStack(&stack);
    return 0;
}
