#include <iostream>
#include <vector>


template <typename Iterator>
int basicSearchIt(Iterator start_it, Iterator end_it, int item) {
    Iterator i = start_it;
    for (start_it ; i != end_it ; ++i) {
        if (*i == item) break;
    }

    int idx = i == end_it ?
        -1 :
        std::distance(start_it, i);

    return idx;
}

int basicSearch(std::vector<int> & v, int item) {
    for (int i = 0; i < (int)v.size(); ++i) {
        if (v[i] == item) return i;
    }
    return -1;
}


int binSearchRec(std::vector<int> & v, int item, int start, int end) {
    if (start > end) return -1;

    int mid = start + (end - start) / 2; 

    if (v[mid] == item) return mid;
    if (v[mid] > item) return binSearchRec(v, item, start, mid-1);
    return binSearchRec(v, item, mid+1, end);
}

int binSearch(std::vector<int> & v, int item) {
    return binSearchRec(v, item, 0, v.size()-1);
}


void insertionSort(std::vector<int> v) {
    for (int i = 0; i < (int)v.size(); ++i) {
        for (int j = i; j > 0 || v[j] > v[j-1]; ++j) {
            std::swap(v[j], v[j-1]);
        }
    }
}
