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
  }
  
  // Store values for average statistics over all runs
  Avg aggregate;
  aggregate.avgTurnaround = 0;
  aggregate.avgResponse = 0;
  aggregate.avgWaiting = 0;
  aggregate.throughput = 0;

  // Reminder what asterisk means in time chart
  printf("Note: * = CPU is idle in time chart\n\n");

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
  printf("Average waiting time: %f\n", aggregate.avgWaiting);
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
  printf("Average waiting time: %f\n", aggregate.avgWaiting);
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
  printf("Average waiting time: %f\n", aggregate.avgWaiting);
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
  printf("Average waiting time: %f\n", aggregate.avgWaiting);
  printf("Average throughput: %f\n", aggregate.throughput);
  printf("================================\n\n\n");
  
  aggregate.avgTurnaround = 0;
  aggregate.avgResponse = 0;
  aggregate.avgWaiting = 0;
  aggregate.throughput = 0;

  aggregate.turnaroundP1 = 0;
  aggregate.responseP1 = 0;
  aggregate.waitingP1 = 0;
  aggregate.throughputP1 = 0;
  aggregate.cntP1 = 0;

  aggregate.turnaroundP2 = 0;
  aggregate.responseP2 = 0;
  aggregate.waitingP2 = 0;
  aggregate.throughputP2 = 0;
  aggregate.cntP2 = 0;

  aggregate.turnaroundP3 = 0;
  aggregate.responseP3 = 0;
  aggregate.waitingP3 = 0;
  aggregate.throughputP3 = 0;
  aggregate.cntP3 = 0;

  aggregate.turnaroundP4 = 0;
  aggregate.responseP4 = 0;
  aggregate.waitingP4 = 0;
  aggregate.throughputP4 = 0;
  aggregate.cntP4 = 0; 

  // Simulate Non-Preemptive HPF
  printf("Non-Preemptive HPF Simulation and Statistics\n");
  for (int i = 0; i < NUM_SETS; ++i) {
    printf("================================\n");
    printf("Run %d\n", i + 1);
    Avg avg;
    NonPreempHPF(arrivalQueue[i], NUM_PROC, &avg);
    
    aggregate.avgTurnaround += avg.avgTurnaround;
    aggregate.avgResponse += avg.avgResponse;
    aggregate.avgWaiting += avg.avgWaiting;
    aggregate.throughput += avg.throughput;

    aggregate.turnaroundP1 += avg.turnaroundP1;
    aggregate.responseP1 += avg.responseP1;
    aggregate.waitingP1 += avg.waitingP1;
    aggregate.throughputP1 += avg.throughputP1;
    aggregate.cntP1 += avg.cntP1;

    aggregate.turnaroundP2 += avg.turnaroundP2;
    aggregate.responseP2 += avg.responseP2;
    aggregate.waitingP2 += avg.waitingP2;
    aggregate.throughputP2 += avg.throughputP2;
    aggregate.cntP2 += avg.cntP2;

    aggregate.turnaroundP3 += avg.turnaroundP3;
    aggregate.responseP3 += avg.responseP3;
    aggregate.waitingP3 += avg.waitingP3;
    aggregate.throughputP3 += avg.throughputP3;
    aggregate.cntP3 += avg.cntP3;

    aggregate.turnaroundP4 += avg.turnaroundP4;
    aggregate.responseP4 += avg.responseP4;
    aggregate.waitingP4 += avg.waitingP4;
    aggregate.throughputP4 += avg.throughputP4;
    aggregate.cntP4 += avg.cntP4;
  }

  aggregate.avgTurnaround /= NUM_SETS;
  aggregate.avgResponse /= NUM_SETS;
  aggregate.avgWaiting /= NUM_SETS;
  aggregate.throughput /= NUM_SETS;

  if (aggregate.cntP1) {
    aggregate.turnaroundP1 /= aggregate.cntP1;
    aggregate.responseP1 /= aggregate.cntP1;
    aggregate.waitingP1 /= aggregate.cntP1;
    aggregate.throughputP1 /= aggregate.cntP1;
  }

  if (aggregate.cntP2) {
    aggregate.turnaroundP2 /= aggregate.cntP2;
    aggregate.responseP2 /= aggregate.cntP2;
    aggregate.waitingP2 /= aggregate.cntP2;
   aggregate.throughputP2 /= aggregate.cntP2;
  }

  if (aggregate.cntP3) {
    aggregate.turnaroundP3 /= aggregate.cntP3;
    aggregate.responseP3 /= aggregate.cntP3;
    aggregate.waitingP3 /= aggregate.cntP3;
    aggregate.throughputP3 /= aggregate.cntP3;
  }

  if (aggregate.cntP4) {
    aggregate.turnaroundP4 /= aggregate.cntP4;
    aggregate.responseP4 /= aggregate.cntP4;
    aggregate.waitingP4 /= aggregate.cntP4;
    aggregate.throughputP4 /= aggregate.cntP4;
  }

  // Print average statics over all runs
  printf("================================\n");
  printf("All runs\n");
  printf("Average turnaround time: %f\n", aggregate.avgTurnaround);
  printf("Average response time: %f\n", aggregate.avgResponse);
  printf("Average waiting time: %f\n", aggregate.avgWaiting);
  printf("Average throughput: %f\n\n", aggregate.throughput);
  
  printf("Average turnaround time (P1): %f\n", aggregate.turnaroundP1);
  printf("Average response time (P1): %f\n", aggregate.responseP1);
  printf("Average waiting time (P1): %f\n", aggregate.waitingP1);
  printf("Average throughput (P1); %f\n\n", aggregate.throughputP1);
  
  printf("Average turnaround time (P2): %f\n", aggregate.turnaroundP2);
  printf("Average response time (P2): %f\n", aggregate.responseP2);
  printf("Average waiting time (P2): %f\n", aggregate.waitingP2);
  printf("Average throughput (P2); %f\n\n", aggregate.throughputP2);
  
  printf("Average turnaround time (P3): %f\n", aggregate.turnaroundP3);
  printf("Average response time (P3): %f\n", aggregate.responseP3);
  printf("Average waiting time (P3): %f\n", aggregate.waitingP3);
  printf("Average throughput (P3); %f\n\n", aggregate.throughputP3);
  
  printf("Average turnaround time (P4): %f\n", aggregate.turnaroundP4);
  printf("Average response time (P4): %f\n", aggregate.responseP4);
  printf("Average waiting time (P4): %f\n", aggregate.waitingP4);
  printf("Average throughput (P4); %f\n", aggregate.throughputP4);
  printf("================================\n\n\n");

  aggregate.avgTurnaround = 0;
  aggregate.avgResponse = 0;
  aggregate.avgWaiting = 0;
  aggregate.throughput = 0;

  aggregate.turnaroundP1 = 0;
  aggregate.responseP1 = 0;
  aggregate.waitingP1 = 0;
  aggregate.throughputP1 = 0;
  aggregate.cntP1 = 0;

  aggregate.turnaroundP2 = 0;
  aggregate.responseP2 = 0;
  aggregate.waitingP2 = 0;
  aggregate.throughputP2 = 0;
  aggregate.cntP2 = 0;

  aggregate.turnaroundP3 = 0;
  aggregate.responseP3 = 0;
  aggregate.waitingP3 = 0;
  aggregate.throughputP3 = 0;
  aggregate.cntP3 = 0;

  aggregate.turnaroundP4 = 0;
  aggregate.responseP4 = 0;
  aggregate.waitingP4 = 0;
  aggregate.throughputP4 = 0;
  aggregate.cntP4 = 0; 

  // Simulate Preemptive HPF
  printf("Preemptive HPF Simulation and Statistics\n");
  for (int i = 0; i < NUM_SETS; ++i) {
    printf("================================\n");
    printf("Run %d\n", i + 1);
    Avg avg;
    PreempHPF(arrivalQueue[i], NUM_PROC, &avg);
    
    aggregate.avgTurnaround += avg.avgTurnaround;
    aggregate.avgResponse += avg.avgResponse;
    aggregate.avgWaiting += avg.avgWaiting;
    aggregate.throughput += avg.throughput;

    aggregate.turnaroundP1 += avg.turnaroundP1;
    aggregate.responseP1 += avg.responseP1;
    aggregate.waitingP1 += avg.waitingP1;
    aggregate.throughputP1 += avg.throughputP1;
    aggregate.cntP1 += avg.cntP1;

    aggregate.turnaroundP2 += avg.turnaroundP2;
    aggregate.responseP2 += avg.responseP2;
    aggregate.waitingP2 += avg.waitingP2;
    aggregate.throughputP2 += avg.throughputP2;
    aggregate.cntP2 += avg.cntP2;

    aggregate.turnaroundP3 += avg.turnaroundP3;
    aggregate.responseP3 += avg.responseP3;
    aggregate.waitingP3 += avg.waitingP3;
    aggregate.throughputP3 += avg.throughputP3;
    aggregate.cntP3 += avg.cntP3;

    aggregate.turnaroundP4 += avg.turnaroundP4;
    aggregate.responseP4 += avg.responseP4;
    aggregate.waitingP4 += avg.waitingP4;
    aggregate.throughputP4 += avg.throughputP4;
    aggregate.cntP4 += avg.cntP4;
  }

  aggregate.avgTurnaround /= NUM_SETS;
  aggregate.avgResponse /= NUM_SETS;
  aggregate.avgWaiting /= NUM_SETS;
  aggregate.throughput /= NUM_SETS;

  if (aggregate.cntP1) {
    aggregate.turnaroundP1 /= aggregate.cntP1;
    aggregate.responseP1 /= aggregate.cntP1;
    aggregate.waitingP1 /= aggregate.cntP1;
    aggregate.throughputP1 /= aggregate.cntP1;
  }

  if (aggregate.cntP2) {
    aggregate.turnaroundP2 /= aggregate.cntP2;
    aggregate.responseP2 /= aggregate.cntP2;
    aggregate.waitingP2 /= aggregate.cntP2;
    aggregate.throughputP2 /= aggregate.cntP2;
  }

  if (aggregate.cntP3) {
    aggregate.turnaroundP3 /= aggregate.cntP3;
    aggregate.responseP3 /= aggregate.cntP3;
    aggregate.waitingP3 /= aggregate.cntP3;
    aggregate.throughputP3 /= aggregate.cntP3;
  }

  if (aggregate.cntP4) {
    aggregate.turnaroundP4 /= aggregate.cntP4;
    aggregate.responseP4 /= aggregate.cntP4;
    aggregate.waitingP4 /= aggregate.cntP4;
    aggregate.throughputP4 /= aggregate.cntP4;
  }

  // Print average statics over all runs
  printf("================================\n");
  printf("All runs\n");
  printf("Average turnaround time: %f\n", aggregate.avgTurnaround);
  printf("Average response time: %f\n", aggregate.avgResponse);
  printf("Average waiting time: %f\n", aggregate.avgWaiting);
  printf("Average throughput: %f\n\n", aggregate.throughput);
  
  printf("Average turnaround time (P1): %f\n", aggregate.turnaroundP1);
  printf("Average response time (P1): %f\n", aggregate.responseP1);
  printf("Average waiting time (P1): %f\n", aggregate.waitingP1);
  printf("Average throughput (P1); %f\n\n", aggregate.throughputP1);
  
  printf("Average turnaround time (P2): %f\n", aggregate.turnaroundP2);
  printf("Average response time (P2): %f\n", aggregate.responseP2);
  printf("Average waiting time (P2): %f\n", aggregate.waitingP2);
  printf("Average throughput (P2); %f\n\n", aggregate.throughputP2);
  
  printf("Average turnaround time (P3): %f\n", aggregate.turnaroundP3);
  printf("Average response time (P3): %f\n", aggregate.responseP3);
  printf("Average waiting time (P3): %f\n", aggregate.waitingP3);
  printf("Average throughput (P3); %f\n\n", aggregate.throughputP3);
  
  printf("Average turnaround time (P4): %f\n", aggregate.turnaroundP4);
  printf("Average response time (P4): %f\n", aggregate.responseP4);
  printf("Average waiting time (P4): %f\n", aggregate.waitingP4);
  printf("Average throughput (P4); %f\n", aggregate.throughputP4);
  printf("================================\n\n\n");


  // Free dynamic memory
  for (int i = 0; i < NUM_SETS; ++i) {
    free(arrivalQueue[i]);
    arrivalQueue[i] = NULL;
  }

  return 0;
}
