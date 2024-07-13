#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0) { // child
        printf("child process PID: %d\n", getpid());
        exit(5);
    } else if (pid > 0) {
        printf("parent process PID: %d\n",getpid());
        wait(&status);
        printf("child process exited with code: %d\n",WEXITSTATUS(status));
    } else {
        printf("fork failure\n");
        return 1;
    }


    return 0;
}
