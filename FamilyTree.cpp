#include "FamilyTree.hpp"
#include <string>
#include <iostream>
using namespace family;


// FUNCTIONS


Person& findPerson(Person& root, string child_name){
    if (root.name != child_name)
    {
        findPerson(*root.father, child_name);
        findPerson(*root.mother, child_name);
    }
    else if(root.name == child_name) return root; 
}



// PERSON
family::Person::Person(string person_name){
    name = person_name;
    father = nullptr;
    mother = nullptr;
};




// TREE
family::Tree::Tree(string name){
    root = new Person(name);

};
family::Tree& Tree::addFather(string child, string father){
    Person& child_found = findPerson(*root, child);
    child_found.father = new Person(father);
    return *this;
    };
family::Tree family::Tree::addMother(string name1, string name2){return Tree("");};
void family::Tree::display(){};
string family::Tree::relation(string name){return "";};
string family::Tree::find(string name){return "";};
void family::Tree::remove(string name){};


// int main(){
//     Tree t("sergey");
//     t.addFather("sergey", "yakov");
//     cout<<t.root->father->name<<endl;
    
// }