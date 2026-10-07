# Linux Process Creation, Execution and Termination System

## Team Members

| Name | Student ID |
|---|---|
| Jalla Geya Reddy | 2520090123 |
| Kamtam Priyanka | 2520090001 |

**Supervisor:** M. Raghupathi

---

## Abstract

Processes are one of the most important concepts in an operating system because they represent programs that are currently being executed. Understanding how a process is created, executed, monitored, synchronized, and terminated helps in understanding how the operating system manages system resources.

This project focuses on developing a Linux-based system that demonstrates the complete lifecycle of a process using C programming and Linux/POSIX system calls. The system demonstrates process creation using `fork()`, program execution using `execvp()`, process synchronization using `waitpid()`, inter-process communication using `pipe()`, and process termination using `exit()`.

The project also demonstrates important process concepts such as parent-child relationships, zombie processes, orphan processes, and process state monitoring using the Linux `/proc` filesystem. Process information such as Process ID (PID), Parent Process ID (PPID), and process state can be observed during the demonstrations.

In addition to the process management demonstrations, the project provides a simple custom terminal called **MY OS TERMINAL**. The terminal supports basic commands such as `pwd`, `ls`, `cd`, and `echo`, along with external command execution and basic pipelines.

The project provides a practical understanding of the Linux process lifecycle and demonstrates how user programs interact with the operating system through system calls.

---

## Project Objective

The main objective of this project is to provide a practical demonstration of the Linux process lifecycle and show how processes are created, executed, synchronized, monitored, and terminated.

The project demonstrates:

- Process creation using `fork()`
- Program execution using `execvp()`
- Parent-child process relationships
- Process synchronization using `waitpid()`
- Inter-process communication using `pipe()`
- Process termination using `exit()`
- Zombie process creation and removal
- Orphan process behavior
- Process state monitoring using `/proc`
- Basic command execution through a custom terminal
- Basic pipeline execution using Linux pipes

---

## Features

### 1. Fork + Exec Demonstration

Demonstrates how a parent process creates a child process using `fork()` and how the child executes another program using `execvp()`.

### 2. Pipe Demonstration

Demonstrates inter-process communication using `pipe()`.

Example:

    ls | wc -l

The output of one process is connected to the input of another process through a pipe.

### 3. Process Termination Demonstration

Demonstrates how a child process terminates using `exit()` and how the parent collects the child's termination status using `waitpid()`.

### 4. Zombie Process Demonstration

Demonstrates a zombie process, which occurs when a child process has terminated but the parent has not yet collected its exit status.

The project uses `/proc` to observe the zombie state and then uses `waitpid()` to remove the zombie.

### 5. Orphan Process Demonstration

Demonstrates an orphan process, where the parent process terminates before the child process.

The project observes the change in the child's Parent Process ID (PPID).

### 6. Run All OS Demonstrations

Provides an option to execute all major process management demonstrations sequentially.

### 7. Custom OS Terminal

The project includes a simple custom terminal called:

    MY OS TERMINAL

The terminal supports:

- `pwd`
- `ls`
- `cd`
- `echo`
- `help`
- External commands
- Basic pipelines
- `exit`

---

## Technologies Used

- **Programming Language:** C
- **Operating System:** Linux / Ubuntu
- **Environment:** Ubuntu / WSL
- **Compiler:** GCC
- **Version Control:** Git and GitHub
- **System Calls / Functions:**
  - `fork()`
  - `execvp()`
  - `waitpid()`
  - `pipe()`
  - `dup2()`
  - `exit()`

---

## Project Architecture

    MY OS TERMINAL
           |
           v
      MAIN MENU
           |
    +------+------+------+
    |             |      |
    v             v      v
 PROCESS DEMOS  CUSTOM  HELP
                TERMINAL
    |             |
    v             v
 +-----------+ +-----------+
 | Fork+Exec | | Built-ins |
 | Pipe      | | External  |
 | Termination| | Commands |
 | Zombie    | | Pipelines |
 | Orphan    | | Exit      |
 +-----------+ +-----------+
       |             |
       +------+------+
              |
              v
       LINUX/POSIX SYSTEM CALLS
   fork | exec | waitpid | pipe | dup2
              |
              v
         LINUX KERNEL

---

## Project Structure

    KLH-CSIT-2029-2-Linux-Process-Management/
    │
    ├── 2520090001/
    │
    ├── 2520090123/
    │
    ├── data/
    │
    ├── docs/
    │
    ├── reports/
    │
    ├── results/
    │
    ├── src/
    │   ├── empty.txt
    │   └── project.c
    │
    ├── Abstract.pdf
    ├── README.md
    └── ...

The main project source code is located at:

    src/project.c

---

## Setup and Execution

### Requirements

- Linux operating system or Ubuntu WSL
- GCC compiler
- Git

