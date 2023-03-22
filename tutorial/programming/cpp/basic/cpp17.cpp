#include <cstdio>
#include <iostream>
#include <any>
#include <map>
#include <string>
#include <utility>

std::map<std::string, std::any> _map;

template<typename  T> T getData(std::string);
void setData(std::string, std::any);
int main()
{
    setData("int", 100);
    setData("string", std::string("Hello World"));

    std::cout << getData<int>("int") << std::endl;
    std::cout << getData<std::string>("string") << std::endl;
    return 0;
}

//store anny data type 
void setData(std::string name, std::any data)
{
    _map.insert(std::make_pair(name, data));
}

template<typename  T>
T getData(std::string name)
{
    T data = std::any_cast<T>(_map[name]);
    return data;
}
