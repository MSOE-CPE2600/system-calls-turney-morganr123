/******************************************************************************
 * Author: Ryan Morgan
 * Date: 11/15/2024
 * Class: CPE2600
 * File: info.c
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>

int main() {
    struct timespec ts;
    struct utsname sys_info;
    char hostname[256];  // Buffer to hold the hostname
    int num_processors = sysconf(_SC_NPROCESSORS_ONLN);
    long page_size = getpagesize();
    long total_pages = sysconf(_SC_PHYS_PAGES);
    long available_pages = sysconf(_SC_AVPHYS_PAGES);
    long total_mem;
    long free_mem;

    // Get the current time using CLOCK_REALTIME (system-wide real time clock)
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        perror("clock_gettime");
        return 1;
    }
    // Get the current time in seconds since the epoch
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    // Calculate the number of seconds since midnight
    long seconds_since_midnight = local->tm_hour * 3600 + local->tm_min * 60 + local->tm_sec;
    // Calculate the total nanoseconds since midnight
    long nanoseconds_since_midnight = seconds_since_midnight * 1000000000L + ts.tv_nsec;
    // Get the current time using CLOCK_REALTIME (system-wide real time clock)
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        perror("clock_gettime");
        return 1;
    }
    // Get system information
    if (uname(&sys_info) == -1) {
        perror("uname");
        return 1;
    }
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        // If an error occurred, print an error message
        perror("gethostname");
        return 1;
    }
    // Check if the call succeeded
    if (num_processors == -1) {
        perror("sysconf");
        return 1;
    }
    if (page_size == -1) {
        perror("getpagesize");
        return 1;
    }
    if (total_pages == -1) {
        perror("sysconf");
        return 1;
    }
    if (available_pages == -1) {
        perror("sysconf");
        return 1;
    }

    total_mem = page_size * total_pages;
    free_mem = page_size * available_pages;

    printf("Current time of day in nanoseconds  : %ld\n", nanoseconds_since_midnight);
    printf("Network Name                        : %s\n", hostname);
    printf("Operating System                    : %s\n", sys_info.sysname);
    printf("OS Release                          : %s\n", sys_info.release);
    printf("OS Version                          : %s\n", sys_info.version);
    printf("Hardware Type                       : %s\n", sys_info.machine);
    printf("Number of processors                : %d\n", num_processors);
    printf("Amount of physical memory(in bytes) : %ld\n", total_mem);
    printf("Amount of free memory(in bytes)     : %ld\n", free_mem);

    return 0;
}