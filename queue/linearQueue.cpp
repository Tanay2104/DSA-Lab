#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty() {
  return tail==head;
}

template <typename T> bool DynamicQueue<T> :: isFull() {
  return ((tail-head)==N-1);
}

template <typename T> void DynamicQueue<T> :: grow() {
  int new_N = N*2;
  T* tmp = new T[new_N];
  for (int i=0; i < N; i++){
    tmp[i] = A[i];
  }
  delete[] A;
  A = tmp;
  N = new_N;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
  return (tail-head);
}

template <typename T> void DynamicQueue<T> :: enqueue(T x) {
  if (isFull()) grow();
  if (!isFull() && (tail==N-1)) {
    for(int i=head; i < size(); i++) {
      A[i-head] = A[i];
    }
  }
  A[tail] = x;
  tail = tail + 1;
}

template <typename T> bool DynamicQueue<T> :: dequeue(T* x) {
  if (isEmpty()) return false;
  x = &A[head];
  return true;
}
