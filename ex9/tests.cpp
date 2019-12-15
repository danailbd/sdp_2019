#include "../lib/testing-framework.h"
#include "../lib/elapse-time.cpp"
#include "main.cpp"

#include <numeric>
#include <list>


#define MEASURE_UNIT std::chrono::microseconds


void compareSearchMethods() {
    //
    // Prepare Vector data
    //
    const int SIZE = 10000000;
    std::vector<int> v(SIZE);

    std::iota(v.begin(), v.end(), 0);
    
    //
    // Measure
    //

    std::cout << "Binary Search test: "   << measure<MEASURE_UNIT>::execution(binSearch, v, -1) << std::endl;

    std::cout << "Basic Search test: "    << measure<MEASURE_UNIT>::execution(basicSearch, v, -1) << std::endl;
    
    //std::cout << "Basic Search It test: " << measure<MEASURE_UNIT>::execution(basicSearchIt<std::vector<int>::const_iterator>, v.cbegin(), v.cend(), -1) << std::endl;
    std::cout << "Basic Search It test: " << measure<MEASURE_UNIT>::execution(basicSearchIt<std::vector<int>::iterator>, v.begin(), v.end(), -1) << std::endl;


    //
    // Prepare Linked list data
    //
    std::list<int> ll(SIZE);

    std::iota(ll.begin(), ll.end(), 0);

    std::cout << "Basic Search LList It test: " << measure<MEASURE_UNIT>::execution(basicSearchIt<std::list<int>::iterator>, ll.begin(), ll.end(), -1) << std::endl;
}


void testBasicSearchIt() {
    std::cout << "Basic Search It:" << std::endl;
    std::vector<int> cont = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    UnitTests::AssertEq( 5,  basicSearchIt(cont.begin(), cont.end(), 6) );
    UnitTests::AssertEq( 1,  basicSearchIt(cont.begin(), cont.end(), 2) );
    UnitTests::AssertEq( 8,  basicSearchIt(cont.begin(), cont.end(), 9) );
    UnitTests::AssertEq( 0,  basicSearchIt(cont.begin(), cont.end(), 1) );
    UnitTests::AssertEq( -1, basicSearchIt(cont.begin(), cont.end(), 10) );
}

void testSearchAlgorithm(const std::function<int(std::vector<int>&, int)> search) {
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
    testBasicSearchIt();

    std::cout << std::endl
        << "Total Execution Time: " << measure<>::execution(compareSearchMethods);

    return 0;
}
