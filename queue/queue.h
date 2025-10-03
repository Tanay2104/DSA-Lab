#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H
#include "../common.h"

#define INIT_SIZE 2

template <typename T> class DynamicQueue {
private:
  T *A;
  unsigned int N;
  unsigned int head;
  unsigned int tail;
  unsigned int nextSize() { return N*2; }
public:
  DynamicQueue()
  {
    A = new T[INIT_SIZE];
    if (A != nullptr) N = INIT_SIZE;
    else N = 0;
    head = tail = 0;
  } 
  ~DynamicQueue(){delete[] A;}; 
  
  bool isEmpty();
  bool isFull();
  void grow();
  unsigned int size();
  void enqueue(T x);
  bool dequeue(T *x);
};

#endif
