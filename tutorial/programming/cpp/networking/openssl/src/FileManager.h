#ifndef _FILEMANAGER
#define _FILEMANAGER
#include <iostream>
#include <fstream>

enum OpMode{ READ, WRITE };

class FileManager
{
    public:
        FileManager();
        FileManager(const std::string fileName, OpMode mode);
            int getFileSize();
            bool readFile(const int buffSizeToRead, char* out, int& outLen);
            bool writeFile(char* inp, const int buffSizeToRead);
        ~FileManager();

    private:
        std::fstream _io;
        int _fileSize, _totalRW;
};
#endif
