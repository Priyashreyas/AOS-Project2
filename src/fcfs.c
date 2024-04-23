#include <stdio.h>
#include <stdlib.h>

#include "../header/queue.h"
#include "../header/algo.h"

void FirstComeFirstServe(Proc* processes, const int num_procs) {
    Queue* queue = malloc(sizeof(Queue));
    queue->head = NULL;

    int quantum = 0;
    Node* runningProc = NULL;

    
    while (queue->head != NULL || runningProc != NULL || quantum < SIM_TIME) {
        for (int i = 0; i < num_procs; i++) {
            if (processes[i].arrivalTime == quantum) {
                Node* newProc = (Node*)malloc(sizeof(Node));
                newProc->process = &processes[i];
                newProc->firstRun = -1;
                newProc->totalRuntime = 0;
                newProc->completionTime = -1;
                newProc->next = NULL;
                insertNode(queue, newProc);
            }
        }

        // Check if the CPU is idle and assign the next process
        if (runningProc == NULL) {
            runningProc = popNode(queue);
            if (runningProc != NULL && runningProc->firstRun == -1) {
                runningProc->firstRun = quantum;
            }
        }

        // Run the current process
        if (runningProc != NULL) {
            runningProc->totalRuntime++;
            // Check if the process has completed its execution
            if (runningProc->totalRuntime == runningProc->process->expectedRuntime) {
                runningProc->completionTime = quantum;
                printf("CPU is being used by Process %d at quantum %d. Remaining Time: %d\n",
                    runningProc->process->arrivalTime, quantum,
                    runningProc->process->expectedRuntime - runningProc->totalRuntime);
                free(runningProc); 
                runningProc = NULL;
            } else {
                printf("CPU is being used by Process %d at quantum %d. Remaining Time: %d\n",
                   runningProc->process->arrivalTime, quantum,
                   runningProc->process->expectedRuntime - runningProc->totalRuntime);

            }
        } else {
            printf("CPU is idle at quantum %d.\n", quantum);
        }

        quantum++;
    }

    // Free any remaining nodes in the queue
    while ((runningProc = popNode(queue)) != NULL) {
        free(runningProc);
    }
    free(queue);
}
