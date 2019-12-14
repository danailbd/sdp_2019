#include "../lib/testing-framework.h"
#include "../lib/elapse-time.cpp"
#include "main.cpp"

#include <numeric>



void compareSearchMethods() {
    const int SIZE = 100000000;
    std::vector<int> v(SIZE);

    std::iota(v.begin(), v.end(), 0);
    
    std::cout << "Binary Search test: " << measure<>::execution(binSearch, v, 6000) << std::endl;
    
    std::cout << "Binary Search test: " << measure<>::execution(basicSearch, v, 6000) << std::endl;
}


void testSearchAlgorithm(const std::function<int(std::vector<int>, int)> search) {
    std::vector<int> cont = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    UnitTests::AssertEq( 5,  search(cont, 6) );
    UnitTests::AssertEq( 1,  search(cont, 2) );
    UnitTests::AssertEq( 8,  search(cont, 9) );
    UnitTests::AssertEq( 0,  search(cont, 1) );
    UnitTests::AssertEq( -1, search(cont, 10) );
}

void testBasicSearch() {
    std::cout << "Basic Search:" << std::endl;
    testSearchAlgorithm(basicSearch);
}

void testBinSearch() {
    std::cout << "Binary Search:" << std::endl;
    testSearchAlgorithm(binSearch);
}

int main()
{
    testBinSearch();
    testBasicSearch();

    compareSearchMethods();

    return 0;
}
