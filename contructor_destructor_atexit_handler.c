#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <bits/wordsize.h>

void
__attribute__ ((constructor))
trace_begin (void)
{
    printf ("Constructor\n");
}

void
__attribute__ ((destructor))
trace_end (void)
{
    printf ("Destructor\n");
}

void
atexit_handler(void)
{
    printf("Inside atexit handler\n");
}

int main()
{
    long a;
    int i;

    a = sysconf(_SC_ATEXIT_MAX);
    printf("ATEXIT_MAX = %ld\n", a);

    i = atexit(atexit_handler); //handler has to be (void (*function)(void)
    if (i != 0) {
        fprintf(stderr, "cannot set exit function\n");
        return EXIT_FAILURE;
    }

    printf("Inside main\n");
    return 0;
}
