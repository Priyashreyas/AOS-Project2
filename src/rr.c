#include <stdlib.h>
#include <stdio.h>

#include "../header/queue.h"
#include "../header/algo.h"


void RoundRobin(Proc* arrivalQueue, const int numProc, Avg* avg) {
  // Initialize process queue
  Queue* readyQueue = malloc(sizeof(Queue));
  readyQueue->head = NULL;

  // Initialize queue for finished processes
  Queue* finishQueue = malloc(sizeof(Queue));
  finishQueue->head = NULL;

  int quantum = 0;
  int index = 0;
  Node* runningProc = NULL;

  while (quantum < SIM_TIME) {
    // Check if any processes arrive at the current quantum
    while (index < numProc && arrivalQueue[index].arrivalTime == quantum) {
      // Initialize new process node
      Node* newProc = malloc(sizeof(Node));
      newProc->process = &arrivalQueue[index];
      newProc->firstRun = -1;
      newProc->totalRuntime = 0;
      newProc->completionTime = -1;
      newProc->next = NULL;
      insertNode(readyQueue, newProc);
      index++;
    }

    // Check if CPU is used and if the running process has finished
    if (runningProc != NULL && ++runningProc->totalRuntime >= runningProc->process->expectedRuntime) {
      // Record quantum to get turnaround time
      runningProc->completionTime = quantum;
      insertNode(finishQueue, runningProc);
      runningProc = NULL;
    }
    // If running process has not finished, put it back into process queue
    else if (runningProc != NULL) {
      insertNode(readyQueue, runningProc);   
      runningProc = NULL;
    }

    // Check if the CPU is available and process queue has at least one process
    if (runningProc == NULL && readyQueue->head != NULL) {
      runningProc = readyQueue->head;
      readyQueue->head = readyQueue->head->next;
      if (runningProc->firstRun == -1) {
        runningProc->firstRun = quantum;
      }
      runningProc->next = NULL;
    }

    if (runningProc != NULL) {
      printf("%c", runningProc->process->name);
      //printf("Process %c is running at quantum %d!\n", runningProc->process->name, quantum);
    }
    else {
      printf("*");
      //printf("CPU is idle at time %d\n", quantum);
    }

    quantum++;
  }
 
  // Get averages
  CalcStats(avg, finishQueue, 0, -1);
  
  // Print averages
  printf("\n"); 
  printf("Average turnaround time: %f\n", avg->avgTurnaround);
  printf("Average response time: %f\n", avg->avgResponse);
  printf("Average waiting time: %f\n", avg->avgWaiting);
  printf("Throughput: %f\n", avg->throughput);
  
  // Free dynamic memory
  free(readyQueue);
  readyQueue = NULL;
  free(finishQueue);
  finishQueue = NULL;
}
