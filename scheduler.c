#include "scheduler.h"


int scheduler(proc_t* set, int setnum, FILE *fd) {
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
        scheduler(sets[i], i, stdout);
        calcStats(sets[i], &stats[i], time, i, stdout);
    }
    destroySets(sets);

    printf("\n//Statistics for all 5 workloads:\n");
    avgStats(stats, stdout);
    free(stats);

    return 0;
}
