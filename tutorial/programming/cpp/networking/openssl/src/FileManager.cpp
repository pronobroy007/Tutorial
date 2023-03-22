#include "FileManager.h"

FileManager::FileManager() {}

FileManager::FileManager(std::string fileName, OpMode mode) : _fileSize(0), _totalRW(0)
{ 
    switch (mode) 
    {
        case OpMode::READ :
            _io.open(fileName.c_str(), std::ios::binary | std::ios::in);  
            if(!_io) 
            {
                std::cout << "Faild to open '" << fileName << "' file !!!!!!!!" << std::endl;
                return;
            }

            //Get Total file size......
            _io.seekg(0, std::ios::end);
            _fileSize = _io.tellg();
            _io.seekg(0, std::ios::beg);
            break;

        case OpMode::WRITE :
            _io.open(fileName.c_str(), std::ios::binary | std::ios::app | std::ios::out);  
            if(!_io) 
            {
                std::cout << "Faild to open '" << fileName << "' file !!!!!!!!" << std::endl;
                return;
            }
            break;
    }

}

int FileManager::getFileSize() { return _fileSize; }

bool FileManager::readFile(const int buffSizeToRead, char* out, int& outLen)
{
    if(_totalRW <= _fileSize - buffSizeToRead)
    {
        outLen = buffSizeToRead;
        _totalRW += outLen;
        _io.read(out, outLen);
        return true;
    }
    else if(_totalRW < _fileSize)
    {
        outLen = _fileSize - _totalRW;
        _totalRW += outLen;
        _io.read(out, outLen);
        return true;
    }

    return false;
}

bool FileManager::writeFile(char* inp, const int buffSizeToRead)
{
    _io.write(inp,buffSizeToRead);
    return true;
}

FileManager::~FileManager() 
{
    if(_io) _io.close();
}
