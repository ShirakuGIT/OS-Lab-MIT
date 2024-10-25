# Disk Scheduling and Memory Management Algorithms

### Overview

This repository contains C programs implementing various fundamental **disk scheduling** and **memory management** algorithms. These algorithms are commonly taught in operating systems courses and are crucial for efficient process and memory management in systems.

### Algorithms Included

1. **Disk Scheduling Algorithms:**
   - **FCFS (First-Come-First-Serve)**
   - **SSTF (Shortest Seek Time First)**
   - **SCAN (Elevator Algorithm)**
   - **C-SCAN (Circular SCAN)**
   - **C-LOOK (Circular LOOK)**
   
2. **Page Replacement Algorithms:**
   - **FIFO (First In, First Out)**
   - **Optimal**
   - **LRU (Least Recently Used)**

3. **CPU Scheduling Algorithms:**
   - **Round Robin**
   - **Shortest Job First (SJF)** (Preemptive and Non-Preemptive)
   - **Priority Scheduling** (Non-Preemptive)
   - **Preemptive SJF**
   
4. **Producer-Consumer Problem:**
   - **Using Semaphores**

5. **Reader's Writer's**
   - **Using Bounded Buffer**
   
5. **Banker's Algorithm for Deadlock Avoidance**

### Background

In operating systems, **scheduling algorithms** are used to decide the order in which processes or data requests are handled. The goal is to ensure fairness and minimize the time taken to execute all requests. For **disk scheduling**, we focus on minimizing the seek time of a disk arm, while for **memory management** and **CPU scheduling**, the aim is efficient usage of memory and processor resources.

### Simplified Pseudocode

The pseudocode mimics the logic of the C code but focuses on simplicity and clarity.

---

### **Disk Scheduling Algorithms**

#### SSTF (Shortest Seek Time First)

- Finds the request closest to the current head position.
- Always chooses the request that results in the smallest movement of the disk arm.

##### Pseudocode:
```
function SSTF(requests, head):
    visited = [false for each request]
    for each request:
        find closest unvisited request
        move head to request, mark visited
        calculate total seek time
```

#### SCAN (Elevator Algorithm)

- Moves the disk arm towards one end, servicing requests along the way, then reverses direction at the boundary.

##### Pseudocode:
```
function SCAN(requests, head, direction):
    while moving to boundary:
        service requests in path
    reverse direction, service remaining requests
```

#### C-SCAN (Circular SCAN)

- Like SCAN, but the arm jumps back to the start of the disk without servicing requests when it reaches the end.

##### Pseudocode:
```
function C-SCAN(requests, head):
    service requests from head to end
    jump to start and service remaining requests
```

---

### **Page Replacement Algorithms**

#### FIFO (First In First Out)

- Replaces the oldest page in memory with the new page.
  
##### Pseudocode:
```
function FIFO(pages, frames):
    for each page:
        if page not in frames:
            replace oldest page in frames
            update total page faults
```

#### Optimal Page Replacement

- Replaces the page that will not be used for the longest period of time in the future.

##### Pseudocode:
```
function Optimal(pages, frames):
    for each page:
        if page not in frames:
            replace page with farthest future use
            update total page faults
```

#### LRU (Least Recently Used)

- Replaces the least recently used page in memory.

##### Pseudocode:
```
function LRU(pages, frames):
    for each page:
        if page not in frames:
            replace least recently used page
            update total page faults
```

---

### **CPU Scheduling Algorithms**

#### Round Robin

- Each process is assigned a fixed time slice (quantum). After the time slice expires, the process is moved to the back of the queue.

##### Pseudocode:
```
function RoundRobin(processes, quantum):
    while processes remain:
        for each process:
            execute for quantum time
            if process not finished, add back to queue
```

#### Shortest Job First (SJF) - Preemptive and Non-Preemptive

- Selects the process with the shortest remaining execution time.

##### Pseudocode:
```
function SJF(processes):
    for each process:
        select process with shortest burst time
        execute process
```

---

### **Producer-Consumer Problem (Using Semaphores)**

- Simulates the producer-consumer problem using semaphores to synchronize access to shared resources (buffer).

##### Pseudocode:
```
function Producer():
    wait(empty), wait(mutex)
    add item to buffer
    signal(mutex), signal(full)

function Consumer():
    wait(full), wait(mutex)
    remove item from buffer
    signal(mutex), signal(empty)
```

---

### **Banker's Algorithm (Deadlock Avoidance)**

- The Banker's algorithm ensures that a system remains in a safe state and avoids deadlocks by simulating resource allocation for processes.

##### Pseudocode:
```
function BankersAlgorithm():
    for each process:
        check if resources are available
        if yes, allocate resources
        else wait for resources
```

---
