#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    char command[50];
    pid_t pid;

    printf("Enter Linux command: ");
    scanf("%49s", command);

    pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
    }
    else if (pid == 0) {
        // Child process
        printf("Child PID: %d\n", getpid());

        execlp(command, command, NULL);

        // This executes only if execlp() fails
        printf("Command execution failed!\n");
    }
    else {
        // Parent process
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        wait(NULL);

        printf("Child process completed.\n");
    }

    return 0;
}
