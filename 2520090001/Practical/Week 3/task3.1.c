#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Process started\n");
    printf("Initial PID: %d\n", getpid());

    pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }

    else if (pid == 0) {
        // Child process
        printf("\n--- Child Process ---\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        printf("Child state: Running\n");

        sleep(3);

        printf("Child state: Running after sleep\n");
    }

    else {
        // Parent process
        printf("\n--- Parent Process ---\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("Parent state: Running\n");

        wait(NULL);

        printf("Parent state: Running after child completed\n");
    }

    return 0;
}
