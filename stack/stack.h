#ifndef STACK_H
#define STACK_H
#include "../common.h"

#define INIT_SIZE 2

template <typename T> class arrayStack {
private:
    T *S = nullptr;
    unsigned int N = INIT_SIZE;
    int h=-1;
public:
    arrayStack() {S = new T[N];}
    ~arrayStack() {delete[] S;}
    //arrayStack(const arrayStack<T>& other) = delete;
    //arrayStack<T>& operator=(const arrayStack<T>& other) = delete;
    int size();
    bool isEmpty();
    void grow();
    T& top();
    void push(T e);
    void pop();

};
#endif