#include <stdlib.h>
#include <stdio.h>

#include "../header/queue.h"
#include "../header/algo.h"


int runTimeComparator(const void * p1, const void * p2) {
	Proc * proc1 = (Proc *) p1;
	Proc * proc2 = (Proc *) p2;
	if(proc1->expectedRuntime < proc2->expectedRuntime) {
		return -1;
	} else {
		return 1;
	}
}

int getQueueSize(Queue* queue) {
	int qSize = 0;
	Node* temp = queue->head;
	while (temp != NULL) {
		qSize++;
		temp = temp->next;
	}
	return qSize;
}

void clearQueue(Queue* queue) {
    while (queue->head != NULL) {
        Node* temp = queue->head;
        queue->head = queue->head->next;
        free(temp);
    }
}

void ShortestJobFirst(Proc* arrivalQueue, const int num_proc) {
    
    Queue* readyQueue = malloc(sizeof(Queue));
    readyQueue->head = NULL;

    Queue* finishQueue = malloc(sizeof(Queue));
    finishQueue->head = NULL;

    int quantum = 0;
    int index = 0;
    Node* runningProc = NULL;
    
    while (quantum < SIM_TIME) {
        // Check if any process arrives at the current quantum

        while (index < num_proc && arrivalQueue[index].arrivalTime == quantum) {
           // Initialize a new process node
            
	    Node* newProc = malloc(sizeof(Node));
            newProc->process = &arrivalQueue[index];
            newProc->firstRun = -1;
            newProc->totalRuntime = 0;
            newProc->completionTime = -1;
            newProc->next = NULL;
            // Insert the newly arrived process into the ready queue
            insertNode(readyQueue, newProc);
            index++;
        }
        //sort ready queue based on runtime if new processes arrive
        if (index > 0) {
            //convert ready queue to array for sorting using qsort
            int queueSize = getQueueSize(readyQueue);
            Proc *procArray = malloc(queueSize * sizeof(Proc));
            Node *current = readyQueue->head;
            int i = 0;
            while (current != NULL) {
                procArray[i] = *(current->process);
                current = current->next;
                i++;
            }
            
            qsort(procArray, queueSize,sizeof(Proc),runTimeComparator);
            //rebuild the ready queue with sorted processes
            clearQueue(readyQueue);
            for (int j = 0; j < queueSize; j++) {
                Node *newNode = malloc(sizeof(Node));
                Proc* p = malloc(sizeof(Proc));
		p->arrivalTime = procArray[j].arrivalTime;
		p->expectedRuntime = procArray[j].expectedRuntime;
		p->priority = procArray[j].priority;
		newNode->process = p;
                newNode->firstRun = -1;
                newNode->totalRuntime = 0;
                newNode->completionTime = -1;
                newNode->next = NULL;
                insertNode(readyQueue, newNode);
            }
            free(procArray);
        }
        // Check if the CPU is idle and assign the next process
        if (runningProc == NULL && readyQueue->head != NULL) {
            runningProc = popNode(readyQueue);
            // Check if the process is running for the first time
            if (runningProc->firstRun == -1) {
                runningProc->firstRun = quantum;
            }
        }

         // Run the current process
        if (runningProc != NULL) {
            runningProc->totalRuntime++;
            // Check if the process has completed its execution
            if (runningProc->totalRuntime == runningProc->process->expectedRuntime) {
                runningProc->completionTime = quantum;
                // Move the completed process to the finish queue
                insertNode(finishQueue, runningProc);
                runningProc = NULL;
            }
        }
        // Print status
        if (runningProc != NULL) {
            printf("CPU is being used by Process %d at quantum %d. Remaining Time: %d\n",
                   runningProc->process->arrivalTime, quantum,
                   runningProc->process->expectedRuntime - runningProc->totalRuntime);
        } else {
            printf("CPU is idle at quantum %d.\n", quantum);
        }

        quantum++;

    }
     // Free the remaining nodes in the ready queue
    while ((runningProc = popNode(readyQueue)) != NULL) {
        free(runningProc);
    }
    free(readyQueue);
    free(finishQueue);
}
