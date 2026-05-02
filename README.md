# xv6 Lottery Scheduler Implementation

## Overview

This project modifies the default round-robin scheduler in the xv6-riscv operating system and replaces it with a lottery scheduler. The implementation enables proportional CPU allocation based on assigned ticket counts.

## Features

- Replaced round-robin scheduling with lottery scheduling
- Added per-process ticket allocation
- Introduced probabilistic CPU selection using a pseudo-random generator
- Implemented a system call to dynamically set ticket counts
- Added runtime tracking of process execution rounds
- Provided a user-level test program to validate scheduler behavior

## Implementation Details

### 1. Process Structure Enhancements

The `struct proc` was extended with:
- `tickets`: number of lottery tickets assigned to a process
- `rounds`: number of times the process has been scheduled

Initialization:
- Default ticket count set to 10 in `allocproc()`
- Child processes inherit tickets from parent during fork

---

### 2. System Call: `settickets(int n)`

A new system call was introduced to allow user processes to set their ticket count.

- Kernel function implemented in `proc.c`
- Syscall handler added in `sysproc.c`
- Registered in `syscall.c` and assigned an ID in `syscall.h`
- Exposed to user space via `user.h` and `usys.pl`

---

### 3. Random Number Generator

A pseudo-random number generator was implemented in the kernel to support lottery selection.

- Functions: `rand()` and `do_rand()`
- Maintains internal state using a global seed

---

### 4. Lottery Scheduler

The `scheduler()` function in `proc.c` was modified as follows:

1. Compute total tickets of all RUNNABLE processes
2. Generate a random number within `[0, total_tickets - 1]`
3. Iterate through processes to identify the winning ticket
4. Select and run the corresponding process
5. Increment the process's `rounds` counter

This ensures that CPU time is distributed proportionally to ticket allocation over time.

---

### 5. Process Monitoring

The `procdump()` function was updated to display:
- Process ID
- State
- Ticket count
- Number of scheduling rounds
- Process name

This allows runtime observation of scheduler behavior using `Ctrl + P`.

---

### 6. Test Program

A user-level program `test_scheduler` was implemented to evaluate the scheduler.

Functionality:
- Accepts ticket count as input
- Calls `settickets()` to assign tickets
- Runs an infinite loop to remain schedulable

Example usage:
```sh
test_scheduler 10 &
test_scheduler 5 &
test_scheduler 2 &
```
### Dependecies

- Fedora 44
```sh
sudo dnf install gcc make qemu-system-riscv gcc-riscv64-linux-gnu
```
- For Ubuntu
```sh
sudo apt install build-essential qemu-system-misc gcc-riscv64-linux-gnu
```
