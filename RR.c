#include "scheduler.h"


int RR(proc_t* set, int setnum, FILE *fd, int timelimit) {
    /*
     *  The preemptive Round Robin scheduling algorithm runs each scheduled
     *  processes in single quanta increments, rotating between arrived and
     *  incomplete processes. When new processes arrive, they take precedence
     *  over previously scheduled processes and are next to run.
     */
    int start   = 0;
    int end     = 1;
    int current = 0;
    int qlen    = 1;
    int time    = set[start]._arrival_time;

    fprintf(fd, "Time,ProcNum\n");
    while (start < ENTRIES) {
        while (set[end]._arrival_time <= time) {
            ++end;
            ++qlen;
            current = end - 1;      // Preemptive scheduling has newly scheduled jobs run next
        }

        for (int i = start; i < end; i++) {
            if ((i == current) && (set[i]._run_time != 0)) {
                set[i]._run_time--;
                set[i]._turnaround_time++;
                if (set[i]._exec == false) {
                    set[i]._exec = true;
                }
                fprintf(fd, "%3d,%2d\n", time, current);
            } else if (set[i]._run_time != 0) {
                set[i]._wait_time++;
                set[i]._turnaround_time++;
                if (set[i]._exec == false)
                    set[i]._response_time++;
            }
        }

        if (set[start]._run_time == 0) {
            if (current == start)
                current++;
            ++start;
        } else {
            current = (current + 1) % qlen + start;
        }
        ++time;
        /* if (time == timelimit) */
        /*     break; */
    }
    return time;
}

int main() {
    /*
     *  Variable 'sets' is an array of arrays. There are a WORKLOADS number of
     *  'set' within 'sets', each of which stores an ENTRIES number of processes
     *  to be scheduled. Each process is associated with their:
            Arrival Time
            Run Time
            Priority
     */
    proc_t **sets = calloc(WORKLOADS, sizeof(proc_t*));
    /*
     *  Variable 'stats' is an array of statistics, one for each workload (set
     *  of process data). These statistics include:
     *      Average Turnaround Time
     *      Average Response Time
     *      Average Wait Time
     *      Throughput
     *  and describe these respective characteristcs of the ENTRIES number of
     *  scheduled processes in the WORKLOADS number of 'sets'.
     */
    stats_t *stats = calloc(WORKLOADS, sizeof(stats_t));
    int time;

    readSets(sets);

    for (int i = 0; i < WORKLOADS; ++i) {
        time = RR(sets[i], i, stdout, QUANTA);
        calcStats(sets[i], &stats[i], time, i, stdout);
    }
    destroySets(sets);

    printf("\n//Statistics for all 5 workloads:\n");
    avgStats(stats, stdout);
    free(stats);

    return 0;
}
