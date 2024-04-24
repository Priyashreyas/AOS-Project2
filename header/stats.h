#ifndef __STATS_H__
#define __STATS_H__

#include "queue.h"


typedef struct Avg {
  double avgTurnaround;
  double avgResponse;
  double avgWaiting;
  double throughput;
  int cnt;

  // Data below only used for HPF
  double turnaroundP1;
  double responseP1;
  double waitingP1;
  double throughputP1;
  int cntP1;

  double turnaroundP2; 
  double responseP2;
  double waitingP2;
  double throughputP2;
  int cntP2;

  double turnaroundP3;
  double responseP3;
  double waitingP3;
  double throughputP3;
  int cntP3;

  double turnaroundP4; 
  double responseP4;
  double waitingP4;
  double throughputP4;
  int cntP4;
} Avg;

void CalcStats(Avg*, Queue*, int, int);

#endif
