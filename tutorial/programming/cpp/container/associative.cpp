// Find : 		O(log n) 	and 	for string key O(m log n)
// Insertion : 	O(log n)
// Deletion : 	O(log n)
// Map dosen't allow any duplicate key element.

#include <iostream>
#include <map>

void map_cont();
void set_cont();

int main()
{
	std::cout << "\nThis is Map Associative Container " << std::endl;
	std::cout << "......................................" << std::endl;
	map_cont();
	std::cout << "......................................" << std::endl;



	return 0;
}

void map_cont()
{
	std::map<char, int> _int({{'z', 30}});

	//Insert element into map...................
	_int.insert(std::pair <char, int> ('a', 1));
	_int.insert(std::pair <char, int> ('b', 2));
	_int.insert(std::make_pair('c', 3));
	_int.insert(std::make_pair('d', 3));
    _int.insert({'e', 10});

	//Total size of _int....................
	std::cout << "Total size of map _int : " << _int.size() << std::endl;

	//Find a particular item..................
	std::cout << "Find a particular value : " << _int['b'] << std::endl;

	std::map<char, int>::iterator ite = _int.find('d');
	std::cout << "Find a using iterator : " << ite->first << std::endl;

	//print all element..................
    int i = 0;
	for (std::map<char, int>::iterator it = _int.begin(); it != _int.end(); it++, i++)
    {
		std::cout << i << " ";
		std::cout << "Key : " << it->first << "		";
        std::cout << "Value : " << it->second << std::endl;
    }
}


