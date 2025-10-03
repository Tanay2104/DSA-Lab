#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty() {
  return (head==tail);
}

template <typename T> bool DynamicQueue<T> :: isFull() {
  return (head==(tail+1)%N);
}

template <typename T> void DynamicQueue<T> :: grow() {
  int new_N = N*2;
  T* tmp = new T[new_N];
  for (int i=0; i<N;i++){
    tmp[i] = A[(head+i)%N];
  }
  delete[] A;
  tail=head+size();
  A = tmp;
  N=new_N;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
  return (N+tail-head)%N;
}

template <typename T> void DynamicQueue<T> :: enqueue(T x) {
  if (isFull()) grow();
  A[tail] = x;
  tail=(tail+1)%N;
}

template <typename T> bool DynamicQueue<T> :: dequeue(T* x) {
  if (isEmpty()) return false;
  x = &A[head];
  head = (head+1)%N;
  return true;
}
