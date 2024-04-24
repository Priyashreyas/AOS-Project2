// #include <stdio.h>
// #include <stdlib.h>
// #include "../header/queue.h"

// const int SIM_TIME = 100;

// void ShortestRemainingTimeFirst(Proc* arrivalQueue, const int numProc) {
//     Queue* readyQueue = malloc(sizeof(Queue));
//     readyQueue->head = NULL;

//     Queue* finishQueue = malloc(sizeof(Queue));
//     finishQueue->head = NULL;

//     int quantum = 0;
//     Node* runningProc = NULL;

//     int queueSize=0;

//     while (readyQueue->head != NULL || runningProc != NULL || quantum < SIM_TIME) {
//         // Enqueue any processes that arrive at the current quantum
//         for (int i = 0; i < numProc; i++) {
//             if (arrivalQueue[i].arrivalTime == quantum) {
//                 Node* newProc = malloc(sizeof(Node));
//                 newProc->process = &arrivalQueue[i];
//                 newProc->firstRun = -1;
//                 newProc->totalRuntime = 0;
//                 newProc->completionTime = -1;
//                 newProc->next = NULL;
//                 insertNode(readyQueue, newProc);
//                 queueSize++;
//             }
//         }

//         vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//         if (runningProc == NULL || (readyQueue->head != NULL && runningProc->process->expectedRuntime - runningProc->totalRuntime > readyQueue->head->process->expectedRuntime - readyQueue->head->totalRuntime)) {
//             if (runningProc != NULL) {
//                 insertNode(readyQueue, runningProc);
//                 queueSize++;
//             }
//             runningProc = popNode(readyQueue);
//             queueSize--;
//             if (runningProc && runningProc->firstRun == -1) {
//                 runningProc->firstRun = quantum;
//             }
//         }

//         // Execute the running process
//         if (runningProc != NULL) {
//             printf("CPU is being used by Process %d at quantum %d. Remaining Time: %d\n",
//                    runningProc->process->arrivalTime, quantum,
//                    runningProc->process->expectedRuntime - runningProc->totalRuntime - 1);
//             runningProc->totalRuntime++;
//             if (runningProc->totalRuntime == runningProc->process->expectedRuntime) {
//                 runningProc->completionTime = quantum;
//                 insertNode(finishQueue, runningProc);
//                 runningProc = NULL;  // Clear the running process
//             }
//         } else {
//             printf("CPU is idle at quantum %d\n", quantum);
//         }

//         // Increment quantum at the end of the loop iteration
//         quantum++;  
//     }

//     // Clean up
//     free(readyQueue);
//     free(finishQueue);
// }
#include <stdio.h>
#include <stdlib.h>
#include "../header/queue.h"
#include "../header/algo.h"

Node* createNode(Proc* proc) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->process = proc;
    newNode->next = NULL;
    newNode->totalRuntime = 0;
    newNode->firstRun = -1;
    newNode->completionTime = -1;
    return newNode;
}

// Find middle node
Node* getMiddle(Node* head) {
    if (!head) return head;
    Node* slow = head, *fast = head;

    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Merge nodes based on Reamaining Run Time
Node* merge(Node* a, Node* b) {
    Node dummy, *tail = &dummy;
    dummy.next = NULL;

    while (a && b) {
        if (a->process->expectedRuntime - a->totalRuntime <= b->process->expectedRuntime - b->totalRuntime) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}

// Merge Sort implementation
Node* mergeSort(Node* head) {
    if (!head || !head->next) return head;

    Node* middle = getMiddle(head);
    Node* nextOfMiddle = middle->next;
    middle->next = NULL;

    Node* left = mergeSort(head);
    Node* right = mergeSort(nextOfMiddle);

    return merge(left, right);
}

void ShortestRemainingTimeFirst(Proc* arrivalQueue, const int numProc) {
    Queue* readyQueue = malloc(sizeof(Queue));
    readyQueue->head = NULL;

    Queue* finishQueue = malloc(sizeof(Queue));
    finishQueue->head = NULL;

    int quantum = 0;
    Node* runningProc = NULL;

    while (quantum < SIM_TIME || runningProc != NULL) {
        // Enqueue any processes that arrive at the current quantum
        if (quantum < SIM_TIME) {
            for (int i = 0; i < numProc; i++) {
                if (arrivalQueue[i].arrivalTime == quantum) {
                    Node* newProc = createNode(&arrivalQueue[i]);
                    newProc->next = readyQueue->head;
                    readyQueue->head = newProc;
                }
            }
        
        // Sort the ready queue every time a process arrives
        readyQueue->head = mergeSort(readyQueue->head);
        }

        

        // Check and manage running and preempting processes
        if (!runningProc || (readyQueue->head && runningProc->totalRuntime < runningProc->process->expectedRuntime && (runningProc->process->expectedRuntime - runningProc->totalRuntime > readyQueue->head->process->expectedRuntime - readyQueue->head->totalRuntime))) {
            if (runningProc && runningProc->totalRuntime < runningProc->process->expectedRuntime) {
                runningProc->next = readyQueue->head; // Reinsert the currently running process back into the queue
                readyQueue->head = runningProc;
                readyQueue->head = mergeSort(readyQueue->head); // Sort again after insertion
            }
            runningProc = popNode(readyQueue); // Always pick the head as the next process to run
        }

        // Execute the running process
        if (runningProc) {
            if (runningProc->firstRun == -1) {
                runningProc->firstRun = quantum;
            }
	    printf("%c", runningProc->process->name);
            /*printf("CPU is being used by Process %c at quantum %d. Remaining Time: %d\n",
                   runningProc->process->name, quantum,
                   runningProc->process->expectedRuntime - runningProc->totalRuntime);*/
            runningProc->totalRuntime++;
            if (runningProc->totalRuntime >= runningProc->process->expectedRuntime) {
                runningProc->completionTime = quantum;
                runningProc->next = finishQueue->head;
                finishQueue->head = runningProc;
                runningProc = NULL; 
            }
        } else {
	    printf("*");
            //printf("CPU is idle at quantum %d\n", quantum);
        }

        // Increment quantum at the end of the loop iteration
        quantum++;
    }

    // Clean up
    free(readyQueue);
    free(finishQueue);
}
