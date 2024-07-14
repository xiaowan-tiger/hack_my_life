#include <apue.h>

int main(void) 
{

    int c;
    while ((c = getc(stdin) != EOF))
    {
        if (putc(c, stdout) == EOF)
            ; // error hanling

    }

    exit(0);
}
