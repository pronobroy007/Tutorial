#include <iostream>
#include <string>
#include <type_traits>

const int size = 10;

class Entity
{
    public:
        Entity() : _str("Unknown") { std::cout << _str << std::endl; }
        Entity(std::string str) : _str(str) { std::cout << _str << std::endl; }
        void set(std::string str) { _str = str; }
        std::string& getString() { return _str; }
        ~Entity() { std::cout << _str << " Distructor !!!" << std::endl; }

    private:
        std::string _str;
};

void normalPointer();
void pointerArithmatic();
int main()
{
    //normalPointer();
    pointerArithmatic();
    return 0;
}

void normalPointer()
{
    //We treat our memory as we want
    //Create some memory to hold data for Entity class, an integer and a charecter
    void* vp = new char[sizeof(Entity) + sizeof(int) + sizeof(char)];
    char* ptr = (char*)vp;

    //Now first create Entity Class then next 4 byte use to hold int data then 1 byte for char
    Entity* e = new(ptr) Entity("This is Entity Class"); 
    int* i = new(&ptr[sizeof(Entity)]) int(100);
    char* c = new(&ptr[sizeof(Entity)+sizeof(int)]) char('C');

    std::cout << "Entity Class : " << e->getString() << std::endl;
    std::cout << "Int : " << *i << std::endl;
    std::cout << "Char : " << *c << std::endl;

    e->~Entity();
    delete [] ptr;
}

void pointerArithmatic()
{
    //here we init 10 Entity class size of memory inside heap
    char* ptr = new char[size * sizeof(Entity)];

    //[NOTE : See new.cpp]
    //Here we actually create Entity class.
    for(int i = 0; i < size; i++)
        new(&ptr[i*sizeof(Entity)]) Entity(std::to_string(i));
    std::cout << std::endl;

    //Here we say that we want to treat this char* as Entity*
    //So when we say "e++" it mean it will advance address by sizeof(Entity)
    //also e[0] = first address and e[1] = first address + sizeof(Entity)
    Entity* e = (Entity*)ptr;
    std::cout << e[0].getString() << std::endl;

    //Calling Distructor manualy
    e = (Entity*)ptr;
    std::cout << std::endl;
    for(int i = 0; i < size; i++)
        e++->~Entity();

    delete [] ptr;
}
