#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>

/******************************************************************************
 * Author: Ryan Morgan
 * Date: 11/15/2024
 * Class: CPE2600
 * File: pinfo.c
 ******************************************************************************/

#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <errno.h>

const char *get_sched_policy_name(int policy) {
    switch (policy) {
        case SCHED_OTHER: return "SCHED_OTHER";
        case SCHED_FIFO: return "SCHED_FIFO";
        case SCHED_RR: return "SCHED_RR";
        case SCHED_BATCH: return "SCHED_BATCH";
        case SCHED_IDLE: return "SCHED_IDLE";
        default: return "UNKNOWN";
    }
}

void print_process_info(pid_t pid) {
    int priority;
    int scheduler_policy;

    // Get priority for the process
    priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1 && errno != 0) {
        perror("getpriority");
        exit(1);
    }

    // Get scheduling policy for the process
    scheduler_policy = sched_getscheduler(pid);
    if (scheduler_policy == -1) {
        perror("sched_getscheduler");
        exit(1);
    }

    // Print process information
    printf("Process ID: %d\n", pid);
    printf("Priority: %d\n", priority);
    printf("Scheduling policy: %s\n", get_sched_policy_name(scheduler_policy));
}

int main(int argc, char *argv[]) {
    pid_t pid;

    if (argc == 1) {
        // If no PID is provided, use the current process
        pid = getpid();
    } else if (argc == 2) {
        // If a PID is provided, use the given PID
        pid = strtol(argv[1], NULL, 10);
        if (pid <= 0) {
            fprintf(stderr, "Invalid process ID: %s\n", argv[1]);
            exit(1);
        }
    } else {
        fprintf(stderr, "Usage: %s [pid]\n", argv[0]);
        exit(1);
    }

    // Print the process info
    print_process_info(pid);

    return 0;
}
