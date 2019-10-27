#include "../lib/testing-framework.h"
#include "./spotify.cpp"





void testLQueue() {
    LQueue q;
    Song s1("Hurt", "Ivan", Duration(200));


    std::cout << "When no elements have been added" << std::endl;
    UnitTests::AssertEq( true, q.empty(), "It should report being empty" );

    // add, top
    std::cout << "When one element added" << std::endl;
    q.push(&s1);
    UnitTests::AssertEq( s1.title(), q.head()->title(), "It should return the proper head element" );
    UnitTests::AssertEq( false, q.empty(), "It should report negative emptiness when single element" );

    // remove, add, top
    std::cout << "When the only element is removed" << std::endl;
    q.pop();
    UnitTests::AssertEq( true, q.empty(), "It should report positively emptiness" );

    std::cout << "When the another element is added" << std::endl;
    Song s2 = Song("Boli", "Jorkata", Duration(150));
    q.push(&s2);
    UnitTests::AssertEq( s2.title(), q.head()->title(), "It should return the proper head element" );
    UnitTests::AssertEq( false, q.empty(), "It should report negative emptiness" );


    std::cout << "When two elements are added" << std::endl;
    // Reset queue
    q = LQueue();
    Song s3 = Song("Why not", "Jimmy", Duration(150));
    Song s4 = Song("Oh John", "Jack", Duration(150));

    // remove, add, add, top
    q.push(&s3);
    q.push(&s4);
    UnitTests::AssertEq( s3.title(), q.head()->title(), "It should return the proper head element" );
    UnitTests::AssertEq( false, q.empty(), "It should report negative emptiness" );


    std::cout << "When one of two elements is removed" << std::endl;
    // remove, top
    q.pop();
    UnitTests::AssertEq( s4.title(), q.head()->title(), "It should return the proper top element" );
    UnitTests::AssertEq( false, q.empty(), "Should report negative emptiness" );

    // remove, empty
    std::cout << "When second of two elements is removed" << std::endl;
    q.pop();
    UnitTests::AssertEq( true, q.empty(), "It should be hollow" );
}


int main()
{

    testLQueue();

    UnitTests::PrintTestsResult();

    return 0;
}
