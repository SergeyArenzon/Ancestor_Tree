#include "FamilyTree.hpp"
#include <string>
#include <iostream>
using namespace family;

// --------------
// HELP FUNCTIONS
// --------------

Person* findPerson(Person* root, string child_name){
    if(root == nullptr) {
        throw exception();
        
        }
    else if(root->name.compare(child_name) == 0) return root;

    return findPerson(root->father, child_name);
    return findPerson(root->mother, child_name);
}


string printTree(Person* root, string family){
    if(root->father == nullptr && root->mother == nullptr) {       
        return family;      
        }
    if(root->father == nullptr){
        family += "[Son: "+root->name+" Mother: "+root->mother->name+"]"; 
        return printTree(root->mother, family);
    } 
    if(root->mother == nullptr){
        family += "[Son: "+root->name+", Father: "+root->father->name+"]";
    
        return printTree(root->father, family);
    }  
    family += "[Son: "+root->name+", Father: "+root->father->name+", Mother: "+root->mother->name+"]";
    return printTree(root->father, family);
    return printTree(root->mother, family);
}

string countRelation(int height, bool gender){
    if(height == 1) {
        if(gender) return "father";
        else return "mother";
    }else if(height == 2){
        if(gender) return "grandfather";
        else return "grandmother";
    }else{
        string great = "";
        for (size_t i = 0; i < height - 3; i++)
        {
            great += "great ";
        }
        if(gender) return great+"grandfather";
        else return great+"grandmother";
    }

}

string treeHeight(Person* root, string rel_name, int height){
   height++;
   if(root->father == nullptr && root->mother == nullptr) {       
        if(root->name == rel_name) return to_string(height);      
        }else
        {
            throw exception();
        }
    if(root->name == rel_name) return to_string(height);    
    if(root->father == nullptr){
        return treeHeight(root->mother, rel_name, height);
    } 
    if(root->mother == nullptr){
        return treeHeight(root->father, rel_name, height);
    }  
    return treeHeight(root->father, rel_name, height);
    return treeHeight(root->mother, rel_name, height);
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
        Person* child_found = findPerson(root, child);
        Person* f = new Person(father, true);
        child_found->father = f;
        return *this;
    };


family::Tree& family::Tree::addMother(string child, string mother){
        Person* child_found = findPerson(root, child);
        Person* f = new Person(mother, false);
        child_found->mother = f;
        return *this;
    };

string family::Tree::relation(string rel_name){
    
    //return treeHeight(root, rel_name, 0);
    
};
void family::Tree::display(){
    cout<<printTree(root, "")<<endl;
    
};
string family::Tree::find(string name){return "";};
void family::Tree::remove(string name){};


// int main(){
//     family::Tree T ("Yosef"); // Yosef is the "root" of the tree (the youngest person).
// 	T.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
// 	   .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
// 	   .addFather("Yaakov", "Isaac")
// 	   .addMother("Yaakov", "Rivka")
// 	   .addFather("Isaac", "Avraham")
// 	   .addFather("Avraham", "Terah");
//       //T.display();
    
//     return 0;
// }