#include "elapse-time.cpp"

#include <iostream>     // std::cout
#include <algorithm>    // std::shuffle
#include <vector>       // std::vector
#include <list>         // std::list
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock


void printArray (int* arr, int size) {
    for (int i = 0; i < size-1; ++i) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[size-1];
}

void insertionSort(std::vector<int> arr) {
    for (int i = 1; i < (int)arr.size()-1; ++i) {
        for (int j = i+1; j >= 0; --j) {
            if (arr[j-1] > arr[j]) {
                std::swap(arr[j], arr[j-1]);
            }
        }
    }
}

void measureInsertionSort()
{
    const int SIZE = 100000;
    /* const int SIZE = 100000;  very slow */

    std::vector<int> arr (SIZE);

    // -- Test reverse order

    for (int i = 0; i < SIZE; i++) {
        arr[i] = SIZE-i;
    }
    std::cout << "Reversed order: " << measure<std::chrono::milliseconds>::execution(insertionSort, arr) << std::endl;

    // -- Test random order

    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (arr.begin(), arr.end(), std::default_random_engine(seed));
    std::cout << "Random order: " << measure<std::chrono::milliseconds>::execution(insertionSort, arr) << std::endl;

    // -- Test sorted

    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }
    std::cout << "Sorted: " << measure<std::chrono::milliseconds>::execution(insertionSort, arr) << std::endl;
}


template <typename container>
void fillContainerBack(container c, int size) {
    for (int i = 0; i < size; ++i) {
        c.push_back(i);
    }
}

template <typename container>
void fillContainerFront(container c, int size) {
    for (int i = 0; i < size; ++i) {
        c.insert(c.begin(), i);
    }
}


template <typename container>
void print_vec(container& cont)
{
    for (auto x: cont) {
         std::cout << ' ' << x;
    }
    std::cout << '\n';
}

void measureVectorVsList()
{
    const int ELEMENTS_NUM = 200000;
    std::vector<int> v;
    std::list<int> l;

    std::cout << "Vector insertion time: " << measure<std::chrono::milliseconds>::execution(fillContainerBack<std::vector<int>>, v, ELEMENTS_NUM) << std::endl;
    std::cout << "List insertion time: " << measure<std::chrono::milliseconds>::execution(fillContainerBack<std::list<int>>, l, ELEMENTS_NUM) << std::endl;

    v.clear();
    l.clear();

    std::cout << "Vector insertion time Front: " << measure<std::chrono::milliseconds>::execution(fillContainerFront<std::vector<int>>, v, ELEMENTS_NUM) << std::endl;
    std::cout << "List insertion time Front: " << measure<std::chrono::milliseconds>::execution(fillContainerFront<std::list<int>>, l, ELEMENTS_NUM) << std::endl;
}

int main()
{
    /* measureInsertionSort(); */
    measureVectorVsList();

    return 0;
}
