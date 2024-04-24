#ifndef __ALGO_H__
#define __ALGO_H__

#include "proc.h"
#include "node.h"
#include "stats.h"

#define SIM_TIME 100

void NonPreempHPF(Proc*, const int);
void PreempHPF(Proc*, const int);
void FirstComeFirstServe(Proc*, const int, Avg*);
void ShortestJobFirst(Proc*, const int, Avg*);
void ShortestRemainingTimeFirst(Proc*, const int, Avg*);
void RoundRobin(Proc*, const int, Avg*);

#endif
