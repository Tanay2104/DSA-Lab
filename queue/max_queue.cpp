#include <iostream>
#define DEBUG true
class MaxQueue {
    private:
        int* arr;
        int* max_arr;
        int max_size;
        int N_tail;
        int M_tail; 
        int N_head;
        int M_head; 
        void expand() {
            if (DEBUG) std::cout << "Expanding array from size " << max_size << " to size " << 2*max_size << std::endl;
            int new_size = max_size*2;
            int* new_arr = new int[new_size];
            int* new_max_arr = new int[new_size];
            for (int i=0; i < max_size; i++) {
                new_arr[i] = arr[i];
                new_max_arr[i] = max_arr[i];
            }
            delete[] arr;
            delete[] max_arr;
            arr = new_arr;
            max_arr = new_max_arr;
            max_size = new_size;
        }
    public:
        MaxQueue() : N_head(0), M_head(0), N_tail(0), M_tail(0), max_size(2) {
            arr = new int[max_size];
            max_arr = new int[max_size];
        }
        ~MaxQueue() {
            delete[] arr;
        }
        void push(int element) {
            if ((N_tail != N_head) && (N_tail - N_head)%max_size == 0) expand();
            arr[(N_tail++)%max_size] = element;
            if (DEBUG) std::cout << "Inserted element " << element << " at pos " << (N_tail-1)%max_size << std::endl;
            while ((M_tail-M_head)%max_size > 0 && element > max_arr[(M_tail-1)%max_size])
                M_tail--;
            max_arr[(M_tail++)%max_size] = element;
            if (DEBUG) std::cout << "Inserted max element " << element << " at pos " << (M_tail-1)%max_size << std::endl;
        }
        int pop() {
            int element = arr[(N_head++)%max_size];
            if (DEBUG) std::cout << "Popped element " << element << " from pos " << (N_head-1)%max_size << std::endl;
            if (element == max_arr[M_head])
                M_head = (M_head+1)%max_size;
                if (DEBUG) std::cout << "Popped max element " << element << " from pos " << (M_head-1)%max_size << std::endl;
            return element;
        }

        int max() {
            if (DEBUG) std::cout << "Current max element " << max_arr[M_head] << " at pos " << (M_head) << std::endl;
            return max_arr[M_head];
        }

};