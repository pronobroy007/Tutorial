#include "MAC.h"
#include "symmetric.h"
#include "FileManager.h"
#include "PublicKey.h"

void rsaPubKey();
void encryptDecryptFile();
void text();
void EncMac();

int main()
{
    //rsaPubKey();
    EncMac();
    //encryptDecryptFile();
    //text();
    
    unsigned char key[EVP_MAX_KEY_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH];
    //Symmetric::genKeyIV(key, iv);

    //unsigned char plaintext[] = "Currently, this function always outputs. However, in the forthcoming 0.9.7 release it will not place anything in the output buffer at all if padding is turned off. In such a case, if there is any buffered data, the function returns an error. Additionally,Version 0.9.7 adds an EVP_EncryptFinal_ex call that should be used when a context has been initialized by EVP_EncryptInit_ex.Example 6-3 shows the implementation of a function that takes a pointer to an initialized EVP cipher context, a buffer to encrypt, an associated length, and a pointer to an integer. The function then encrypts the data 100 bytes at a time into a heap-allocated buffer, which is the function's return value. The length of the resulting ciphertext is passed back in the address specified by the final parameter.The above example works well when we can afford to encrypt everything into a single buffer before processing the ciphertext. It doesn't work so well if we need to deal with ciphertext incrementally. For example, we might wish to send blocks of data as quickly as possible, and not wait for all data to be processed. Example 6-4 shows a solution for such a scenario. Data to be encrypted is sent to incremental_encrypt as needed. When there's data to be sent, incremental_encrypt calls incremental_send , which is simply a stub, but it can place those blocks currently encrypted on the network. When all data to be encrypted has been passed to incremental_encrypt, then incremental_finish is called.OpenSSL is primarily a library that is used by developers to include support for strong cryptography in their programs, but it is also a tool that provides access to much of its functionality from the command line. The command-line tool makes it easy to perform common operations, such as computing the MD5 hash of a file's contents. What's more, the command-line tool provides the ability to access much of OpenSSL's higher-level functionality from shell scripts on Unix or batch files on Windows. It also provides a simple interface for languages that do not have native SSL bindings, but can run shell commands.OpenSSL is primarily a library that is used by developers to include support for strong cryptography in their programs, but it is also a tool that provides access to much of its functionality from the command line. The command-line tool makes it easy to perform common operations, such as computing the MD5 hash of a file's contents. What's more, the command-line tool provides the ability to access much of OpenSSL's higher-level functionality from shell scripts on Unix or batch files on Windows. It also provides a simple interface for languages that do not have native SSL bindings, but can run shell commands.OpenSSL is primarily a library that is used by developers to include support for strong cryptography in their programs, but it is also a tool that provides access to much of its functionality from the command line. The command-line tool makes it easy o";

    unsigned char plaintext[] = "Currently, this function always outputs";
    const ssize_t sizePlaneText = sizeof(plaintext);
    unsigned char digesttext[50];
    //int ret = MAC::encryptHMACBuff("sha3-512", plaintext, sizePlaneText, digesttext, (char*)key, EVP_MAX_KEY_LENGTH);
    //for (int i = 0; i < 1024; i++)
        //printf("%02x", digesttext[i]);
    //std::cout << std::endl;

    //const int ret = MAC::encryptHMACFile("sha3-512", "Makefile", digesttext, key, EVP_MAX_KEY_LENGTH);
    //for (int i = 0; i < ret; i++)
    //    printf("%02x", digesttext[i]);
    //std::cout << std::endl;

    return 0;
}

