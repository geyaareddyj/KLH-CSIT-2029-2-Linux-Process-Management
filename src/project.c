#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/* =================================================
   SHOW PROCESS STATE
   ================================================= */

void show_process_state(pid_t pid)
{
    char path[100];
    char line[256];

    sprintf(path, "/proc/%d/status", pid);

    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        perror("Could not open process status");
        return;
    }

    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "State:", 6) == 0)
        {
            printf("%s", line);
            break;
        }
    }

    fclose(file);
}


/* =================================================
   FORK + EXEC DEMO
   ================================================= */

void fork_exec_demo()
{
    printf("\n========== FORK + EXEC DEMO ==========\n");

    fflush(stdout);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        /* Child */

        printf("Child process created\n");
        printf("Child PID  : %d\n", getpid());
        printf("Child PPID : %d\n", getppid());

        printf("Child is now executing 'ls -l'\n\n");

        fflush(stdout);

        execlp("ls", "ls", "-l", NULL);

        perror("exec failed");
        exit(1);
    }
    else
    {
        /* Parent */

        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);

        printf("Parent is waiting for child...\n");

        waitpid(pid, NULL, 0);

        printf("Child finished.\n");
    }

    printf("=======================================\n\n");
}


/* =================================================
   PIPE DEMO
   ================================================= */

void pipe_demo()
{
    printf("\n========== PIPE DEMO ==========\n");

    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    pid_t pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork");
        return;
    }

    if (pid1 == 0)
    {
        /* First child */

        printf("First child PID: %d\n", getpid());

        close(pipefd[0]);

        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[1]);

        execlp("ls", "ls", NULL);

        perror("exec ls");
        exit(1);
    }


    pid_t pid2 = fork();

    if (pid2 < 0)
    {
        perror("fork");
        return;
    }

    if (pid2 == 0)
    {
        /* Second child */

        printf("Second child PID: %d\n", getpid());

        close(pipefd[1]);

        dup2(pipefd[0], STDIN_FILENO);

        close(pipefd[0]);

        execlp("wc", "wc", "-l", NULL);

        perror("exec wc");
        exit(1);
    }


    /* Parent */

    close(pipefd[0]);
    close(pipefd[1]);

    printf("Parent PID: %d\n", getpid());
    printf("Waiting for both processes...\n");

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Pipe execution completed.\n");

    printf("================================\n\n");
}


/* =================================================
   TERMINATION DEMO
   ================================================= */

void termination_demo()
{
    printf("\n========== TERMINATION DEMO ==========\n");

    fflush(stdout);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        /* Child */

        printf("Child PID: %d\n", getpid());

        printf("Child is terminating using exit(5)\n");

        exit(5);
    }
    else
    {
        /* Parent */

        int status;

        printf("Parent PID: %d\n", getpid());
        printf("Waiting for child...\n");

        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            printf("Child terminated normally.\n");
            printf("Child exit status: %d\n",
                   WEXITSTATUS(status));
        }
    }

    printf("=======================================\n\n");
}


/* =================================================
   ZOMBIE DEMO
   ================================================= */

void zombie_demo()
{
    printf("\n========== ZOMBIE PROCESS DEMO ==========\n");

    fflush(stdout);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        /* Child */

        printf("Child PID: %d\n", getpid());

        printf("Child is exiting now...\n");

        fflush(stdout);

        exit(0);
    }
    else
    {
        /* Parent */

        printf("Parent PID: %d\n", getpid());
        printf("Child PID : %d\n", pid);

        printf("\nChild has terminated.\n");

        printf("Parent has NOT called wait() yet.\n");

        printf("Checking child state from /proc...\n");

        sleep(2);

        printf("\nChild process state:\n");

        show_process_state(pid);

        printf("\nNow parent calls waitpid()...\n");

        waitpid(pid, NULL, 0);

        printf("Zombie removed.\n");
    }

    printf("==========================================\n\n");
}


/* =================================================
   ORPHAN DEMO
   ================================================= */

