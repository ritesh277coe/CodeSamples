//multiple calls to atexit_handler call gets called in LIFO manner(stack)
//gcc -ggdb -O0 ./multiple_atexit_handlers_stack_up.c -o t

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <bits/wordsize.h>

void
atexit_handler1(void)
{
    printf("Inside atexit handler1\n");
}

void
atexit_handler2(void)
{
    printf("Inside atexit handler2\n");
}

int main()
{
    long a;
    int i;

    a = sysconf(_SC_ATEXIT_MAX);
    printf("ATEXIT_MAX = %ld\n", a);

    i = atexit(atexit_handler1); //handler has to be (void (*function)(void)
    if (i != 0) {
        fprintf(stderr, "cannot set exit function\n");
        return EXIT_FAILURE;
    }

    i = atexit(atexit_handler2);
    if (i != 0) {
        fprintf(stderr, "cannot set exit function\n");
        exit(EXIT_FAILURE);
    }
    printf("Inside main\n");
    return 0;
}
