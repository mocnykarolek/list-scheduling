# Multiprocessor Task Scheduling Simulator

A C++ implementation of task scheduling algorithms for distributing jobs across multiple processors.

## Features

- Basic List Scheduling (BLS)
- Longest Processing Time First (LPT)
- Shortest Processing Time First (SPT)
- Dynamic task insertion and removal
- Custom Quicksort implementation
- Dynamically resized arrays and linked lists
- Manual memory management using `malloc`, `realloc`, and `free`
- Memory manipulation using `memcpy` and `memmove`

## Technologies

- C++
- Scheduling Algorithms
- Pointers and Dynamic Memory Allocation
- Data Structures and Algorithms

## How It Works

The program simulates task allocation across multiple processors using different scheduling strategies.

It calculates two scheduling metrics:

- **Cmax** — maximum completion time across all processors (makespan)
- **SigmaC** — sum of task completion times

Users can dynamically add or remove tasks and compare scheduling results.

## Compilation

```bash
g++ -std=c++11 taskscheduling.cpp -o taskscheduling
```

## Execution

```bash
./taskscheduling
```

## Purpose

This project demonstrates scheduling algorithm implementation, manual memory management, dynamic data structures, and algorithmic problem-solving in C++.
