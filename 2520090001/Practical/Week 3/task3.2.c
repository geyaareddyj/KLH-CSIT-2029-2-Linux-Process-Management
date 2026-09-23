#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Process started.\n");
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());

    printf("\nProcess is Running...\n");

    printf("\nProcess will enter Waiting state for 10 seconds.\n");
    sleep(10);

    printf("\nProcess is Running again.\n");

    printf("Press Enter to terminate the process...\n");
    getchar();

    printf("Process is Terminating...\n");

    return 0;
}
