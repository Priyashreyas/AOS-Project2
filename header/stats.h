#ifndef __STATS_H__
#define __STATS_H__

#include "queue.h"


typedef struct Avg {
  double avgTurnaround;
  double avgResponse;
  double avgWaiting;
  double avgThroughput; 
} Avg;

Avg CalcStats(Queue*, int, int);

#endif
