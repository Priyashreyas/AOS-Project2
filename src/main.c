#include <stdlib.h>
#include <stdio.h>

#include "../header/algo.h"

const int NUM_PROC = 10;
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
    for (int j = 0; j < NUM_PROC; ++j) {
      arrivalQueue[i][j].arrivalTime = rand() % 100;
      arrivalQueue[i][j].expectedRuntime = (rand() % 10) + 1;
      arrivalQueue[i][j].priority = (rand() % 4) + 1;
      //printf("%d\n", arrivalQueue[i][j].arrivalTime);    
    }
    //printf("\n\n");
    // Sort arrival queue by arrival time
    qsort(arrivalQueue[i], NUM_PROC, sizeof(Proc), comparator);
    
    for (int j = 0; j < NUM_PROC; ++j) {
      //printf("Process arrives at %d: priority (%d), runtime (%d)\n", arrivalQueue[i][j].arrivalTime, arrivalQueue[i][j].priority, arrivalQueue[i][j].expectedRuntime);
    }
    //printf("\n\n");
    //NonPreempHPF(arrivalQueue[i], NUM_PROC); 
    //PreempHPF(arrivalQueue[i], NUM_PROC);
  }

  // Free dynamic memory
  for (int i = 0; i < NUM_SETS; ++i) {
    free(arrivalQueue[i]);
    arrivalQueue[i] = NULL;
  }

  return 0;
}
