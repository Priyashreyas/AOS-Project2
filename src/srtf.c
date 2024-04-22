#include <stdio.h>
#include <stdlib.h>
#include "../header/queue.h"

const int SIM_TIME = 100;

void ShortestRemainingTimeFirst(Proc* arrivalQueue, const int numProc) {
    Queue* readyQueue = malloc(sizeof(Queue));
    readyQueue->head = NULL;

    Queue* finishQueue = malloc(sizeof(Queue));
    finishQueue->head = NULL;

    int quantum = 0;
    Node* runningProc = NULL;

    while (readyQueue->head != NULL || runningProc != NULL || quantum < SIM_TIME) {
        // Enqueue any processes that arrive at the current quantum
        for (int i = 0; i < numProc; i++) {
            if (arrivalQueue[i].arrivalTime == quantum) {
                Node* newProc = malloc(sizeof(Node));
                newProc->process = &arrivalQueue[i];
                newProc->firstRun = -1;
                newProc->totalRuntime = 0;
                newProc->completionTime = -1;
                newProc->next = NULL;
                insertNode(readyQueue, newProc);
            }
        }

        // Check and manage running and preempting processes
        if (runningProc == NULL || (readyQueue->head != NULL && runningProc->process->expectedRuntime - runningProc->totalRuntime > readyQueue->head->process->expectedRuntime - readyQueue->head->totalRuntime)) {
            if (runningProc != NULL) {
                insertNode(readyQueue, runningProc);
            }
            runningProc = popNode(readyQueue);
            if (runningProc && runningProc->firstRun == -1) {
                runningProc->firstRun = quantum;
            }
        }

        // Execute the running process
        if (runningProc != NULL) {
            printf("CPU is being used by Process %d at quantum %d. Remaining Time: %d\n",
                   runningProc->process->arrivalTime, quantum,
                   runningProc->process->expectedRuntime - runningProc->totalRuntime - 1);
            runningProc->totalRuntime++;
            if (runningProc->totalRuntime == runningProc->process->expectedRuntime) {
                runningProc->completionTime = quantum;
                insertNode(finishQueue, runningProc);
                runningProc = NULL;  // Clear the running process
            }
        } else {
            printf("CPU is idle at quantum %d\n", quantum);
        }

        // Increment quantum at the end of the loop iteration
        quantum++;  
    }

    // Clean up
    free(readyQueue);
    free(finishQueue);
}
