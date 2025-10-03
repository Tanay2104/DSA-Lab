#include "stack.h"

using namespace std;

template<typename T> int arrayStack<T>::size() {
    return h+1;
}
template<typename T> bool arrayStack<T>::isEmpty(){
    return h<0;
}
template<typename T> void arrayStack<T>::grow(){
    int new_N = N*2;
    T* tmp = new T[new_N];

    for(unsigned i=0;i<size();i++){
        tmp[i] = S[i];
    }
    delete[] S;
    S = tmp;
    N = new_N;
}

template<typename T> T& arrayStack<T>::top(){
    return S[h];
}

template<typename T> void arrayStack<T>::push(T value){
    if (size()==N) grow();
    S[++h] = value;
}

template<typename T> void arrayStack<T>::pop() { 
    if(!isEmpty()) h--;
}