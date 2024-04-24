#include <stdlib.h>
#include <stdio.h>

#include "../header/queue.h"
#include "../header/algo.h"

void NonPreempHPF(Proc* arrivalQueue, const int numProc, Avg* avg) {
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

  while (quantum < SIM_TIME || runningProc != NULL) {
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
       if (quantum >= SIM_TIME) {
         break;
       }
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
      printf("%c", runningProc->process->name);
      //printf("Process %c is running at quantum %d!\n", runningProc->process->name, quantum);
    }
    else {
      printf("*");
    }
    quantum++;
  }

  printf("\n");
  // Calculate and print averages
  for (int prior = 1; prior <= 4; ++prior) {
    CalcStats(avg, finishQueue, 1, prior);
    if (prior == 1) {
      printf("Average turnaround time (P1): %f\n", avg->avgTurnaround);
      printf("Average response time (P1): %f\n", avg->avgResponse);
      printf("Average waiting time (P1): %f\n", avg->avgWaiting);
      printf("Throughput (P1): %f\n\n", avg->throughput);
      avg->turnaroundP1 = avg->avgTurnaround;
      avg->responseP1 = avg->avgResponse;
      avg->waitingP1 = avg->avgWaiting;
      avg->throughputP1 = avg->throughput;
      avg->cntP1 = avg->cnt;
    }
    else if (prior == 2) {
      printf("Average turnaround time (P2): %f\n", avg->avgTurnaround);
      printf("Average response time (P2): %f\n", avg->avgResponse);
      printf("Average waiting time (P2): %f\n", avg->avgWaiting);
      printf("Throughput (P2): %f\n\n", avg->throughput);
      avg->turnaroundP2 = avg->avgTurnaround;
      avg->responseP2 = avg->avgResponse;
      avg->waitingP2 = avg->avgWaiting;
      avg->throughputP2 = avg->throughput;
      avg->cntP2 = avg->cnt;
    }
    else if (prior == 3) {
      printf("Average turnaround time (P3): %f\n", avg->avgTurnaround);
      printf("Average response time (P3): %f\n", avg->avgResponse);
      printf("Average waiting time (P3): %f\n", avg->avgWaiting);
      printf("Throughput (P3): %f\n\n", avg->throughput);
      avg->turnaroundP3 = avg->avgTurnaround;
      avg->responseP3 = avg->avgResponse;
      avg->waitingP3 = avg->avgWaiting;
      avg->throughputP3 = avg->throughput;
      avg->cntP3 = avg->cnt;
    }
    else if (prior == 4) {
      printf("Average turnaround time (P4): %f\n", avg->avgTurnaround);
      printf("Average response time (P4): %f\n", avg->avgResponse);
      printf("Average waiting time (P4): %f\n", avg->avgWaiting);
      printf("Throughput (P4): %f\n\n", avg->throughput);
      avg->turnaroundP4 = avg->avgTurnaround;
      avg->responseP4 = avg->avgResponse;
      avg->waitingP4 = avg->avgWaiting;
      avg->throughputP4 = avg->throughput;
      avg->cntP4 = avg->cnt;
    }
  }

  CalcStats(avg, finishQueue, 0, -1);
  printf("Average turnaround time: %f\n", avg->avgTurnaround);
  printf("Average response time: %f\n", avg->avgResponse);
  printf("Average waiting time: %f\n", avg->avgWaiting);
  printf("Throughput: %f\n", avg->throughput);

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

void PreempHPF(Proc* arrivalQueue, const int numProc, Avg* avg) {
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
      printf("%c", runningProc->process->name);
      //printf("Process %c is running at quantum %d!\n", runningProc->process->name, quantum);
    }
    else {
      printf("*");
      //printf("CPU is idle at time %d\n", quantum);
    }
    quantum++;
  }

  printf("\n"); 
  // Calculate and print averages
  for (int prior = 1; prior <= 4; ++prior) {
    CalcStats(avg, finishQueue, 1, prior);
    if (prior == 1) {
      printf("Average turnaround time (P1): %f\n", avg->avgTurnaround);
      printf("Average response time (P1): %f\n", avg->avgResponse);
      printf("Average waiting time (P1): %f\n", avg->avgWaiting);
      printf("Throughput (P1): %f\n\n", avg->throughput);
      avg->turnaroundP1 = avg->avgTurnaround;
      avg->responseP1 = avg->avgResponse;
      avg->waitingP1 = avg->avgWaiting;
      avg->throughputP1 = avg->throughput;
      avg->cntP1 = avg->cnt;
    }
    else if (prior == 2) {
      printf("Average turnaround time (P2): %f\n", avg->avgTurnaround);
      printf("Average response time (P2): %f\n", avg->avgResponse);
      printf("Average waiting time (P2): %f\n", avg->avgWaiting);
      printf("Throughput (P2): %f\n\n", avg->throughput);
      avg->turnaroundP2 = avg->avgTurnaround;
      avg->responseP2 = avg->avgResponse;
      avg->waitingP2 = avg->avgWaiting;
      avg->throughputP2 = avg->throughput;
      avg->cntP2 = avg->cnt;
    }
    else if (prior == 3) {
      printf("Average turnaround time (P3): %f\n", avg->avgTurnaround);
      printf("Average response time (P3): %f\n", avg->avgResponse);
      printf("Average waiting time (P3): %f\n", avg->avgWaiting);
      printf("Throughput (P3): %f\n\n", avg->throughput);
      avg->turnaroundP3 = avg->avgTurnaround;
      avg->responseP3 = avg->avgResponse;
      avg->waitingP3 = avg->avgWaiting;
      avg->throughputP3 = avg->throughput;
      avg->cntP3 = avg->cnt;
    }
    else if (prior == 4) {
      printf("Average turnaround time (P4): %f\n", avg->avgTurnaround);
      printf("Average response time (P4): %f\n", avg->avgResponse);
      printf("Average waiting time (P4): %f\n", avg->avgWaiting);
      printf("Throughput (P4): %f\n\n", avg->throughput);
      avg->turnaroundP4 = avg->avgTurnaround;
      avg->responseP4 = avg->avgResponse;
      avg->waitingP4 = avg->avgWaiting;
      avg->throughputP4 = avg->throughput;
      avg->cntP4 = avg->cnt;
    }
  }

  CalcStats(avg, finishQueue, 0, -1);
  printf("Average turnaround time: %f\n", avg->avgTurnaround);
  printf("Average response time: %f\n", avg->avgResponse);
  printf("Average waiting time: %f\n", avg->avgWaiting);
  printf("Throughput: %f\n", avg->throughput);
 
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


