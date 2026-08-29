# Linux Process Creation, Execution and Termination System

## Team Members

| Name             | Student ID |
| ---------------  | ---------- |
| Jalla Geya Reddy | 2520090123 |
| Kamtam Priyanka  | 2520090001 |

**Supervisor:** M. Raghupathi

---

## Abstract

Processes are one of the most important concepts in an operating system because they represent programs that are currently being executed. Understanding how a process is created, executed, monitored, and terminated helps in understanding how the operating system manages system resources and provides services to applications.

This project focuses on developing a Linux-based system that demonstrates the complete lifecycle of a process. The system will use C programming and Linux/POSIX system calls such as `fork()`, `exec()`, `waitpid()`, and `exit()` to demonstrate process creation, execution, synchronization, and termination. The project will also display important process information such as Process ID (PID), Parent Process ID (PPID), process status, and the relationship between parent and child processes.

The project aims to provide a practical understanding of the process abstraction and the interaction between user programs and the operating system through system calls. It will also demonstrate how a parent process creates and controls child processes and how the operating system maintains process states during execution.

The expected outcome is a simple Linux-based process management system through which users can create processes, execute programs, observe parent-child relationships, and monitor process termination.

---

## Setup and Execution

### Requirements

* Linux operating system or Windows with WSL
* GCC compiler
* Git

### Clone the Repository

```bash
git clone https://github.com/geyaareddyj/KLH-CSIT-2029-2-Linux-Process-Management.git
cd linux-process-management
```

### Compile the Project

```bash
gcc main.c -o process_manager
```

> If the project contains multiple C source files, the compilation command will be updated accordingly.

### Run the Project

```bash
./process_manager
```

The program will demonstrate process creation, execution, synchronization, and termination using Linux/POSIX system calls.

---

## Technologies Used

* **Language:** C
* **Operating System:** Linux
* **System Calls:** `fork()`, `exec()`, `waitpid()`, `exit()`
* **Compiler:** GCC
* **Environment:** Linux / WSL

---

## Current Phase Status

**Phase:** [Current Phase]

**Status:** In Progress

### Completed

* Project topic and objective finalized
* Project abstract prepared
* Initial project structure planned

### In Progress

* Implementation of process creation and execution
* Process information and state monitoring
* Parent-child process synchronization

### Upcoming

* Process termination handling
* Testing and debugging
* Final documentation
* Demonstration and presentation

---

## Project Objective

The main objective of this project is to provide a practical demonstration of the Linux process lifecycle and show how operating systems create, execute, synchronize, monitor, and terminate processes using system calls.

---

## Project Structure

```text
linux-process-management/
│
├── main.c
├── README.md
└── ...
```

*The project structure will be updated as development progresses.*

