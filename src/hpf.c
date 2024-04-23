#include <stdlib.h>
#include <stdio.h>

#include "../header/queue.h"

const int SIM_TIME = 100;

void NonPreempHPF(Proc* arrivalQueue, const int numProc) {
  // Initialize priority queues
  Queue* priorityQueue1 = malloc(sizeof(Queue));
  priorityQueue1->head = NULL;
  Queue* priorityQueue2 = malloc(sizeof(Queue));
  priorityQueue2->head = NULL;
  Queue* priorityQueue3 = malloc(sizeof(Queue));
  priorityQueue3->head = NULL;
  Queue* priorityQueue4 = malloc(sizeof(Queue));
  priorityQueue4->head = NULL;
  
  // Initialize queue for finished processes
  Queue* finishQueue = malloc(sizeof(Queue));
  finishQueue->head = NULL;

  int quantum = 0;
  int index = 0;
  Node* runningProc = NULL;

  while (quantum < SIM_TIME) {
    // Check if any process arrives at current quantum
    while (index < numProc && arrivalQueue[index].arrivalTime == quantum) {
      // Initialize new process node
      Node* newProc = malloc(sizeof(Node));
      newProc->process = &arrivalQueue[index];
      newProc->firstRun = -1;
      newProc->totalRuntime = 0;
      newProc->completionTime = -1;
      newProc->next = NULL;
      // Place newly arrived process into the correct priority queue
      if (arrivalQueue[index].priority == 1) {
        insertNode(priorityQueue1, newProc);
      }
      else if (arrivalQueue[index].priority == 2) {
	insertNode(priorityQueue2, newProc);
      }
      else if (arrivalQueue[index].priority == 3) {
	insertNode(priorityQueue3, newProc);      
      }
      else if (arrivalQueue[index].priority == 4) {
	insertNode(priorityQueue4, newProc);
      }
      index++;
    }

    // Check if CPU is used and if the running process has finished
    if (runningProc != NULL && ++runningProc->totalRuntime >= runningProc->process->expectedRuntime) {
       // Record quantum to get turnaround time
       runningProc->completionTime = quantum;
       insertNode(finishQueue, runningProc);
       runningProc = NULL;
    }

    // Check if the CPU is available
    if (runningProc == NULL) {
      if (priorityQueue1->head != NULL) {
        runningProc = priorityQueue1->head;
	priorityQueue1->head = priorityQueue1->head->next;
      }
      else if (priorityQueue2->head != NULL) {
	runningProc = priorityQueue2->head;
	priorityQueue2->head = priorityQueue2->head->next;
      }
      else if (priorityQueue3->head != NULL) {
	runningProc = priorityQueue3->head;
	priorityQueue3->head = priorityQueue3->head->next;
      }
      else if (priorityQueue4->head != NULL) {
	runningProc = priorityQueue4->head;
	priorityQueue4->head = priorityQueue4->head->next;
      }
      // Check if the new process is running for the first time
      // If so, record quantum to get response time
      if (runningProc != NULL) {
	if (runningProc->firstRun == -1) {
	  runningProc->firstRun = quantum;
	}
	runningProc->next = NULL;
      }
    }
    if (runningProc != NULL) {
      //printf("Process %d is running at quantum %d!\n", runningProc->process->arrivalTime, quantum);
    }
    quantum++;
  }
  // Free dynamic memory
  free(priorityQueue1);
  priorityQueue1 = NULL;
  free(priorityQueue2);
  priorityQueue2 = NULL;
  free(priorityQueue3);
  priorityQueue3 = NULL;
  free(priorityQueue4);
  priorityQueue4 = NULL;
  free(finishQueue);
  finishQueue = NULL;
}