### Clone the Repository

    git clone https://github.com/geyaareddyj/KLH-CSIT-2029-2-Linux-Process-Management.git

Navigate into the project:

    cd KLH-CSIT-2029-2-Linux-Process-Management

### Compile the Project

Navigate to the source directory:

    cd src

Compile the project using GCC:

    gcc project.c -o project

### Run the Project

    ./project

The program will display the main menu:

    ========================================
                 MY OS TERMINAL
    ========================================

    1. Fork + Exec Demo
    2. Pipe Demo
    3. Process Termination Demo
    4. Zombie Process Demo
    5. Orphan Process Demo
    6. Run All OS Demos
    7. Start Normal Terminal
    8. Help
    9. Exit

---

## Custom Terminal

Selecting option `7` starts the custom terminal.

The terminal displays:

    ========================================
              MY OS TERMINAL
    ========================================
    Type 'help' to see available commands.
    When you see 'myterminal$', type 'exit' to return to the menu.
    ========================================

    myterminal$

Example commands:

    myterminal$ pwd
    myterminal$ ls
    myterminal$ echo Hello
    myterminal$ cd ..
    myterminal$ ls | wc -l

To return to the main menu:

    myterminal$ exit

---

## Process Management Demonstrations

### Fork + Exec

    Parent Process
           |
         fork()
           |
       +---+---+
       |       |
     Parent   Child
                |
             execvp()
                |
         External Program

The parent waits for the child to finish.

### Pipe

The project demonstrates communication between two child processes.

Example:

          Child 1                  Child 2
             |                       |
            ls                     wc -l
             |                       ^
             |                       |
             +-------> PIPE ---------+

The output of `ls` is sent through the pipe to `wc -l`.

### Process Termination

    Parent
      |
    fork()
      |
    Child
      |
    exit(5)
      |
    waitpid()
      |
    Parent collects status

The parent retrieves the child's termination status using `waitpid()`.

### Zombie Process

    Parent
      |
    fork()
      |
    Child
      |
    exit()
      |
    Zombie Process
      |
    waitpid()
      |
    Zombie Removed

The zombie state is observed using the Linux `/proc` filesystem.

### Orphan Process

    Parent
      |
    fork()
      |
    Child
      |
    Parent terminates
      |
    Child continues
      |
    PPID changes

This demonstrates what happens when a child continues running after its original parent terminates.

---

## Process Information

The project uses the Linux `/proc` filesystem to observe process information.

Important information includes:

- Process ID (PID)
- Parent Process ID (PPID)
- Process state
- Zombie state

Example:

    /proc/<PID>/status

The process state can be used to identify the current state of a process, including the zombie state demonstrated by the project.

---

## Current Phase Status

**Phase:** Implementation, Testing and Documentation

**Status:** In Progress

### Completed

- Project topic and objective finalized
- Project structure created
- Process creation using `fork()`
- Program execution using `execvp()`
- Process synchronization using `waitpid()`
- Pipe demonstration
- Process termination demonstration
- Zombie process demonstration
- Orphan process demonstration
- Process state monitoring using `/proc`
- Custom terminal implementation
- Basic command execution
- Basic pipeline support
- GitHub repository setup
- Compilation and execution testing
- GitHub Actions build testing

### In Progress

- Final documentation
- Project presentation
- Final testing and refinement

### Upcoming

- Final project submission
- Final demonstration
- Project presentation

---

## Testing

The project has been tested in an Ubuntu/WSL environment.

The following demonstrations have been verified:

| Feature | Status |
|---|---|
| Fork + Exec | Tested |
| Pipe | Tested |
| Process Termination | Tested |
| Zombie Process | Tested |
| Orphan Process | Tested |
| Run All Demos | Tested |
| Custom Terminal | Tested |
| Basic Commands | Tested |
| Basic Pipelines | Tested |
| GCC Compilation | Tested |
| GitHub Actions Build | Tested |

---

## Expected Outcome

The project successfully demonstrates Linux process management concepts and provides a functional custom terminal for executing commands and basic pipelines.

---

## Conclusion

This project provides a practical demonstration of Linux process creation, execution, synchronization, communication, monitoring, and termination.

By implementing process management demonstrations and a custom terminal in C, the project helps understand how system calls interact with the Linux operating system and how parent and child processes are managed during their lifecycle.

The project also provides practical experience with Linux, C programming, system calls, process states, inter-process communication, and Git/GitHub-based development.

---

## Repository

GitHub Repository:

    https://github.com/geyaareddyj/KLH-CSIT-2029-2-Linux-Process-Management

---

## Team

**Jalla Geya Reddy**  
Student ID: `2520090123`

**Kamtam Priyanka**  
Student ID: `2520090001`

**Supervisor:** M. Raghupathi