void orphan_demo()
{
    printf("\n========== ORPHAN PROCESS DEMO ==========\n");

    int sync_pipe[2];

    if (pipe(sync_pipe) == -1)
    {
        perror("pipe");
        return;
    }

    fflush(stdout);

    /*
       The terminal creates a demo parent.

       The demo parent creates another child.

       The demo parent exits.

       The child becomes an orphan.
    */

    pid_t demo_parent = fork();

    if (demo_parent < 0)
    {
        perror("fork");
        return;
    }


    if (demo_parent == 0)
    {
        /* Demo parent */

        close(sync_pipe[0]);

        pid_t orphan = fork();

        if (orphan < 0)
        {
            perror("fork");
            exit(1);
        }

        if (orphan == 0)
        {
            /* This process will become an orphan */

            printf("Orphan candidate PID : %d\n",
                   getpid());

            printf("Original PPID        : %d\n",
                   getppid());

            fflush(stdout);

            sleep(2);

            printf("\nDemo parent has terminated.\n");

            printf("New PPID of orphan   : %d\n",
                   getppid());

            printf("This process is now an orphan.\n");

            fflush(stdout);

            /*
               Tell original terminal that
               demonstration is complete.
            */

            write(sync_pipe[1], "1", 1);

            close(sync_pipe[1]);

            exit(0);
        }
        else
        {
            printf("Demo parent PID      : %d\n",
                   getpid());

            printf("Created child PID    : %d\n",
                   orphan);

            printf("Demo parent is now terminating...\n");

            fflush(stdout);

            close(sync_pipe[1]);

            exit(0);
        }
    }
    else
    {
        /* Original terminal */

        close(sync_pipe[1]);

        printf("Terminal PID         : %d\n",
               getpid());

        printf("Demo parent PID      : %d\n",
               demo_parent);

        waitpid(demo_parent, NULL, 0);

        printf("\nDemo parent terminated.\n");

        printf("Waiting for orphan demonstration...\n");

        char message;

        read(sync_pipe[0], &message, 1);

        close(sync_pipe[0]);

        printf("Orphan demonstration completed.\n");
    }

    printf("==========================================\n\n");
}


/* =================================================
   RUN ALL DEMOS
   ================================================= */

void os_demo()
{
    printf("\n");
    printf("##########################################\n");
    printf("#       OS PROCESS DEMONSTRATIONS        #\n");
    printf("##########################################\n");

    fork_exec_demo();

    pipe_demo();

    termination_demo();

    zombie_demo();

    orphan_demo();

    printf("##########################################\n");
    printf("#          ALL DEMOS COMPLETED           #\n");
    printf("##########################################\n\n");
}


/* =================================================
   HELP
   ================================================= */

void show_help()
{
    printf("\n========== MY TERMINAL COMMANDS ==========\n");

    printf("\nNormal Linux commands:\n");
    printf("  ls\n");
    printf("  ls -l\n");
    printf("  ps\n");
    printf("  date\n");
    printf("  whoami\n");
    printf("  cat <file>\n");

    printf("\nBuilt-in commands:\n");
    printf("  pwd\n");
    printf("  cd <directory>\n");
    printf("  help\n");
    printf("  exit\n");

    printf("\nOS demonstrations:\n");
    printf("  forkdemo\n");
    printf("  pipedemo\n");
    printf("  terminationdemo\n");
    printf("  zombiedemo\n");
    printf("  orphandemo\n");
    printf("  osdemo\n");

    printf("==========================================\n\n");
}


/* =================================================
   NORMAL TERMINAL
   ================================================= */

