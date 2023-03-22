#include <iostream>
#include <string>

//Calling Base class constructor form Driven class
class AB
{
    public :
        AB(std::string name) {std::cout << name << std::endl;}
};

class E : public AB
{
    public :
        E () : AB("hello") {};

};



class A
{
	public:
		A() { std::cout << "base class constructor " << std::endl; }
            virtual void print() { std::cout << "This is Base class A" << std::endl; }
            void show()	{ std::cout << "This is Base class Show function" << std::endl; }
		virtual ~A() { std::cout << "base class Distructor" << std::endl; }
};

class B : public A 
{
	public:
		B() { std::cout << "Driven class constructor " << std::endl; }
            void print() { std::cout << "This is Driven class B" << std::endl; }
            void show() { std::cout << "This is Driven class Show function" << std::endl; }
		~B() { std::cout << "Driven class Distructor" << std::endl; }
};



int main()
{
    //Calling Base class constructor form Driven class
	std::cout << "Calling Base Class constructor Form driven class : " << std::endl;
	std::cout << "..................................................." << std::endl;
	{
		E dri;
	}
	std::cout << std::endl;


	std::cout << "This is Base class : " << std::endl;
	std::cout << "......................." << std::endl;
	{
		A base;
		base.print();
		base.show();
	}
	std::cout << std::endl;

	std::cout << "This is Driven class : " << std::endl;
	std::cout << "........................" << std::endl;
	{
		B driven;
		driven.print();
		driven.show();
	}
	std::cout << std::endl;

	std::cout << "Thsi base class make a type of driven class : " << std::endl;
	std::cout << ".............................................." << std::endl;
	{
		A *base;
		B driven;
		base = &driven;
		//This print function will call driven class print function not base class print() function.
		base->print();
		base->show();
	}

	//This is another way to call virtual function.
	//Here problem is base class constructor is call but driven class disturctor dosen't call.
	//For this make distructor as virtual function.
	std::cout << std::endl;
	{
		A *base = new B;
		base->print();
		base->show();
		delete base;
	}

	return 0;
}