void rsaPubKey()
{
    PublicKey pk;
    char sigFileName[] = "Sign";
    char pubKeyFileName[] = "pubKey", prpiKeyFileName[] = "priKey";
    char originalFileName[] = "Makefile", encryptFileName[] = "Encrypt", decryptFileName[] = "Decrypt";

    if(CryptoLib::genRsaKey(pubKeyFileName, prpiKeyFileName)) 
        std::cout << "Key generate successfully" << std::endl;

    pk.load_key("public", pubKeyFileName);
    if(CryptoLib::rsaEncrypt(pk._pkey, originalFileName, encryptFileName)) 
        std::cout << "Encrypt successfully" << std::endl;

    pk.load_key("private", prpiKeyFileName);
    if(CryptoLib::rsaDecrypt(pk._pkey, encryptFileName, decryptFileName)) 
        std::cout << "Decrypt successfully" << std::endl;

    unsigned char digesttext[50];
    int digestLen = CryptoLib::macEncryptFile("sha3-256", "Makefile", digesttext);
    pk.load_key("private", prpiKeyFileName);
    if(CryptoLib::rsaSign(pk._pkey, digesttext, digestLen, sigFileName)) 
        std::cout << "Sign successfully" << std::endl;

    pk.load_key("public", pubKeyFileName);
    if(CryptoLib::rsaVarify(pk._pkey, digesttext, digestLen, sigFileName)) 
       std::cout << "Verify successfully" << std::endl;
}

void EncMac()
{
    unsigned char plaintext[] = "Currently, this function always outputs. However, in the forthcoming 0.9.7 release it will not place anything in the output buffer at all if padding is turned off. In such a case, if there is any buffered data, the function returns an error. Additionally,Version 0.9.7 adds an EVP_EncryptFinal_ex call that should be used when a context has been initialized by EVP_EncryptInit_ex.Example 6-3 shows the implementation of a function that takes a pointer to an initialized EVP cipher context, a buffer to encrypt, an associated length, and a pointer to an integer. The function then encrypts the data 100 bytes at a time into a heap-allocated buffer, which is the function's return value. The length of the resulting ciphertext is passed back in the address specified by the final parameter.The above example works well when we can afford to encrypt everything into a single buffer before processing the ciphertext. It doesn't work so well if we need to deal with ciphertext incrementally. For example, we might wish to send blocks of data as quickly as possible, and not wait for all data to be processed. Example 6-4 shows a solution for such a scenario. Data to be encrypted is sent to incremental_encrypt as needed. When there's data to be sent, incremental_encrypt calls incremental_send , which is simply a stub, but it can place those blocks currently encrypted on the network. When all data to be encrypted has been passed to incremental_encrypt, then incremental_finish is called.OpenSSL is primarily a library that is used by developers to include support for strong cryptography in their programs, but it is also a tool that provides access to much of its functionality from the command line. The command-line tool makes it easy to perform common operations, such as computing the MD5 hash of a file's contents. What's more, the command-line tool provides the ability to access much of OpenSSL's higher-level functionality from shell scripts on Unix or batch files on Windows. It also provides a simple interface for languages that do not have native SSL bindings, but can run shell commands.OpenSSL is primarily a library that is used by developers to include support for strong cryptography in their programs, but it is also a tool that provides access to much of its functionality from the command line. The command-line tool makes it easy to perform common operations, such as computing the MD5 hash of a file's contents. What's more, the command-line tool provides the ability to access much of OpenSSL's higher-level functionality from shell scripts on Unix or batch files on Windows. It also provides a simple interface for languages that do not have native SSL bindings, but can run shell commands.OpenSSL is primarily a library that is used by developers to include support for strong cryptography in their programs, but it is also a tool that provides access to much of its functionality from the command line. The command-line tool makes it easy o";

    unsigned char key[EVP_MAX_KEY_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH];
    CryptoLib::genSymKeyIV(key, iv);

    const ssize_t sizePlaneText = sizeof(plaintext);
    unsigned char digesttext[sizePlaneText+100];

    //int ret = mac.encryptBuff("sha1", plaintext, sizePlaneText, digesttext);
    //int ret = CryptoLib::macEncryptFile("sha3-512", "Makefile", digesttext);
    //int ret = CryptoLib::hmacEncryptBuff("sha3-256", plaintext, sizePlaneText, digesttext, key, EVP_MAX_KEY_LENGTH);
    int ret = CryptoLib::hmacEncryptFile("sha3-256", "Makefile", digesttext, key, EVP_MAX_KEY_LENGTH);
    if(!ret) return;

    for (int i = 0; i < ret; i++)
        printf("%02x", digesttext[i]);
    std::cout << std::endl;
}

