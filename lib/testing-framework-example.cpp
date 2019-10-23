#include "./testing-framework.h"


int add (int x, int y) {
 return x + y;
}

int subtract (int x, int y) {
 return x - y;
}


void testAdd()
{
    UnitTests::AssertEq( 5, add(2, 3), "Should do a basic sum" );
    UnitTests::AssertEq( 0, add(0, 0) );
    UnitTests::AssertEq( -1, add(0, -1), "Should add negative numbers correctly" );
    // failing tests
    UnitTests::AssertEq( 6, add(2, 3), "Should do a basic sum" );
    UnitTests::AssertEq( 0, add(0, -1) );
}

void testSubtract()
{
    UnitTests::AssertEq( 1,  subtract(3, 2) );
    UnitTests::AssertEq( -1,  subtract(2, 3) );
    UnitTests::AssertEq( 5,  subtract(2, -3) );
    // failing
    UnitTests::AssertEq( -1, subtract(0, -1), "Should subtract negative numbers correctly" );
}


int main()
{
    testAdd();
    testSubtract();
    UnitTests::PrintTestsResult();

    return 0;
}
