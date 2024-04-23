#ifndef __ALGO_H__
#define __ALGO_H__

#include "proc.h"
#include "node.h"

#define SIM_TIME 100

void NonPreempHPF(Proc*, const int);
void PreempHPF(Proc*, const int);
void FirstComeFirstServe(Proc*, const int);
void ShortestJobFirst(Proc*, const int);
void ShortestRemainingTimeFirst(Proc*,const int);

#endif