void encryptDecryptFile()
{
    unsigned char skey[EVP_MAX_KEY_LENGTH];
    unsigned char siv[EVP_MAX_IV_LENGTH];
    CryptoLib::genSymKeyIV(skey, siv);

    char* cipherName = (char*)"Null";
    char* inpFileName = (char*)"Makefile";
    char* encryptFileName = (char*)"Encrypt";
    char* decryptFileName = (char*)"Decrypt";

    CryptoLib::symEncryptFile(cipherName, inpFileName, encryptFileName, skey, siv);
    CryptoLib::symDecryptFile(cipherName, encryptFileName, decryptFileName, skey, siv);
}

void text()
{
    unsigned char skey[EVP_MAX_KEY_LENGTH];
    unsigned char siv[EVP_MAX_IV_LENGTH];
    CryptoLib::genSymKeyIV(skey, siv);

    //unsigned char plaintext[] = "The quick brown fox jumps over the lazy dog";
    unsigned char plaintext[] = "Currently, this function always outputs. However, in the forthcoming 0.9.7 release it will not place anything in the output buffer at all if padding is turned off. In such a case, if there is any buffered data, the function returns an error. Additionally,Version 0.9.7 adds an EVP_EncryptFinal_ex call that should be used when a context has been initialized by EVP_EncryptInit_ex.Example 6-3 shows the implementation of a function that takes a pointer to an initialized EVP cipher context, a buffer to encrypt, an associated length, and a pointer to an integer. The function then encrypts the data 100 bytes at a time into a heap-allocated buffer, which is the function's return value. The length of the resulting ciphertext is passed back in the address specified by the final parameter.The above example works well when we can afford to encrypt everything into a single buffer before processing the ciphertext. It doesn't work so well if we need to deal with ciphertext incrementally. For example, we might wish to send blocks of data as quickly as possible, and not wait for all data to be processed. Example 6-4 shows a solution for such a scenario. Data to be encrypted is sent to incremental_encrypt as needed. When there's data to be sent, incremental_encrypt calls incremental_send , which is simply a stub, but it can place those blocks currently encrypted on the network. When all data to be encrypted has been passed to incremental_encrypt, then incremental_finish is called.OpenSSL is primarily a library that is used by developers to include support for strong cryptography in their programs, but it is also a tool that provides access to much of its functionality from the command line. The command-line tool makes it easy to perform common operations, such as computing the MD5 hash of a file's contents. What's more, the command-line tool provides the ability to access much of OpenSSL's higher-level functionality from shell scripts on Unix or batch files on Windows. It also provides a simple interface for languages that do not have native SSL bindings, but can run shell commands.OpenSSL is primarily a library that is used by developers to include support for strong cryptography in their programs, but it is also a tool that provides access to much of its functionality from the command line. The command-line tool makes it easy to perform common operations, such as computing the MD5 hash of a file's contents. What's more, the command-line tool provides the ability to access much of OpenSSL's higher-level functionality from shell scripts on Unix or batch files on Windows. It also provides a simple interface for languages that do not have native SSL bindings, but can run shell commands.OpenSSL is primarily a library that is used by developers to include support for strong cryptography in their programs, but it is also a tool that provides access to much of its functionality from the command line. The command-line tool makes it easy o";

    const ssize_t sizePlaneText = sizeof(plaintext);
    unsigned char decriptText[sizePlaneText+100];
    unsigned char ciphertext[sizePlaneText+100];

    int eSize = CryptoLib::symEncryptBuff(plaintext, sizePlaneText, ciphertext, skey, siv);
    for(int i = 0; i < eSize; i++) std::cout << ciphertext[i];
    std::cout << "\n\n" << std::endl;

    int dSize = CryptoLib::symDecryptBuff(ciphertext, eSize, decriptText, skey, siv);
    for(int i = 0; i < dSize; i++) std::cout << decriptText[i];
    std::cout << std::endl;
    //std::cout << "PlaneTxt and Cipher Txt size : " << sizePlaneText << ", " << eSize << std::endl;
}
