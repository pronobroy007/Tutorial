#ifndef _MAC
#define _MAC
#include "OpensslHeader.h"

namespace CryptoLib
{
    //Message Authenticate Algorithem
    int hmacEncryptFile(std::string digestName, std::string fileName, unsigned char* out, unsigned char* key, size_t keyLen);
    int hmacEncryptBuff(std::string digestName, unsigned char* inp, size_t inLen, unsigned char* out, unsigned char* key, size_t keyLen);
    int macEncryptFile(std::string digestName, std::string fileName, unsigned char* out);
    int macEncryptBuff(std::string digestName, unsigned char* inp, size_t inLen, unsigned char* out);

    //Symmetric Cipher
    void genSymKeyIV(unsigned char* key, unsigned char* iv);
    int symEncryptBuff(unsigned char* inp, size_t inLen, unsigned char* out, const unsigned char* key, const unsigned char* iv);
    int symDecryptBuff(unsigned char* inp, size_t inLen, unsigned char* out, const unsigned char* key, const unsigned char* iv);
    int symEncryptFile(std::string cipherName, std::string inpFileName, std::string outFileName, const unsigned char* key, const unsigned char* iv);
    int symDecryptFile(std::string cipherName, std::string inpFileName, std::string outFileName, const unsigned char* key, const unsigned char* iv);

    //Public Key Algorithem
    int genRsaKey(std::string pubkeyFileName, std::string priKeyFileName);
    int rsaEncrypt(EVP_PKEY* publicKey, std::string originalFileName, std::string encryptFileName);
    int rsaDecrypt(EVP_PKEY* privateKey, std::string encryptFileName, std::string decryptFileName);
    int rsaSign(EVP_PKEY* privateKey, const unsigned char* digest, size_t digestLen, std::string signFileName);
    int rsaVarify(EVP_PKEY* publicKey, const unsigned char* digest, size_t digestLen, std::string signFileName);
    void displayRsaKey(EVP_PKEY *pkey, bool is_private);
    void writeRsakey(EVP_PKEY *pkey, std::string key_file, bool is_private);
};
#endif
