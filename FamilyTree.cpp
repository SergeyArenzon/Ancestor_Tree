#include "FamilyTree.hpp"
#include <string>
#include <iostream>
using namespace family;


// FUNCTIONS


Person& findPerson(Person* root, string child_name){
    if(root == nullptr) throw exception();
    else if(root->name.compare(child_name) == 0) return *root;
    else{
        if(root->father == nullptr)return findPerson(root->mother, child_name);
        else if(root->mother == nullptr)return findPerson(root->father, child_name);
        else {
            return findPerson(root->mother, child_name);
            return findPerson(root->father, child_name);
        }
        
    }
}

string calcRelation(int count, bool gender){
    if(count == 1) {
        if (gender == true) return "father";
        else return "mother";
    
    }else if(count == 2) {
        if (gender == true) return "grandfather";
        else return "grandmother";
        
    }
    else{
        string path = "";
        for (size_t i = 0; i < count - 3; i++)
        {
            path += "great ";
        }
        if (gender == true) return path + "grandfather";
        else return path + "grandmother";
        
    }    
} 

string getRelation(Person* root,string person, int count){
    if(root == nullptr) throw exception();
    else if(root->name.compare(person) == 0) return to_string(count);
    else{
        if(root->father == nullptr)return getRelation(root->mother, person, count);
        else if(root->mother == nullptr)return getRelation(root->father, person, count);
        else {
            return getRelation(root->mother, person, count);
            return getRelation(root->father, person, count);
        }
        
    }
}


string printTree(Person* root){
    if(root == nullptr) throw exception();
    else if (root->father != nullptr){
        cout<<root->name<<endl;
        return printTree(root->father);
    }else if (root->mother != nullptr){
        cout<<root->name<<endl;
        return printTree(root->mother);
}
}


// PERSON
family::Person::Person(string person_name){
    name = person_name;
    father = nullptr;
    mother = nullptr;

};

family::Person::Person(string person_name, bool is_male){
    name = person_name;
    father = nullptr;
    mother = nullptr;
    isMale = is_male;

};



// TREE
family::Tree::Tree(string name){
    root = new Person(name);
};

family::Tree& Tree::addFather(string child, string father){
    Person& child_found = findPerson(root, child);
    Person* f = new Person(father, true);
    child_found.father = f;

    return *this;
    };


family::Tree& family::Tree::addMother(string child, string mother){
    Person& child_found = findPerson(root, child);
    Person* f = new Person(mother, false);
    child_found.mother = f;
    return *this;
    };

string family::Tree::relation(string rel_name){
    
    return getRelation(root, rel_name,0);
    
};
void family::Tree::display(){
    printTree(root);
};
string family::Tree::find(string name){return "";};
void family::Tree::remove(string name){};


int main(){
    Tree t("X");

    t.addFather("X","Y");
    t.addMother("X", "Z");
    t.addFather("Z", "W");
    t.addFather("X", "F");
    //cout<<t.root->mother->father->name<<endl;;
   //t.relation("Y");
    return 0;
}