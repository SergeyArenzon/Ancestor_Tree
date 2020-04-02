#include "doctest.h"
#include "FamilyTree.hpp"


family::Tree T("a");


TEST_CASE("f-f-f-f-f-f-...."){
    T.addFather("a","b");
    CHECK(T.relation("b") == string("father"));

    T.addFather("b", "c");
    CHECK(T.relation("c") == string("father"));

    T.addFather("c", "d");
    CHECK(T.relation("d") == string("father"));

    T.addFather("d", "e");
    CHECK(T.relation("e") == string("father"));

    T.addFather("e", "f");
    CHECK(T.relation("f") == string("father"));
}  //5


TEST_CASE(""){
    for (size_t i = 0; i < 100; i++)
    {
        CHECK(T.relation("f") == string("father"));
    }
    
}