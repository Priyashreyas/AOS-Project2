#ifndef __PROC_H__
#define __PROC_H__

typedef struct Proc {
  int arrivalTime;
  int expectedRuntime;
  int priority;
  char name;
} Proc;

#endif