void start_terminal()
{
    char input[200];
    char *args[20];

    printf("\n");
    printf("========================================\n");
    printf("          MY OS TERMINAL\n");
    printf("========================================\n");
    printf("Type 'help' to see available commands.\n");
    printf("Type 'exit' to return to the menu.\n");
    printf("========================================\n\n");


    while (1)
    {
        printf("myterminal$ ");
        fflush(stdout);

        /* Read command */

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        /* Remove newline */

        input[strcspn(input, "\n")] = '\0';

        /* Ignore empty input */

        if (strlen(input) == 0)
        {
            continue;
        }


        /* -----------------------------------------
           EXIT TERMINAL
           ----------------------------------------- */

        if (strcmp(input, "exit") == 0)
        {
            printf("Returning to main menu...\n");
            break;
        }


        /* -----------------------------------------
           HELP
           ----------------------------------------- */

        if (strcmp(input, "help") == 0)
        {
            show_help();
            continue;
        }


        /* -----------------------------------------
           FORK DEMO
           ----------------------------------------- */

        if (strcmp(input, "forkdemo") == 0)
        {
            fork_exec_demo();
            continue;
        }


        /* -----------------------------------------
           PIPE DEMO
           ----------------------------------------- */

        if (strcmp(input, "pipedemo") == 0)
        {
            pipe_demo();
            continue;
        }


        /* -----------------------------------------
           TERMINATION DEMO
           ----------------------------------------- */

        if (strcmp(input, "terminationdemo") == 0)
        {
            termination_demo();
            continue;
        }


        /* -----------------------------------------
           ZOMBIE DEMO
           ----------------------------------------- */

        if (strcmp(input, "zombiedemo") == 0)
        {
            zombie_demo();
            continue;
        }


        /* -----------------------------------------
           ORPHAN DEMO
           ----------------------------------------- */

        if (strcmp(input, "orphandemo") == 0)
        {
            orphan_demo();
            continue;
        }


        /* -----------------------------------------
           ALL DEMOS
           ----------------------------------------- */

        if (strcmp(input, "osdemo") == 0)
        {
            os_demo();
            continue;
        }


        /* -----------------------------------------
           CHECK FOR PIPE
           ----------------------------------------- */

        char *pipe_position = strchr(input, '|');

        if (pipe_position != NULL)
        {
            *pipe_position = '\0';

            char *command1 = input;
            char *command2 = pipe_position + 1;

            while (*command1 == ' ')
            {
                command1++;
            }

            while (*command2 == ' ')
            {
                command2++;
            }


            /* Parse first command */

            char *args1[20];

            int i = 0;

            char *token = strtok(command1, " ");

            while (token != NULL && i < 19)
            {
                args1[i] = token;
                i++;

                token = strtok(NULL, " ");
            }

            args1[i] = NULL;


            /* Parse second command */

            char *args2[20];

            i = 0;

            token = strtok(command2, " ");

            while (token != NULL && i < 19)
            {
                args2[i] = token;
                i++;

                token = strtok(NULL, " ");
            }

            args2[i] = NULL;


            /* Create pipe */

            int pipefd[2];

            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                continue;
            }


            /* First child */

            pid_t pid1 = fork();

            if (pid1 < 0)
            {
                perror("fork");
                continue;
            }

            if (pid1 == 0)
            {
                close(pipefd[0]);

                dup2(pipefd[1], STDOUT_FILENO);

                close(pipefd[1]);

                execvp(args1[0], args1);

                perror("Command 1 failed");

                exit(1);
            }


            /* Second child */

            pid_t pid2 = fork();

            if (pid2 < 0)
            {
                perror("fork");
                continue;
            }

            if (pid2 == 0)
            {
                close(pipefd[1]);

                dup2(pipefd[0], STDIN_FILENO);

                close(pipefd[0]);

                execvp(args2[0], args2);

                perror("Command 2 failed");

                exit(1);
            }


            /* Parent */

            close(pipefd[0]);
            close(pipefd[1]);

            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

            continue;
        }


        /* -----------------------------------------
           PARSE NORMAL COMMAND
           ----------------------------------------- */

        int i = 0;

        char *token = strtok(input, " ");

        while (token != NULL && i < 19)
        {
            args[i] = token;
            i++;

            token = strtok(NULL, " ");
        }

        args[i] = NULL;


        /* -----------------------------------------
           PWD
           ----------------------------------------- */

        if (strcmp(args[0], "pwd") == 0)
        {
            char cwd[200];

            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                printf("%s\n", cwd);
            }
            else
            {
                perror("pwd");
            }

            continue;
        }


        /* -----------------------------------------
           CD
           ----------------------------------------- */

        if (strcmp(args[0], "cd") == 0)
        {
            if (args[1] == NULL)
            {
                printf("Usage: cd <directory>\n");
            }
            else if (chdir(args[1]) != 0)
            {
                perror("cd");
            }

            continue;
        }


        /* -----------------------------------------
           EXTERNAL COMMAND
           ----------------------------------------- */

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            continue;
        }

        if (pid == 0)
        {
            execvp(args[0], args);

            perror("Command not found");

            exit(1);
        }
        else
        {
            waitpid(pid, NULL, 0);
        }
    }
}


/* =================================================
   STARTUP MENU
   ================================================= */

void show_menu()
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("========================================\n");
        printf("             MY OS TERMINAL\n");
        printf("========================================\n");
        printf("1. Fork + Exec Demo\n");
        printf("2. Pipe Demo\n");
        printf("3. Process Termination Demo\n");
        printf("4. Zombie Process Demo\n");
        printf("5. Orphan Process Demo\n");
        printf("6. Run All OS Demos\n");
        printf("7. Start Normal Terminal\n");
        printf("8. Help\n");
        printf("9. Exit\n");
        printf("========================================\n");

        printf("Enter your choice: ");
        fflush(stdout);

        scanf("%d", &choice);

        /*
           Remove the leftover newline from scanf
           so fgets() works correctly later.
        */

        getchar();


        switch (choice)
        {
            case 1:
                fork_exec_demo();
                break;

            case 2:
                pipe_demo();
                break;

            case 3:
                termination_demo();
                break;

            case 4:
                zombie_demo();
                break;

            case 5:
                orphan_demo();
                break;

            case 6:
                os_demo();
                break;

            case 7:
                start_terminal();
                break;

            case 8:
                show_help();
                break;

            case 9:
                printf("\nExiting My OS Terminal...\n");
                return;

            default:
                printf("\nInvalid choice. Please enter 1-9.\n");
        }
    }
}


/* =================================================
   MAIN
   ================================================= */

int main()
{
    show_menu();

    return 0;
}
