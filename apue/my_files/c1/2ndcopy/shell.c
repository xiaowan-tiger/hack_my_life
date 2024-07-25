#include "apue.h"

static void sig_int(int signo);


int main(void)
{
    char buf[MAXLINE];
    pid_t pid;

    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
        err_sys("signal error");
    }

    printf("%%");

    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n') 
        {
            buf[strlen(buf) - 1] = 0;
        }

        if ((pid = fork()) == 0)
        {
            execlp(buf, buf, (char *)0);
            err_sys("could not execute %s", buf);
            exit(127);
        }

        printf("%%");

    }

    exit(0);
}

void sig_int(int signo)
{
    printf("interrupted by %d\n",signo);
}