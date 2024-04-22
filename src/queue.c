#include <stdlib.h>

#include "../header/queue.h"

void insertNode(Queue* q, Node* node) {
  Node* temp = q->head;
  Node* prev = NULL;
  while (temp != NULL) {
    prev = temp;
    temp = temp->next;
  }
  if (prev != NULL) {
    prev->next = node;
    return;
  }
  q->head = node;
}

Node* popNode(Queue* q) {
    if (q->head == NULL) return NULL;
    Node* node = q->head;
    q->head = q->head->next;
    node->next = NULL;
    return node;
}
