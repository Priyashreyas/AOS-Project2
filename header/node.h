#ifndef __NODE_H__
#define __NODE_H__

#include "proc.h"

typedef struct Node {
  Proc* process;
  int firstRun;
  int totalRuntime;
  int completionTime;
  struct Node* next;
} Node;

#endif
