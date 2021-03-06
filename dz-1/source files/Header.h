#pragma once
#include <iostream>
#include <sstream>
#include <vector>

#define out_of_heap_range 2;
#define empty_heap 1;

void test1_4();
void test2_1();
void test4_3();
void test5_2();
void test6_4();
void test7_3();
void test_heap();

void run1_4(std::string s = "", std::string sa = "");

typedef struct ListNode {
    int value;
    ListNode* next;
    ListNode* prev;
};

typedef struct List {
    ListNode* beg = NULL;
    int num_nodes = 0;
};

void print_list(ListNode* list);
void list_add(List& st, int val);
int list_pop_node(List& st);
int list_pop(List& st, int i);

int run2_1(std::string s = "", std::string a = "");
int BinarySearch(const int* a, int len, int el);

template <typename T> class Comparator;
void run4_3(std::string s, std::string sa);

template <typename T, typename Comparator>
int merge_sort(T* arr, size_t len);
template <typename T, typename Comparator>
int merge(T* l, size_t lsize, T* r, size_t rsize, T* res);
void run5_2(std::string s = "", std::string sa = "");
typedef struct {
    short d;
    short m;
    short y;
} date;

class DateComparator {
public:
    bool operator()(const date& l, const date& r)
    {
        if (l.y == r.y)
            if (l.m == r.m)
                return l.d < r.d;
            else
                return l.m < r.m;
        else
            return l.y < r.y;        
    }
};

class DatePairComparator {
public:
    bool operator()(const std::pair<date, date>& l, const std::pair<date, date>& r)
    {
        if (l.first.y == r.first.y)
            if (l.first.m == r.first.m)
                return l.first.d < r.first.d;
            else
                return l.first.m < r.first.m;
        else
            return l.first.y < r.first.y;
    }
};

template <typename T>
int partition(int* a, int len, Comparator<T> cmp);
void run6_4(std::string s, std::string sa);
void print(const int* a, int n);

template <typename T>
class Comparator {
public:
    virtual bool operator()(const T& l, const T& r)
    {
        return l < r;
    }
};

template <typename T>
class MinHeapComparator: Comparator<T> {
public:
    bool operator()(const T& l, const T& r) override
    {
        return l < r;
    }
};

//template <typename T, typename Comparator<T>>
template <typename T>
class Heap {
public:
    Heap()=delete;
    Heap(Comparator<T> custom_cmp) :
        _cmp(custom_cmp) {}
    explicit Heap(const std::vector<T>& v, Comparator<T> custom_cmp = new Comparator<T>()) :
        _heap(v),
        _cmp(custom_cmp)
    {
        create();
    }
    ~Heap() = default;

    void insert(T el);
    void print();
    T extract_top();
    T peek_top();
    size_t size();
private:
    std::vector<T> _heap;
    Comparator<T> _cmp;
    
    void create(const std::vector<T>& v);
    void sift_up(size_t i);
    void sift_down(size_t i);
};

template <typename T>
void Heap<T>::sift_up(size_t i) {
    if (_heap.empty())
        return;
    if (i >= _heap.size())
        throw out_of_heap_range;
    while (i > 0) {
        size_t upper = (i - 1) / 2;
        if (!_cmp(_heap[i], _heap[upper]))  // ??? ? ????? ???????, ????? ?????
                                          // ??? ??????? ???????? ??????, ???? ????? ???????
            return;
        std::swap(_heap[i], _heap[upper]);
        i = upper;
    }
}

template <typename T>
void Heap<T>::sift_down(size_t i) {
    if (_heap.empty())
        return; 
    if (i >= _heap.size())
        throw out_of_heap_range;
    size_t l = i * 2 + 1;
    size_t r = i * 2 + 2;
    size_t changeble = i;
    if (l < _heap.size() && !_cmp(_heap[changeble], _heap[l]))
        changeble = l;
    if (r < _heap.size() &&!_cmp(_heap[changeble], _heap[r]))
        changeble = r;
    if (changeble != i) {
        std::swap(_heap[i], _heap[changeble]);
        sift_down(changeble);
    }
}


template <typename T>
void Heap<T>::create(const std::vector<T>& v) {
    if (v.empty())
        return;
    for (size_t i = 0; i < _heap.size() / 2; ++i)
        sift_down(i);
}

template <typename T>
void Heap<T>::insert(T el) {
    _heap.push_back(el);
    sift_up(_heap.size() - 1);
}

template <typename T>
T Heap<T>::peek_top() {
    if (!_heap.size())
        throw empty_heap;
    return _heap[0];
}

template <typename T>
T Heap<T>::extract_top() {
    if (!_heap.size())
        throw empty_heap;
    T res = _heap[0];
    _heap[0] = _heap.back();
    _heap.pop_back();
    sift_down(0);
    return res;
}

template <typename T>
void Heap<T>::print() {
    if (_heap.empty()) {
        std::cout << "heap is empty\n";
        return;
    }
    size_t k = 2;
    for (size_t i = 0; i < _heap.size() - 1; ++i) {
        std::cout << _heap[i];
        if (i == 0) std::cout << '.';
        if (i == k) {
            std::cout << '.';
            k += (i + 2);
        }
        else {
            if (i == 0) continue;
            std::cout << ' ';
        }
    }
    std::cout << _heap.back() << '\n';
}

template <typename T>
size_t Heap<T>::size() {
    return _heap.size();
}

void run7_3(std::string s = "", std::string sa = "");