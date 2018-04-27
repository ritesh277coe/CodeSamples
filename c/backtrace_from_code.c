#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <bits/wordsize.h>

/***************************************************************************/
/***************************************************************************/
//Backtrace inside the code
//code compile with  gcc -ggdb -O0 -rdynamic  -o t ./test.c
//rdynamic is important if output needs to see the function names

//Links worth reading
//http://www.linuxjournal.com/article/6391?page=0,2
//man backtrace_symbols

void bt(void)
{
    int c, i;
    void *addresses[10];
    char **strings;

    c = backtrace(addresses, 10);
    strings = backtrace_symbols(addresses, c); //This symbold need malloc as you can see by overriding malloc/free.
                                               //Use backtrace_symbols_fd if you want to dump in file directly bypassing the malloc call.
    printf("backtrace returned: %dn", c);

    for(i = 0; i < c; i++)
    {
        printf("%d: %X ", i, (int)addresses[i]);
        printf("%s\n", strings[i]);
    }
}

void func2(int x)
{
    bt();
}

void func1(int x)
{
    func2(20);
}

int
main(void)
{
    func1(10);
    return 0;
}
