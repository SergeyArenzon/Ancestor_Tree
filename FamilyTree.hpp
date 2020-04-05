using namespace std;
#include <string>

namespace family{

    class Person{
        public:
        string name;
        Person* mother;
        Person* father;
        
        Person(string name);

    };


    class Tree{
        public:
        Person* root;

        Tree(string name);

        Tree& addFather(string name1, string name2);
        Tree addMother(string name1, string name2);
        void display();
        string relation(string name);
        string find(string name);
        void remove(string name);
    };

};
