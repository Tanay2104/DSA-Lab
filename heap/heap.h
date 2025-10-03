class Heap {
    int max_size;
    int N;
    int * array;
    void expand();
    int parent(int idx);
    void my_swap(int & a, int & b);
public:
    Heap(): max_size(2), N(0) {
        array = new int[max_size];
    }
    ~Heap() {
        delete[] array;
    }
    int maximum();
    void insert(int key);
    void heapify(int key, int * a);
    int delete_max();
    void build_heap(int* arr, int size);
    int get_size() const { return N; }
    bool is_empty() const {return N == 0 ; }
};