#include <iostream>
#include <string>

class Entity
{
    public:
        Entity(std::string str) : _str(str) { }
        std::string& getString() { return _str; }
        ~Entity() { std::cout << _str << " Distructor !!!!!!!!!!" << std::endl; }

    private:
        std::string _str;
};



void normalNew();
void plesmentNew();

int main()
{
    //normalNew();
    plesmentNew();
    return 0;
}


void normalNew()
{
    //When we use new keyword in class It will do two thing
    //1st create necessary block of memory inside heap
    //2nd it also call the constructor
    //If we create it by using malloc() then it only create that many block of memory not calling constructor
    Entity* entiry = new Entity("Hello");
    std::cout << entiry->getString() << std::endl;
    //Free created heap section memory
    delete entiry;

    //This is alos pure array of int.
    int* i = new int[50];
    //Free blocks of memory.
    delete [] i;
}


void plesmentNew()
{
    int a = 10;
    //Here new use to point p to have same address of a also change value of a = 100
    int* p = new(&a) int(100);
    std::cout << std::endl << &a << std::endl << p << "\n\n";

    //std::cout << "Size of Entity class is : " << sizeof(Entity) << std::endl;

    //Here we create total 3 Entity size of block of memory inside heap
    char* c = new char[3 * sizeof(Entity)];
    //Here we get that block of memory and make Entity Class 
    Entity* e0 = new(&c[0]) Entity("Hello E0");
    Entity* e1 = new(&c[sizeof(Entity)]) Entity("Hello E1");
    Entity* e2 = new(&c[sizeof(Entity) * 2]) Entity("Hello E2");

    std::cout << e0->getString() << std::endl;
    std::cout << e1->getString() << std::endl;
    std::cout << e2->getString() << std::endl;

    //By default in this case Distructor will not call
    e0->~Entity();
    e1->~Entity();
    e2->~Entity();

    delete [] c;
}