void PreempHPF(Proc* arrivalQueue, const int numProc) {
  // Initialize priority queues
  Queue* priorityQueue1 = malloc(sizeof(Queue));
  priorityQueue1->head = NULL;
  Queue* priorityQueue2 = malloc(sizeof(Queue));
  priorityQueue2->head = NULL;
  Queue* priorityQueue3 = malloc(sizeof(Queue));
  priorityQueue3->head = NULL;
  Queue* priorityQueue4 = malloc(sizeof(Queue));
  priorityQueue4->head = NULL;
  
  // Initialize queue for finished processes
  Queue* finishQueue = malloc(sizeof(Queue));
  finishQueue->head = NULL;

  int quantum = 0;
  int index = 0;
  Node* runningProc = NULL;

  while (quantum < SIM_TIME) {
    // Check if any process arrives at current quantum
    while (index < numProc && arrivalQueue[index].arrivalTime == quantum) {
      // Initialize new process node
      Node* newProc = malloc(sizeof(Node));
      newProc->process = &arrivalQueue[index];
      newProc->firstRun = -1;
      newProc->totalRuntime = 0;
      newProc->completionTime = -1;
      newProc->next = NULL;
      // Place newly arrived process into the correct priority queue
      if (arrivalQueue[index].priority == 1) {
        insertNode(priorityQueue1, newProc);
      }
      else if (arrivalQueue[index].priority == 2) {
	insertNode(priorityQueue2, newProc);
      }
      else if (arrivalQueue[index].priority == 3) {
	insertNode(priorityQueue3, newProc);      
      }
      else if (arrivalQueue[index].priority == 4) {
	insertNode(priorityQueue4, newProc);
      }
      index++;
    }

    // Check if CPU is used and if the running process has finished
    if (runningProc != NULL && ++runningProc->totalRuntime >= runningProc->process->expectedRuntime) {
      // Record quantum to get turnaround time
      runningProc->completionTime = quantum;
      insertNode(finishQueue, runningProc);
      runningProc = NULL;
    }
    // If running process has not finished, put it back into priority queue
    else if (runningProc != NULL) {
      if (runningProc->process->priority == 1) {
        insertNode(priorityQueue1, runningProc);
      }
      else if (runningProc->process->priority == 2) {
        insertNode(priorityQueue2, runningProc);
      }
      else if (runningProc->process->priority == 3) {
        insertNode(priorityQueue3, runningProc);
      }
      else if (runningProc->process->priority == 4) {
	insertNode(priorityQueue4, runningProc);
      }
      runningProc = NULL;
    }

    // Check if the CPU is available
    if (runningProc == NULL) {
      // Check priority queues from highest to lowest prioity to find ready processes
        if (priorityQueue1->head != NULL) {
          runningProc = priorityQueue1->head;
	  priorityQueue1->head = priorityQueue1->head->next;
        }
        else if (priorityQueue2->head != NULL) {
	  runningProc = priorityQueue2->head;
	  priorityQueue2->head = priorityQueue2->head->next;
        }
        else if (priorityQueue3->head != NULL) {
	  runningProc = priorityQueue3->head;
	  priorityQueue3->head = priorityQueue3->head->next;
        }
        else if (priorityQueue4->head != NULL) {
	  runningProc = priorityQueue4->head;
	  priorityQueue4->head = priorityQueue4->head->next;
        }
	if (runningProc != NULL) {
	  // Check if the new process is running for the first time
          // If so, record quantum to get response time
	  if (runningProc->firstRun == -1) {
	    runningProc->firstRun = quantum;
	  }
	  runningProc->next = NULL;
	}
      }
    if (runningProc != NULL) {
      printf("Process %d is running at quantum %d!\n", runningProc->process->arrivalTime, quantum);
    }
    else {
      printf("CPU is idle at time %d\n", quantum);
    }
    quantum++;
  }
  // Free dynamic memory
  free(priorityQueue1);
  priorityQueue1 = NULL;
  free(priorityQueue2);
  priorityQueue2 = NULL;
  free(priorityQueue3);
  priorityQueue3 = NULL;
  free(priorityQueue4);
  priorityQueue4 = NULL;
  free(finishQueue);
  finishQueue = NULL;
}


