/*
Here's a simple Linux C program that helps students understand the short-term, mid-term,
and long-term schedulers in an operating system. The program uses process creation (fork),
process suspension (sleep), and process termination (exit) to mimic how schedulers manage
different processes.

Explanation:
Long-Term Scheduler – Decides when a new process is admitted into the system (simulated with fork()).
Mid-Term Scheduler – Swaps processes in and out of memory (simulated with sleep() to indicate suspension).
Short-Term Scheduler – Decides which process runs next (simulated with waitpid() to allow process execution).

How it Works:
Long-Term Scheduler: fork() simulates admitting new processes.
Mid-Term Scheduler: kill(pid2, SIGSTOP) simulates swapping a process out of memory.
Mid-Term Scheduler: kill(pid2, SIGCONT) simulates swapping a process in memory.
Short-Term Scheduler: waitpid() ensures CPU schedules processes.

Here’s the C code for Linux:
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void run_process(const char *name, int duration) {
    printf("Process %s started and running for %d seconds.\n", name, duration);
    for (int i = 1; i <= duration; i++) {
        printf("Process %s running... %d second(s) elapsed.\n", name, i);
        sleep(1);
    }
    printf("Process %s finished execution.\n", name);
}

int main() {
    pid_t pid1, pid2, pid3;

    printf("=== OS Scheduler Simulation ===\n");

    // Long-Term Scheduler: Admitting new processes
    printf("Long-Term Scheduler: Admitting Process A, B, and C into the system...\n");

    pid1 = fork();
    if (pid1 == 0) {
        run_process("A", 3);
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        run_process("B", 8); // B runs longer so that we can suspend it
        exit(0);
    }

    pid3 = fork();
    if (pid3 == 0) {
        run_process("C", 4);
        exit(0);
    }

    sleep(2);  // Let processes start execution

    // Mid-Term Scheduler: Suspending Process B
    printf("Mid-Term Scheduler: Suspending Process B temporarily (Swapping Out)...\n");
    kill(pid2, SIGSTOP);  // Pause Process B
    sleep(3);  // Process B stays swapped out for 3 seconds

    // Resuming Process B
    printf("Mid-Term Scheduler: Resuming Process B (Swapping In)...\n");
    kill(pid2, SIGCONT);  // Resume Process B

    // Short-Term Scheduler: Managing execution order
    printf("Short-Term Scheduler: Managing process execution order...\n");
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    printf("All processes completed.\n");
    return 0;
}
/*
Output:
localhost:/home/alphapeeler/OsSp25/week04/CPU_Scheduler_Simulation # gcc schedulers01.c -o schedulers01.o
localhost:/home/alphapeeler/OsSp25/week04/CPU_Scheduler_Simulation # ./schedulers01.o 
=== OS Scheduler Simulation ===
Long-Term Scheduler: Admitting Process A, B, and C into the system...
Process A started and running for 3 seconds.
Process A running... 1 second(s) elapsed.
Process C started and running for 4 seconds.
Process C running... 1 second(s) elapsed.
Process B started and running for 8 seconds.
Process B running... 1 second(s) elapsed.
Process A running... 2 second(s) elapsed.
Process C running... 2 second(s) elapsed.
Process B running... 2 second(s) elapsed.
Mid-Term Scheduler: Suspending Process B temporarily (Swapping Out)...
Process A running... 3 second(s) elapsed.
Process C running... 3 second(s) elapsed.
Process A finished execution.
Process C running... 4 second(s) elapsed.
Process C finished execution.
Mid-Term Scheduler: Resuming Process B (Swapping In)...
Short-Term Scheduler: Managing process execution order...
Process B running... 3 second(s) elapsed.
Process B running... 4 second(s) elapsed.
Process B running... 5 second(s) elapsed.
Process B running... 6 second(s) elapsed.
Process B running... 7 second(s) elapsed.
Process B running... 8 second(s) elapsed.
Process B finished execution.
All processes completed.
localhost:/home/alphapeeler/OsSp25/week04/CPU_Scheduler_Simulation # 

*/