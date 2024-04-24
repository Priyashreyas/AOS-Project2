#include <stdlib.h>
#include <stdio.h>

#include "../header/stats.h"
#include "../header/algo.h"


void CalcStats(Avg* avg, Queue* finishQueue, int hpf, int prior) {
  double turnaround = 0;
  double response = 0;
  double waiting = 0;
  Node* temp = finishQueue->head;
  int count = 0;
  while (temp != NULL) {
    if (hpf && temp->process->priority != prior) {
      temp = temp->next;
      continue;
    }
    int taTime = temp->completionTime - temp->process->arrivalTime;
    turnaround += taTime;
    response += temp->firstRun - temp->process->arrivalTime;
    waiting += taTime - temp->process->expectedRuntime;
    count++;
    temp = temp->next;
  }
  avg->avgTurnaround = turnaround / count;
  avg->avgResponse = response / count;
  avg->avgWaiting = waiting / count;
  avg->throughput = ((double) count) / SIM_TIME;
}
