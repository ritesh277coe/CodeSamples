#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <bits/wordsize.h>

# if __WORDSIZE == 64
//int dagljh
#endif
/***************************************************************************/
/***************************************************************************/

//Steps to override the glic malloc implementation
//malloc is weak symbol in glic and its implemenation can be overridden by strong symbol
//Similarly, free, calloc, realloc can also be overridden
//Suggested reading on weak symbols and alias in gcc
extern void *__libc_malloc(size_t size);

__attribute__((no_instrument_function))
void* malloc(size_t size)
{
    void *caller = __builtin_return_address(0);
    return __libc_malloc(size);
}
extern void *__libc_free(void *ptr);

__attribute__((no_instrument_function))
void free(void *ptr)
{
     __libc_free(ptr);
}

int
main(void)
{
    void *ptr = malloc(10);
    free(ptr);

    exit(EXIT_SUCCESS);
}
