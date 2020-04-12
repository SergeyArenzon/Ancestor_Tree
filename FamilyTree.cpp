#include "FamilyTree.hpp"
#include <string>
#include <iostream>
#include <regex>
#include <iostream>
using namespace family;

// --------------
// HELP FUNCTIONS
// --------------

// find given person by name
Person* findPerson(Person* root, string child_name){
    if(root==nullptr)
		return nullptr;
	if(root->name == child_name)
		return root;
	Person *found = findPerson(root->father,child_name);
	if(found != nullptr)
		return found;
	return findPerson(root->mother, child_name);
}

// printing the tree in format [son:"son", father:"father", mother:"mother"]
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

// creates relation format string
string countRelation(int height, bool gender){
    if(height == 1) {
        if(gender) return "father";
        else return "mother";
    }else if(height == 2){
        if(gender) return "grandfather";
        else return "grandmother";
    }else{
        string great = "";
        for (size_t i = 0; i < height - 2; i++)
        {
            great += "great-";
        }
        if(gender) return great+"grandfather";
        else return great+"grandmother";
    }
}
// returns tree height by person name
int treeHeight(Person* root, string rel_name){
    if(root == nullptr) {  
       return -1;           //could not find the rel_name
    }    
    else if(root->name == rel_name)
    {
        return 0;
    }
    int leftSide  =  treeHeight(root->father, rel_name);

    if(leftSide < 0)
    {
        int rightSide =  treeHeight(root->mother, rel_name);
        if(rightSide < 0)
            return rightSide;
        else
            return 1 + rightSide;
    }
    return 1 + leftSide;
}

// getting relation string and returns its height in the tree
int stringToNum(string relation){
    std::regex words_regex("[^\\s-]+");
    auto words_begin = std::sregex_iterator(relation.begin(), relation.end(), words_regex);
    auto words_end = std::sregex_iterator();

    if ((*words_begin).str() == "great"){
        int great_count = 0;
        for (std::sregex_iterator i = words_begin; i != words_end; ++i){
            if((*i).str() == "great") great_count++;
        }
            return great_count+2;
    }
    else if ((*words_begin).str() == "grandfather" ||  (*words_begin).str() == "grandmother") return 2;
    else return 1;
}


string reltaionsNames(Person* root, int height, bool isMale){
    
}



// ----------------
// PERSON FUNCTIONS
// ----------------
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





// --------------
// TREE FUNCTIONS
// --------------
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

    if(rel_name == root->name) return "me";
    else{
        Person* found = findPerson(root, rel_name);
        if(found != nullptr){
            int height = treeHeight(root, rel_name);
            return countRelation(height, found->isMale);  
    }
    else return "unrelated";
    }
};
void family::Tree::display(){
    cout<<printTree(root, "")<<endl;
    
};
string family::Tree::find(string relation){
    int count = stringToNum(relation);
    return to_string(count);
    std::regex words_regex("[^\\s-]+");
    auto words_begin = std::sregex_iterator(relation.begin(), relation.end(), words_regex);
    auto words_end = std::sregex_iterator();

    bool isMale;
    if((*words_end).str() == "grandfather" || (*words_end).str() == "father") isMale = true;
    else if((*words_end).str() == "grandmother" || (*words_end).str() == "mother") isMale = false;
    else return "wrong find() input";

    


};
void family::Tree::remove(string name){};


// int main(){
//     // family::Tree T ("Yosef"); // Yosef is the "root" of the tree (the youngest person).
// 	// T.addFather("Yosef", "Yaakov")  // Tells the tree that the father of Yosef is Yaakov.
// 	//    .addMother("Yosef", "Rachel")  // Tells the tree that the mother of Yosef is Rachel.
//     //    .addFather("Yaakov", "Isaac")
// 	//    .addMother("Yaakov", "Rivka")
// 	//    .addFather("Isaac", "Avraham")
// 	//    .addFather("Avraham", "Terah")
//     //    .addMother("Rachel", "x");
//     //    cout<<T.root->mother->mother->name<<endl;
//     //   //T.display();
//     //stringToNum("great-great grandmother");
//     return 0;
// }