#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "node.h"

typedef struct Queue {
  Node* head;
} Queue;

void insertNode(Queue* q, Node* node);
Node* popNode(Queue* q);
#endif
