#include "helperFunction.h"

HelperFunction::HelperFunction()
{
}

bool HelperFunction::parse(std::string src,char delemeter, std::vector<std::string> &buffer)
{
    if(!src.empty())
    {
        //Count Size of buffer array.
        int row = buffer.size();

        std::string str;
        int val = 0, i = 0;
        while(src[i]  != '\0')
        {
            if(src[i] == delemeter)
            {
                if(!str.empty())
                {
                    buffer[val] = str;
                    str.clear();
                    val++;
                }
                else 
                    return false;
            }
            else if (val >= row)
                break;
            else
                str += src[i];
            
            i++;
        }
        return true;    
    }
    else 
        return false;
}

bool HelperFunction::parse(std::string src, std::vector<std::vector<std::string>> &buffer)
{
    if(!src.empty())
    {
        std::vector<std::string> buff;
        std::string str;
        int i = 0;
        while(src[i] != '\0')
        {
			//This is for new line
            if((int)src[i] == 10 && int(src[i+1]) == 13)
            {
                buff.push_back(str);
                str.clear();
				i++;
            }
			//27 = Esc button.
            else if(int(src[i]) == 27)
            {
                if(buff.empty())
                    return false;
                buffer.push_back(buff);
                buff.clear();
            }
			//End fo string.
			else if(i == src.size() -1)
			{
				if(buffer.empty())
					return false;
				break;
			}
            else
                str += src[i];

			i++;
        }

        return true;
    }

    return false;
}


void HelperFunction::sort(std::vector<std::string> &data)
{
    if(data[0] > data[1])
    {
        std::string temp = data[0];
        data[0] = data[1];
        data[1] = temp;
    }
}



HelperFunction::~HelperFunction()
{
} 
