#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

void vector_cont();
void list_cont();

int main()
{
	std::cout << "\nThis is Map Associative Container " << std::endl;
	std::cout << "......................................" << std::endl;
	vector_cont();
	list_cont();
	std::cout << "......................................" << std::endl;
	return 0;
}

void list_cont()
{
    std::cout << "\nFor List : " << std::endl;
    std::cout << "----------" << std::endl;

    std::list<int> _lint = {1, 15, 3, 4};
    _lint.push_back(100);       //1 2 3 4 100
    _lint.push_front(10);       //10 1 15 3 4 100

    std::list<int> :: iterator it = _lint.begin();
    std::advance(it, 2);        //now it point at "15"
    _lint.insert(it, 5);        //10 1 5 2 3 4 100
    std::cout << std::endl;

    //Pring..............
    for(it = _lint.begin(); it != _lint.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    _lint.pop_back();
    _lint.pop_front();
    
    for(it = _lint.begin(); it != _lint.end();)
    {
        if(*it == 3)
            it = _lint.erase(it);
        else
            it++;
    }

    //Print..............
    for(it = _lint.begin(); it != _lint.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}




void vector_cont()
{
	std::vector<int> _int;

	//Insert element into vector.
	_int.push_back(4);
	_int.push_back(3);
	_int.push_back(30);


	//Delete 2nd element.
	std::cout << "Vector size : " << _int.size() << std::endl;
	 _int.erase (_int.begin()+1);
	std::cout << "Vector size : " << _int.size() << std::endl;
	std::cout << std::endl;


	//Random access of element.
	std::cout << "Frist Element : " << _int[0] << std::endl;
	//Here _int.at() function throw an exception if element is out of range.
	std::cout << "Second Element : " << _int.at(1) << std::endl;

}

