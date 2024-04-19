#include "proc.h"

typedef struct Node {
  Proc* process;
  int firstRun;
  int waitTime;
  int completionTime;
  Node* next;
} Node;
