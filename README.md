# Linux Process Management and Custom OS Terminal

## Team Members

| Name | Student ID |
|---|---|
| Jalla Geya Reddy | 2520090123 |
| Kamtam Priyanka | 2520090001 |

**Supervisor:** M. Raghupathi

---

## Abstract

Processes are one of the most important concepts in an operating system because they represent programs that are currently being executed. Understanding how processes are created, executed, synchronized, and terminated helps in understanding how an operating system manages system resources.

This project focuses on developing a Linux-based process management system using C programming and Linux/POSIX system calls. The system demonstrates important process management concepts including process creation using `fork()`, program execution using `exec()`, process synchronization using `waitpid()`, inter-process communication using `pipe()`, and process termination using `exit()`.

The project also demonstrates important process states and relationships, including zombie and orphan processes. Process information such as Process ID (PID), Parent Process ID (PPID), and process state is displayed using the Linux `/proc` filesystem.

In addition to the process demonstrations, the project provides a simple custom terminal called **MY OS TERMINAL**. The terminal supports basic commands such as `pwd`, `ls`, `cd`, and `echo`, along with external command execution and basic pipelines.

The project provides a practical understanding of the Linux process lifecycle and demonstrates how user programs interact with the operating system through system calls.

---

## Project Objective

The main objective of this project is to provide a practical demonstration of Linux process management and the complete process lifecycle.

The project demonstrates:

- Process creation using `fork()`
- Program execution using `exec()`
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

### 1. Fork and Exec Demonstration

Demonstrates how a parent process creates a child process using `fork()` and how the child executes another program using `exec()`.

### 2. Pipe Demonstration

Demonstrates inter-process communication using `pipe()`.

Example:

```text
ls | wc -l
