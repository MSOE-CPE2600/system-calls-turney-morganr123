/******************************************************************************
 * Author: Ryan Morgan
 * Date: 11/15/2024
 * Class: CPE2600
 * File: pmod.c
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]) {
    // Modify the process's priority (reduce by 10)
    if (nice(10) == -1) {
        perror("Failed to change priority");
        return 1;
    }

    // Set up the timespec for nanosleep (1,837,272,638 nanoseconds)
    struct timespec req, rem;
    req.tv_sec = 1;  // 1 second
    req.tv_nsec = 837272638;  // 1,837,272,638 nanoseconds

    // Sleep for the specified time
    if (nanosleep(&req, &rem) == -1) {
        perror("nanosleep failed");
        return 1;
    }

    // Print a goodbye message
    printf("Goodbye!\n");

    return 0;
}