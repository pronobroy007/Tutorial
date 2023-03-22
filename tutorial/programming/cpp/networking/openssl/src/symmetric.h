#ifndef _SYMMETRIC
#define _SYMMETRIC

#include "OpensslHeader.h"
#include "FileManager.h"
#include <utility>

class Symmetric
{
    public:
        Symmetric();
            bool init();
            int getBlockSize();
            unsigned char* getIV();
            unsigned char* getKey();
            //void handleErrors(std::string msg);
            //Get random number for Key and IV.
            void selectRandNum(unsigned char* key, int keyLen);

            int setEncrypt(const unsigned char* key, const unsigned char* iv);
            int setDecrypt(const unsigned char* key, const unsigned char* iv);

            int incremental_encrypt(unsigned char* inp, int inLen, unsigned char* out);
            int incremental_encrypt_finish(unsigned char* inp, unsigned char* out);


        ~Symmetric();

    private:
        int _blockSize;
        EVP_CIPHER_CTX* _ctx;
        unsigned char _key[EVP_MAX_KEY_LENGTH], _iv[EVP_MAX_IV_LENGTH];
};
#endif
