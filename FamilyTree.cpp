#include "FamilyTree.hpp"
#include <string>
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
bool checkLegailInput(string relation){
    
        regex pat{ "^(?:(?:great-)*grand)?(?:mother|father)$" };
        bool match = regex_search(relation, pat);
        if(match) return true;
        else return false;
    
}


Person* reltaionsNames(Person* root, string relation){
    if(root==nullptr)
		return nullptr;
	if(root->relation == relation)
		return root;
	Person *found = reltaionsNames(root->father, relation);
	if(found != nullptr)
		return found;
	return reltaionsNames(root->mother, relation);
}

void deleteTree(Person* node)  
{  
    if (node == NULL) return;  
  
    /* first delete both subtrees */
    deleteTree(node->mother);  
    deleteTree(node->father);  
    cout<<"deleted: "<<node->name<<endl;
    free(node) ;  
    node = NULL;
}  

// find given person child by name
Person* findChild(Person* root, string child_name){
    // cout<<"check: " + root->name<<endl; 
    // if(root  == nullptr && root->mother == nullptr)
	// 	return nullptr;
       
	// if(root->father != nullptr && (root->father->name == child_name)) return root;
	// if(root->mother != nullptr && (root->mother->name == child_name)) return root; 

	// Person *found = findChild(root->father,child_name);
	// if(found != nullptr)
	// 	return found;
	// return findChild(root->mother, child_name);




    if(root==nullptr)
		return nullptr;
	if( (root->mother && root->mother->name == child_name) || (root->father && root->father->name == child_name))
		return root;
	Person *found = findChild(root->father,child_name);
	if(found != nullptr)
		return found;
	return findChild(root->mother, child_name);
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
        if(child_found == nullptr) throw exception();
        else{
            Person* f = new Person(father, true);
            child_found->father = f;
            child_found->father->relation = relation(father);
        return *this;}
        
    };


family::Tree& family::Tree::addMother(string child, string mother){
        Person* child_found = findPerson(root, child);
        if(child_found == nullptr) throw exception();
        else{
            Person* f = new Person(mother, false);
            child_found->mother = f;
            child_found->mother->relation = relation(mother);
            return *this;
        }
        
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
    if(checkLegailInput(relation)){
        Person* found = reltaionsNames(root, relation);
        if(found == nullptr) throw exception();
        else return found->name;
    }else throw runtime_error( "The tree cannot handle the '" + relation + "' relation");
    
};


void family::Tree::remove(string name){
    if(name == root->name) throw exception();
    else{
        bool gender;
        Person* found = findPerson(root, name);
        cout<<"remove: "+name<<endl; 
        if(found != nullptr) {
            
            Person* child;
            
            if((root->father && root->father->name == found->name) || (root->mother && root->mother->name == found->name)){
                child = root;
            }else{
                child = findChild(root, name);
            }
            
            if(child->father != nullptr && (child->father->name == name ) )gender = true;
            else gender = false;
            deleteTree(found);
            if(gender) child->father = nullptr;
            else child->mother = nullptr;

        }else{

            throw runtime_error( "'"+ name +"'" + "doesnt exist");
        }
    }
    


};


//  int main(){
//     family::Tree T ("Yosef"); // Yosef is the "root" of the tree (the youngest person).
// 	T.addFather("Yosef", "Yaakov")  // Tells the tree that the father of Yosef is Yaakov.
// 	    .addMother("Yosef", "Rachel") // Tells the tree that the mother of Yosef is Rachel.
//         .addFather("Yaakov", "Isaac")
// 	    .addMother("Yaakov", "Rivka")
// 	    .addFather("Isaac", "Avraham")
// 	    .addFather("Avraham", "Terah");
//         T.addFather("Sergey", "avi");
        


//      return 0;
// }