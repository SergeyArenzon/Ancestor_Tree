#include "doctest.h"
#include "FamilyTree.hpp"


family::Tree T("a");


TEST_CASE("addFather"){
    
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

    CHECK(T.find("father") == string("a, b"));
    CHECK(T.find("grandfather") == string("a, c"));
    CHECK(T.find("great grandfather") == string("a, d")); 
    CHECK(T.find("great great grandfather") == string("a, e")); 
    CHECK(T.find("great great great grandfather") == string("a, f")); 



}  //10


TEST_CASE("g*gf"){
    CHECK(T.relation("c") == string("grandfather"));
    CHECK(T.relation("d") == string("great grandfather"));
    CHECK(T.relation("e") == string("great great grandfather"));
    CHECK(T.relation("f") == string("great great great grandfather"));

     // remove

    CHECK_NOTHROW(T.remove("a") );
    CHECK_NOTHROW(T.remove("b") );
    CHECK_NOTHROW(T.remove("c") );
    CHECK_NOTHROW(T.remove("d") );
    CHECK_NOTHROW(T.remove("e") );
    CHECK_NOTHROW(T.remove("f") );
    CHECK_THROWS_AS(T.remove("k"), const std::exception&);
    CHECK_THROWS_AS(T.remove("z"), const std::exception&);
    CHECK_THROWS_AS(T.remove("a"), const std::exception&);
    CHECK_THROWS_AS(T.remove("b"), const std::exception&);
    CHECK_THROWS_AS(T.remove("c"), const std::exception&);
    CHECK_THROWS_AS(T.remove("d"), const std::exception&);
    CHECK_THROWS_AS(T.remove("e"), const std::exception&);
    CHECK_THROWS_AS(T.remove("f"), const std::exception&);
    
} //18


family::Tree TT("a");

TEST_CASE("m-mm-m-..."){
    TT.addMother("a","b");
    CHECK(TT.relation("b") == string("mother"));

    TT.addFather("b", "c");
    CHECK(TT.relation("c") == string("mother"));

    TT.addFather("c", "d");
    CHECK(TT.relation("d") == string("mother"));

    TT.addFather("d", "e");
    CHECK(TT.relation("e") == string("mother"));

    TT.addFather("e", "f");
    CHECK(TT.relation("f") == string("mother"));

    CHECK(TT.find("mother") == string("a, b"));
    CHECK(TT.find("grandmother") == string("a, c"));
    CHECK(TT.find("great grandmother") == string("a, d")); 
    CHECK(TT.find("great great grandmother") == string("a, e")); 
    CHECK(TT.find("great great great granmother") == string("a, f"));

}// 10

TEST_CASE("g*gm"){
    CHECK(TT.relation("c") == string("grandmother"));
    CHECK(TT.relation("d") == string("great grandmother"));
    CHECK(TT.relation("e") == string("great great grandmother"));
    CHECK(TT.relation("f") == string("great great great grandmother"));


     // remove

    CHECK_NOTHROW(TT.remove("a") );
    CHECK_NOTHROW(TT.remove("b") );
    CHECK_NOTHROW(TT.remove("c") );
    CHECK_NOTHROW(TT.remove("d") );
    CHECK_NOTHROW(TT.remove("e") );
    CHECK_NOTHROW(TT.remove("f") );
    CHECK_THROWS_AS(TT.remove("k"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("z"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("a"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("b"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("c"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("d"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("e"), const std::exception&);
    CHECK_THROWS_AS(TT.remove("f"), const std::exception&);
} //18



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
    CHECK(TTT.relation("f") == string("great grandmother"));
    
    TTT.addFather("e", "g");
    CHECK(TTT.relation("g") == string("great grandfather"));
  
  
  
//     b
   
// a 
//         d
  
//     c    
//             f
//         e
//             g


    // find
    CHECK(TTT.find("mother") == string("e, g"));
    CHECK(TTT.find("father") == string("e, f"));
    CHECK(TTT.find("father") == string("c, d"));
    CHECK(TTT.find("mother") == string("c, e"));
    CHECK(TTT.find("father") == string("a, b"));
    CHECK(TTT.find("mother") == string("a, c"));
    CHECK(TTT.find("grandfather") == string("a, d"));
    CHECK(TTT.find("grandmother") == string("c, e"));
    CHECK(TTT.find("great grandfather") == string("a, f"));
    CHECK(TTT.find("great grandmother") == string("c, g"));


    CHECK_NOTHROW(TTT.remove("a") );
    CHECK_NOTHROW(TTT.remove("b") );
    CHECK_NOTHROW(TTT.remove("c") );
    CHECK_NOTHROW(TTT.remove("d") );
    CHECK_NOTHROW(TTT.remove("e") );
    CHECK_NOTHROW(TTT.remove("f") );
    CHECK_NOTHROW(TTT.remove("g") );
    CHECK_THROWS_AS(TTT.remove("k"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("z"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("a"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("b"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("c"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("d"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("e"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("f"), const std::exception&);
    CHECK_THROWS_AS(TTT.remove("g"), const std::exception&);

}// 32


   /// 88

family::Tree TTTT("a");

TEST_CASE("MIX"){
    TTTT.addFather("a","b");
    TTTT.addMother("a", "c");
    TTTT.addFather("c", "d");   
    TTTT.addMother("c", "e");
    TTTT.addFather("e", "f");
    TTTT.addFather("e", "g");

    CHECK_NOTHROW(TTTT.remove("b"));
    CHECK_THROWS_AS(TTTT.remove("a"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("b"), const std::exception&);
    

    CHECK_NOTHROW(TTTT.remove("f"));
    CHECK_THROWS_AS(TTTT.remove("d"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("e"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("f"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("c"), const std::exception&);

    CHECK_NOTHROW(TTTT.remove("g"));
    CHECK_THROWS_AS(TTTT.remove("g"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("e"), const std::exception&);
    CHECK_THROWS_AS(TTTT.remove("p"), const std::exception&);


} //12