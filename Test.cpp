#include "doctest.h"
#include "FamilyTree.hpp"
#include <iostream>

family::Tree T("a");


TEST_CASE("addFather"){
    
    T.addFather("a","b");
    CHECK(T.relation("b") == string("father"));

    T.addFather("b", "c");
    CHECK(T.relation("c") == string("grandfather"));

    T.addFather("c", "d");
    CHECK(T.relation("d") == string("great-grandfather"));

    T.addFather("d", "e");
    CHECK(T.relation("e") == string("great-great-grandfather"));

    T.addFather("e", "f");
    CHECK(T.relation("f") == string("great-great-great-grandfather"));

    CHECK(T.find("father") == string("b"));
    CHECK(T.find("grandfather") == string("c"));
    CHECK(T.find("great-grandfather") == string("d")); 
    CHECK(T.find("great-great-grandfather") == string("e")); 
    CHECK(T.find("great-great-great-grandfather") == string("f")); 

std::cout<<"----------------------"<<std::endl;

}  //10


TEST_CASE("g*gf"){  
    CHECK(T.relation("c") == string("grandfather"));
    CHECK(T.relation("d") == string("great-grandfather"));
    CHECK(T.relation("e") == string("great-great-grandfather"));
    CHECK(T.relation("f") == string("great-great-great-grandfather"));

     // remove


    CHECK_NOTHROW(T.remove("b") );
    CHECK_THROWS_AS(T.remove("c"), const std::exception& );
    CHECK_THROWS_AS(T.remove("d"), const std::exception& );
    CHECK_THROWS_AS(T.remove("f"), const std::exception& );
    CHECK_THROWS_AS(T.remove("k"), const std::exception&);
    CHECK_THROWS_AS(T.remove("z"), const std::exception&);
    CHECK_THROWS_AS(T.remove("b"), const std::exception&);
    CHECK_THROWS_AS(T.remove("c"), const std::exception&);
    CHECK_THROWS_AS(T.remove("d"), const std::exception&);
    CHECK_THROWS_AS(T.remove("e"), const std::exception&);
    CHECK_THROWS_AS(T.remove("f"), const std::exception&);
    
} //15


family::Tree TT("a");

TEST_CASE("m-mm-m-..."){
    TT.addMother("a","b");
    CHECK(TT.relation("b") == string("mother"));

    TT.addFather("b", "c");
    CHECK(TT.relation("c") == string("grandfather"));

    TT.addFather("c", "d");
    CHECK(TT.relation("d") == string("great-grandfather"));

    TT.addFather("d", "e");
    CHECK(TT.relation("e") == string("great-great-grandfather"));

    TT.addFather("e", "f");
    CHECK(TT.relation("f") == string("great-great-great-grandfather"));

    CHECK(TT.find("mother") == string("b"));
    CHECK(TT.find("grandfather") == string("c"));
    CHECK(TT.find("great-grandfather") == string("d")); 
    CHECK(TT.find("great-great-grandfather") == string("e")); 
    CHECK(TT.find("great-great-great-grandfather") == string("f"));

}// 10

TEST_CASE("g*gm"){
    family::Tree TT("a");
    TT.addMother("a","b");
    TT.addFather("b", "c");
    TT.addFather("c", "d");
    TT.addFather("d", "e");
    TT.addFather("e", "f");

    CHECK(TT.relation("c") == string("grandfather"));
    CHECK(TT.relation("d") == string("great-grandfather"));
    CHECK(TT.relation("e") == string("great-great-grandfather"));
    CHECK(TT.relation("f") == string("great-great-great-grandfather"));


     // remove

    CHECK_NOTHROW(TT.remove("b") );
    CHECK_THROWS_AS(TT.remove("c"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("d"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("e"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("f"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("k"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("z"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("b"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("c"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("d"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("e"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("f"), const std::exception&);
} //16



family::Tree TTT("a");

TEST_CASE("MIX"){
    TTT.addFather("a","b");
    CHECK(TTT.relation("b") == string("father"));

    TTT.addMother("a", "c");
    CHECK(TTT.relation("c") == string("mother"));

    TTT.addFather("c", "d");
    CHECK(TTT.relation("d") == string("grandfather"));

    TTT.addMother("c", "e");
    CHECK(TTT.relation("e") == string("grandmother"));

    TTT.addFather("e", "f");
    CHECK(TTT.relation("f") == string("great-grandfather"));
    
    TTT.addFather("e", "g");
    CHECK(TTT.relation("g") == string("great-grandfather"));




//     b

// a 
//         d
  
//     c    
//             f
//         e
//             g


    // find
    CHECK(TTT.find("mother") == string("c"));
    CHECK(TTT.find("father") == string("b"));
    CHECK(TTT.find("father") == string("b"));
    CHECK(TTT.find("mother") == string("c"));
    CHECK(TTT.find("father") == string("b"));
    CHECK(TTT.find("mother") == string("c"));
    CHECK(TTT.find("grandfather") == string("d"));
    CHECK(TTT.find("grandmother") == string("e"));


    CHECK_NOTHROW(TTT.remove("b") );
    CHECK_NOTHROW(TTT.remove("c") );
    CHECK_THROWS_AS(TTT.remove("d"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("e"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("f"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("g"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("k"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("z"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("b"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("c"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("d"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("e"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("f"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("g"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("cc"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("db"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("eg"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("fhfghf"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove(""), const std::exception&);

}// 28



   /// 88

family::Tree TTTT("a");
TEST_CASE("MIX"){
    TTTT.addFather("a","b");
    TTTT.addMother("a", "c");
    TTTT.addFather("c", "d");   
    TTTT.addMother("c", "e");
    TTTT.addFather("e", "f");
    TTTT.addFather("e", "g");

    CHECK_NOTHROW(TTTT.remove("c"));
    CHECK_THROWS_AS(TTTT.remove("d"), const std::exception&);
    CHECK_NOTHROW(TTTT.remove("b"));
    
    
    

    CHECK_THROWS_AS(TTTT.remove("f"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("d"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("e"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("f"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("c"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("g"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("e"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("p"), const std::exception&);
     CHECK_THROWS_AS(TTTT.remove("fd"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("csgdfg"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("gsdfs"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove(" "), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove(""), const std::exception&);

} //11