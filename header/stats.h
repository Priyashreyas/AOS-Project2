#ifndef __STATS_H__
#define __STATS_H__

#include "queue.h"


typedef struct Avg {
  double avgTurnaround;
  double avgResponse;
  double avgWaiting;
  double throughput; 
} Avg;

void CalcStats(Avg*, Queue*, int, int);

#endif
