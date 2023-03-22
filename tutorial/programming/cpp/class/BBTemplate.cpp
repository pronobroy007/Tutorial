#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <bits/stdc++.h>
#include <ctime>
#include <unistd.h>
#include <memory>
#include <map>


class BlackBoard
{
    public:
        BlackBoard() { }
        ~BlackBoard() { }

        template<typename T>
        T getData(std::string key)
        {
            return *(T*)_data[key].get();
        }

        template<typename T>
        void setData(std::string key, T value) {
           _data.insert(std::pair<std::string, std::shared_ptr<void>>(key, std::make_shared<T>(value)));
        }


    private: 
        std::map<std::string, std::shared_ptr<void>> _data;

};


template<typename T>
void PrintValue(T value)
{
    std::cout << "Value is : " << value << std::endl;
}

int main()
{
    BlackBoard bb;
    bb.setData<int>("int", 3);
    bb.setData<float>("float", 3.3);
    PrintValue(bb.getData<int>("int"));
    PrintValue(bb.getData<float>("float"));

    return 0;
}

