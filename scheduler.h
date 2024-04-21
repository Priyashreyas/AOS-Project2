#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

/* 
 *  This file defines the number of WORKLOADS and ENTRIES to load in, defines
 *  the 'proc_t' and 'stats_t' structs to store relevant scheduling data, and
 *  defines the prototypes used to setup and run a scheudler.
 */

#define WORKLOADS   5
#define ENTRIES     30
#define QUANTA      100

typedef struct _proc_t
{
    int _arrival_time;      // When the job arrives
    int _run_time;          // The length of the job from execution to completion
    int _priority;          // The job priority, from 1 to 4
    int _turnaround_time;   // The time from when the job is scheduled to when it is completed
    int _response_time;     // The time from when the job is scheduled to when it is executed
    int _wait_time;         // The time the job is scheduled but not running
    bool _exec;
} proc_t;

typedef struct _stats_t
{
    int _run_num;               // A job's number, from 0 to WORKLOADS
    int _avg_turnaround_time;   // The average turnaround time for the ENTRIES number of processes
    int _avg_response_time;     // The average response time for the ENTRIES number of processes
    int _avg_wait_time;         // The average wait time for the ENTRIES number of processes
    float _avg_throughput;      // The throughput of the scheduler
    int _proc_count;            // The number of completed processes.
} stats_t;

/*
 *  Function 'readSets()' opens each of the WORKLOADS number of CSV files
 *  containing the data of the processes to be scheduled.
 */
void readSets(proc_t **sets);
/*
 *  Function 'printSet()' prints the 'set' data read in from 'readSets()'. It
 *  takes a 'set' as an argument, alongside the set number 'i' and a file
 *  descriptor to output the set's process information.
 */
void printSet(proc_t* set, int setnum, FILE* fd);
/*
 *  Function 'destroySets()' deallocates the memory used to store the
 *  wordload data loaded from the CSV files.
 */
void destroySets(proc_t **sets);

/*
 *  Function 'calcStats()' calculates the average turnaround time,
 *  average wait time, average response time, and throughput of the
 *  given schedulued set. It takes the workload 'set' and corresponding
 *  'stats' struct, as well as the total run time, set number 'i', and a
 *  file descriptor to output the calculated statistics.
 */
void calcStats(proc_t *set, stats_t *stats, int time, int setnum, FILE *fd);
/*
 *  Function 'avgStats()' calculates and stores the average statistics
 *  across all WORKLOADS number of scheduled processes. It takes the 'stats'
 *  struct and a file descriptor to output the calculated average turnaround
 *  time, average wait time, average response time, and average throughput.
 */
void avgStats(stats_t *stats, FILE *fd);

#endif
