#include <stdlib.h>
#include <stdio.h>

#include "../header/algo.h"

const int NUM_PROC = 50;
const int NUM_SETS = 5;

int comparator(const void* p1, const void* p2) {
  Proc* proc1 = (Proc*)p1;
  Proc* proc2 = (Proc*)p2;
  return (proc1->arrivalTime - proc2->arrivalTime);
}

int main() {
  // Generate NUM_SETS sets of NUM_PROC random processes
  Proc* arrivalQueue[NUM_SETS];
  for (int i = 0;  i < NUM_SETS; ++i) {
    arrivalQueue[i] = malloc(NUM_PROC * sizeof(Proc));
    char id = 'A';
    for (int j = 0; j < NUM_PROC; ++j) {
      arrivalQueue[i][j].arrivalTime = rand() % 100;
      arrivalQueue[i][j].expectedRuntime = (rand() % 10) + 1;
      arrivalQueue[i][j].priority = (rand() % 4) + 1;
      arrivalQueue[i][j].name = id;
      id = (id == 'Z')? 'a' : id + 1;
    }
    //printf("\n\n");
    // Sort arrival queue by arrival time
    qsort(arrivalQueue[i], NUM_PROC, sizeof(Proc), comparator);
 
    for (int j = 0; j < NUM_PROC; ++j) {
      //printf("Process %c arrives at %d: priority (%d), runtime (%d)\n", arrivalQueue[i][j].name, arrivalQueue[i][j].arrivalTime, arrivalQueue[i][j].priority, arrivalQueue[i][j].expectedRuntime);
    }
    //printf("\n\n");
    
    //FirstComeFirstServe(arrivalQueue[i], NUM_PROC);
    //printf("\n\n");
    //ShortestJobFirst(arrivalQueue[i], NUM_PROC);
    //printf("\n\n");
    //ShortestRemainingTimeFirst(arrivalQueue[i], NUM_PROC);
    //printf("\n\n");
    //RoundRobin(arrivalQueue[i], NUM_PROC);
    //printf("\n\n");
    //NonPreempHPF(arrivalQueue[i], NUM_PROC); 
    //printf("\n\n");
    //PreempHPF(arrivalQueue[i], NUM_PROC);
    //printf("\n\n");
  }
  
  // Store values for average statistics over all runs
  Avg aggregate;
  aggregate.avgTurnaround = 0;
  aggregate.avgResponse = 0;
  aggregate.avgWaiting = 0;
  aggregate.throughput = 0;

  // Simulate FCFS
  printf("FCFS Simulation and Statistics\n");
  for (int i = 0; i < NUM_SETS; ++i) {
    printf("================================\n");
    printf("Run %d\n", i + 1);
    Avg avg;
    FirstComeFirstServe(arrivalQueue[i], NUM_PROC, &avg);
    aggregate.avgTurnaround += avg.avgTurnaround;
    aggregate.avgResponse += avg.avgResponse;
    aggregate.avgWaiting += avg.avgWaiting;
    aggregate.throughput += avg.throughput;
  }

  aggregate.avgTurnaround /= NUM_SETS;
  aggregate.avgResponse /= NUM_SETS;
  aggregate.avgWaiting /= NUM_SETS;
  aggregate.throughput /= NUM_SETS;

  // Print average statics over all runs
  printf("================================\n");
  printf("All runs\n");
  printf("Average turnaround time: %f\n", aggregate.avgTurnaround);
  printf("Average response time: %f\n", aggregate.avgResponse);
  printf("Average throughput: %f\n", aggregate.throughput);
  printf("================================\n\n\n");
  
  aggregate.avgTurnaround = 0;
  aggregate.avgResponse = 0;
  aggregate.avgWaiting = 0;
  aggregate.throughput = 0;

  // Simulate SJF
  printf("SJF Simulation and Statistics\n");
  for (int i = 0; i < NUM_SETS; ++i) {
    printf("================================\n");
    printf("Run %d\n", i + 1);
    Avg avg;
    ShortestJobFirst(arrivalQueue[i], NUM_PROC, &avg);
    aggregate.avgTurnaround += avg.avgTurnaround;
    aggregate.avgResponse += avg.avgResponse;
    aggregate.avgWaiting += avg.avgWaiting;
    aggregate.throughput += avg.throughput;
  }

  aggregate.avgTurnaround /= NUM_SETS;
  aggregate.avgResponse /= NUM_SETS;
  aggregate.avgWaiting /= NUM_SETS;
  aggregate.throughput /= NUM_SETS;

  // Print average statics over all runs
  printf("================================\n");
  printf("All runs\n");
  printf("Average turnaround time: %f\n", aggregate.avgTurnaround);
  printf("Average response time: %f\n", aggregate.avgResponse);
  printf("Average throughput: %f\n", aggregate.throughput);
  printf("================================\n\n\n");

  aggregate.avgTurnaround = 0;
  aggregate.avgResponse = 0;
  aggregate.avgWaiting = 0;
  aggregate.throughput = 0;

  // Simulate SRTF
  printf("SRTF Simulation and Statistics\n");
  for (int i = 0; i < NUM_SETS; ++i) {
    printf("================================\n");
    printf("Run %d\n", i + 1);
    Avg avg;
    ShortestRemainingTimeFirst(arrivalQueue[i], NUM_PROC, &avg);
    aggregate.avgTurnaround += avg.avgTurnaround;
    aggregate.avgResponse += avg.avgResponse;
    aggregate.avgWaiting += avg.avgWaiting;
    aggregate.throughput += avg.throughput;
  }

  aggregate.avgTurnaround /= NUM_SETS;
  aggregate.avgResponse /= NUM_SETS;
  aggregate.avgWaiting /= NUM_SETS;
  aggregate.throughput /= NUM_SETS;

  // Print average statics over all runs
  printf("================================\n");
  printf("All runs\n");
  printf("Average turnaround time: %f\n", aggregate.avgTurnaround);
  printf("Average response time: %f\n", aggregate.avgResponse);
  printf("Average throughput: %f\n", aggregate.throughput);
  printf("================================\n\n\n");

  aggregate.avgTurnaround = 0;
  aggregate.avgResponse = 0;
  aggregate.avgWaiting = 0;
  aggregate.throughput = 0;

  // Simulate RR
  printf("RR Simulation and Statistics\n");
  for (int i = 0; i < NUM_SETS; ++i) {
    printf("================================\n");
    printf("Run %d\n", i + 1);
    Avg avg;
    RoundRobin(arrivalQueue[i], NUM_PROC, &avg);
    aggregate.avgTurnaround += avg.avgTurnaround;
    aggregate.avgResponse += avg.avgResponse;
    aggregate.avgWaiting += avg.avgWaiting;
    aggregate.throughput += avg.throughput;
  }

  aggregate.avgTurnaround /= NUM_SETS;
  aggregate.avgResponse /= NUM_SETS;
  aggregate.avgWaiting /= NUM_SETS;
  aggregate.throughput /= NUM_SETS;

  // Print average statics over all runs
  printf("================================\n");
  printf("All runs\n");
  printf("Average turnaround time: %f\n", aggregate.avgTurnaround);
  printf("Average response time: %f\n", aggregate.avgResponse);
  printf("Average throughput: %f\n", aggregate.throughput);
  printf("================================\n\n\n");

  // Free dynamic memory
  for (int i = 0; i < NUM_SETS; ++i) {
    free(arrivalQueue[i]);
    arrivalQueue[i] = NULL;
  }

  return 0;
}
