#include "scheduler.h"

void _readSet(char* file_name, proc_t* set)
{
    FILE* fin = fopen(file_name, "r");
    fscanf(fin, "%*[^\n]\n");

    for (int i = 0; i < ENTRIES; i++)
    {
        fscanf(fin, "%d,%d,%d\n",
            &set[i]._arrival_time,
            &set[i]._run_time,
            &set[i]._priority);
        set[i]._turnaround_time = 0;
        set[i]._response_time = 0;
        set[i]._wait_time = 0;
        set[i]._exec = false;
    }
    fclose(fin);
}

void readSets(proc_t** sets)
{
    char file_name[16];

    for (int i = 0; i < WORKLOADS; i++)
    {
        sets[i] = calloc(ENTRIES, sizeof(proc_t));
        sprintf(file_name, "sort/data%d.csv", i);
        _readSet(file_name, sets[i]);
    }
}

void printSet(proc_t* set, int setnum, FILE* fd)
{

    fprintf(fd, "Proc#,ArrivalTime,RunTime,Priority\n");
    for (int i = 0; i < ENTRIES; i++)
    {
        fprintf(fd, "%02d,%d,%d,%d\n", i+1,
            set[i]._arrival_time,
            set[i]._run_time,
            set[i]._priority);
    }
}

void destroySets(proc_t** sets)
{
    for (int i = 0; i < WORKLOADS; i++)
    {
        free(sets[i]);
    }
    free(sets);
}

void calcStats(proc_t *set, stats_t *stats, int time, int setnum, FILE *fd) {
    int proc_count = 0;
    for (int i = 0; i < ENTRIES; ++i) {
        /* if (set[i]._run_time == 0) { */
        if ((set[i]._arrival_time + set[i]._response_time) < QUANTA) {
            stats->_avg_turnaround_time += set[i]._turnaround_time;
            stats->_avg_response_time += set[i]._response_time;
            stats->_avg_wait_time += set[i]._wait_time;
            proc_count++;
        }
    }

    stats->_avg_turnaround_time /= proc_count;
    stats->_avg_response_time /= proc_count;
    stats->_avg_wait_time /= proc_count;
    stats->_avg_throughput = (float)proc_count / (float)time;
    stats->_proc_count = proc_count;

    fprintf(fd, "AvgTurnaroundTime,AvgResponseTime,AvgWaitTime,Throughput\n");
    fprintf(fd, "%d,%d,%d,%f\n",
        stats->_avg_turnaround_time,
        stats->_avg_response_time,
        stats->_avg_wait_time,
        stats->_avg_throughput);
}

void avgStats(stats_t *stats, FILE *fd) {
    float avg_turnaround_time   = 0.0;
    float avg_response_time     = 0.0;
    float avg_wait_time         = 0.0;
    float avg_throughput        = 0.0;

    for (int i = 0; i < WORKLOADS; ++i) {
        avg_turnaround_time += (float) stats[i]._avg_turnaround_time;
        avg_response_time   += (float) stats[i]._avg_response_time;
        avg_wait_time       += (float) stats[i]._avg_wait_time;
        avg_throughput      += (float) stats[i]._avg_throughput;
    }

    avg_turnaround_time /= (float) WORKLOADS;
    avg_response_time   /= (float) WORKLOADS;
    avg_wait_time       /= (float) WORKLOADS;
    avg_throughput      /= (float) WORKLOADS;

    fprintf(fd, "NumWorkloads,AvgTurnaroundTime,AvgResponseTime,AvgWaitTime,AvgThroughput\n");
    fprintf(fd, "%d,%f,%f,%f,%f\n",
        WORKLOADS,
        avg_turnaround_time,
        avg_response_time,
        avg_wait_time,
        avg_throughput);
}
