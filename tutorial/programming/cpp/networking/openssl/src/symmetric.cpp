#include "symmetric.h"
#include <cstring>
#include <openssl/evp.h>
#include <openssl/rand.h>

int handleErrors(std::string msg)
{
    unsigned long errCode;

    std::cout << msg << std::endl;
    while((errCode = ERR_get_error()))
    {
        char *err = ERR_error_string(errCode, NULL);
        std::cout << err << std::endl;
    }
    return 0;
}


namespace CryptoLib 
{

    void genSymKeyIV(unsigned char *key, unsigned char *iv)
    {
        //Seed random number.....................
        if(!RAND_load_file("/dev/random", 1024*4))
            handleErrors("Error RAND_load_file() ");

        //Get random array EVP_MAX_KEY_LENGTH size.
        RAND_bytes(key, EVP_MAX_KEY_LENGTH);
        //Get random array EVP_MAX_IV_LENGTH size.
        RAND_bytes(iv, EVP_MAX_IV_LENGTH);
    }

    int symEncryptBuff(unsigned char* inp, size_t inLen, unsigned char* out, const unsigned char* key, const unsigned char* iv)
    {

        /***********************************************************************************************
         * //Specifying Key Length and Other Options
         * //---------------------------------------
         * // Many ciphers take a variable key length, which can be easily set after initialization using the 
         * // call EVP_CIPHER_CTX_set_key_length . For example, we can set the Blowfish key length to 64 bits, as follows:
         * EVP_EncryptInit(_ctx, EVP_bf_ecb(  ), NULL, NULL);
         * EVP_CIPHER_CTX_set_key_length(_ctx, 8);
         * EVP_EncryptInit(_ctx, NULL, key, NULL);
         * //Set IV length if default 12 bytes (96 bits) is not appropriate 
         * EVP_CIPHER_CTX_ctrl(_ctx, EVP_CTRL_GCM_SET_IVLEN, 16, NULL);
         * //Initialise key and IV 
         * EVP_EncryptInit(_ctx, NULL, key, iv);
         * //In this case, we set the key with a second call to EVP_EncryptInit after we specify the key length.
         * //When using this functionality, make sure you only set the key length to a valid value for the cipher.

         * //If we wish to check the default key length of a cipher object, we can use the call EVP_CIPHER_key_length .
         * //For example, the following will show us the default key length for Blowfish:
         * printf("%d\n", EVP_CIPHER_key_length(EVP_bf_ecb(  )));
         * //We can also check to see the length of the keys a cipher context is using:

         * printf("%d\n", EVP_CIPHER_CTX_key_length(_ctx));
         * //For other cipher parameters, OpenSSL provides a generic call, EVP_CIPHER_CTX_ctrl .
         * //Currently, this call can only set or query the effective key strength in RC2 or the number of rounds used in RC5.
         * int EVP_CIPHER_CTX_ctrl(EVP_CIPHER_CTX *ctx, int type, int arg, void *ptr);
        ***********************************************************************************************/

        ERR_load_crypto_strings();
        /***********************************************************************************************
         * Before we can begin encrypting or decrypting, we must allocate and initialize a cipher context.
         * The cipher context is a data structure that keeps track of all relevant state for the purposes 
         * of encrypting or decrypting data over a period of time. For example, we can have multiple 
         * streams of data encrypted in CBC mode. The cipher context will keep track of the key associated 
         * with each stream and the internal state that needs to be kept between messages for CBC mode.
        ***********************************************************************************************/
        EVP_CIPHER_CTX* ctx;

        if(!(ctx = EVP_CIPHER_CTX_new())) 
        {
            EVP_CIPHER_CTX_free(ctx);
            handleErrors("Error EVP_CIPHER_CTX_new() ");
            return 0;
        }
        /*********************************************************************************************** 
         * After allocating the context object and initializing it, we must set up the cipher context.
         * At this point, we generally determine whether the particular context will be used for encrypting 
         * or decrypting. It is possible to set up a context to do both,
        ***********************************************************************************************/
        if(EVP_EncryptInit(ctx, EVP_aes_128_cbc(), key, iv) != 1) 
        {
            handleErrors("Error to EVP_EncryptInit() ");
            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }

        int outputLen = 0, tmp = 0;
        //The function then encrypts the data 100 bytes at a time into a buffer.
        for(int i = 0; i < inLen/100; i++)
        {
            /*********************************************************************************************** 
             * When you have data to encrypt, you pass the data to the update function, along with a pointer to 
             * where you'd like any output to go. There may or may not be output as the result of an update. If the 
             * cipher can encrypt one or more entire blocks of data, it will do so. Any leftover data will be buffered 
             * and processed either during the next call to the update function or during the call to finalize. 
            ***********************************************************************************************/
            if(EVP_EncryptUpdate(ctx, &out[outputLen], &tmp, &inp[outputLen], 100) != 1)
            {
                handleErrors("Error to EVP_EncryptUpdate() : ");
                EVP_CIPHER_CTX_free(ctx);
                return 0;
            }
            outputLen += tmp;
        }

        //The function then encrypts remming data.
        if(inLen % 100)
        {
            //Encrypt remming bytes.
            int rem = inLen - outputLen;
            if(EVP_EncryptUpdate(ctx, &out[outputLen], &tmp, &inp[outputLen], rem) != 1)
            {
                handleErrors("Error to EVP_EncryptUpdate() : ");
                EVP_CIPHER_CTX_free(ctx);
                return 0;
            }
            outputLen += tmp;
        }

        //When calling finalize, any leftover data is padded and encrypted.
        if(EVP_EncryptFinal(ctx, &out[outputLen], &tmp) != 1)
            handleErrors("Error to EVP_EncryptFinal() : ");

        outputLen += tmp;
        EVP_CIPHER_CTX_free(ctx);
        return outputLen;
    }

    int symDecryptBuff(unsigned char* inp, size_t inLen, unsigned char* out, const unsigned char* key, const unsigned char* iv)
    {
        ERR_load_crypto_strings();
        EVP_CIPHER_CTX* ctx;

        if(!(ctx = EVP_CIPHER_CTX_new())) 
        {
            handleErrors("Error EVP_CIPHER_CTX_new() ");
            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }

        if(EVP_DecryptInit(ctx, EVP_aes_128_cbc(), key, iv) != 1)
        {
            handleErrors("Error to EVP_DecryptInit() ");
            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }

        int outputLen = 0, tmp = 0;

        //Init Deryption
        //if(EVP_DecryptInit(_ctx, EVP_aes_128_cbc(), _key, _iv) != 1) handleErrors("Error EVP_DecryptInit(tmp)");

        if(EVP_DecryptUpdate(ctx, out, &tmp, inp, inLen) != 1)
        {
            handleErrors("Error to EVP_DecryptUpdate() ");
            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }
        outputLen = tmp;

        if(EVP_DecryptFinal(ctx, &out[outputLen], &tmp) != 1) 
            handleErrors("Error to EVP_DecryptFinal() ");

        outputLen += tmp;

        EVP_CIPHER_CTX_free(ctx);
        return outputLen;
    }

    int symEncryptFile(std::string cipherName, std::string inpFileName, std::string outFileName, const unsigned char* key, const unsigned char* iv)
    {
        ERR_load_crypto_strings();
        EVP_CIPHER_CTX* ctx;

        if(!(ctx = EVP_CIPHER_CTX_new())) 
        {
            EVP_CIPHER_CTX_free(ctx);
            return handleErrors("Error EVP_CIPHER_CTX_new() ");
        }

        if(EVP_EncryptInit(ctx, EVP_aes_128_cbc(), key, iv) != 1)
        {
            EVP_CIPHER_CTX_free(ctx);
            return handleErrors("Error to EVP_EncryptInit() : ");
        }

        int totalRead = 0, outputLen = 0;
        const int readSize = EVP_CIPHER_CTX_block_size(ctx);
        char plaintext[readSize];
        unsigned char ciphertext[readSize];
        FileManager readFile(inpFileName, OpMode::READ), writeFile(outFileName, OpMode::WRITE);

        while (true) 
        {
            if(!readFile.readFile(readSize, plaintext, totalRead)) break;
            //for(int i = 0; i < totalRead; i++) std::cout << plaintext[i];
            
            if(EVP_EncryptUpdate(ctx, ciphertext, &outputLen, (unsigned char*)plaintext, totalRead) != 1)
            {
                EVP_CIPHER_CTX_free(ctx);
                return handleErrors("Error to EVP_EncryptUpdate() : ");
                return 0;
            }

            //for(int i = 0; i < totalRead; i++) std::cout << ciphertext[i];
            //std::cout << "Total read and write : " << totalRead << ", " << outputLen;
            if(outputLen) writeFile.writeFile((char*)ciphertext, outputLen);
        }

        if(EVP_EncryptFinal(ctx, ciphertext, &outputLen) != 1)
        {
            EVP_CIPHER_CTX_free(ctx);
            return handleErrors("Error to EVP_EncryptFinal() ");
        }
        //std::cout << "Total write : " << outputLen;
        if(outputLen) writeFile.writeFile((char*)ciphertext, outputLen);

        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    int symDecryptFile(std::string cipherName, std::string inpFileName, std::string outFileName, const unsigned char* key, const unsigned char* iv)
    {
        ERR_load_crypto_strings();
        EVP_CIPHER_CTX* ctx;

        if(!(ctx = EVP_CIPHER_CTX_new())) 
            return handleErrors("Error EVP_CIPHER_CTX_new() ");

        if(EVP_DecryptInit(ctx, EVP_aes_128_cbc(), key, iv) != 1)
        {
            EVP_CIPHER_CTX_free(ctx);
            return handleErrors("Error to EVP_DecryptInit() ");
        }

        int totalRead = 0, outputLen = 0;
        const int readSize = EVP_CIPHER_CTX_block_size(ctx);
        char ciphertext[readSize];
        unsigned char plaintext[readSize];
        FileManager readFile(inpFileName, OpMode::READ), writeFile(outFileName, OpMode::WRITE);

        while (true) 
        {
            if(!readFile.readFile(readSize, ciphertext, totalRead)) break;
            //for(int i = 0; i < totalRead; i++) std::cout << ciphertext[i];

            if(EVP_DecryptUpdate(ctx, plaintext, &outputLen, (unsigned char*)ciphertext, totalRead) != 1)
            {
                EVP_CIPHER_CTX_free(ctx);
                return handleErrors("Error to EVP_DecryptUpdate() ");
            }

            //for(int i = 0; i < outputLen; i++) std::cout << plaintext[i];
            //std::cout << "      " << outputLen << std::endl;
            if(outputLen) writeFile.writeFile((char*)plaintext, outputLen);
        }

        if(EVP_DecryptFinal(ctx, plaintext, &outputLen) != 1) 
            handleErrors("Error to EVP_DecryptFinal() ");

        if(outputLen) writeFile.writeFile((char*)plaintext, outputLen);

        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }
}

Symmetric::Symmetric() { }

bool Symmetric::init()
{
    _blockSize = 0;
    ERR_load_crypto_strings();

    if(!RAND_load_file("/dev/random", 1024))
    {
        handleErrors("Error RAND_load_file() ");
    }

    if(!(_ctx = EVP_CIPHER_CTX_new())) 
    {
        handleErrors("Error EVP_CIPHER_CTX_new() ");
        return false;
    }

    //Init Encryption
    selectRandNum(_key, EVP_MAX_KEY_LENGTH);
    selectRandNum(_iv, EVP_MAX_IV_LENGTH);
    return true;
}

unsigned char* Symmetric::getIV() { return _iv; }
unsigned char* Symmetric::getKey() { return _key; }
int Symmetric::getBlockSize() { return EVP_CIPHER_CTX_block_size(_ctx); }
void Symmetric::selectRandNum(unsigned char* key, int keyLen) { RAND_bytes(key, keyLen); }


int Symmetric::setEncrypt(const unsigned char* key, const unsigned char* iv)
{
    if(EVP_EncryptInit(_ctx, EVP_aes_128_cbc(), key, iv) != 1)
    {
        handleErrors("Error to EVP_EncryptInit() : ");
        return  -1;
    }
    return 1;
}

int Symmetric::setDecrypt(const unsigned char* key, const unsigned char* iv)
{
    if(EVP_DecryptInit(_ctx, EVP_aes_128_cbc(), key, iv) != 1)
    {
        handleErrors("Error to EVP_DecryptInit() : ");
        return  -1;
    }
    return 1;

}


int Symmetric::incremental_encrypt(unsigned char* inp, int inLen, unsigned char* out)
{
    int outputLen = 0;
    //The function then encrypts the data 100 bytes at a time into a buffer.
    if(EVP_EncryptUpdate(_ctx, out, &outputLen, inp, inLen) != 1)
    {
        handleErrors("Error to EVP_EncryptUpdate() : ");
        return 0;
    }

    return outputLen;
}

int Symmetric::incremental_encrypt_finish(unsigned char* inp, unsigned char* out)
{
    int outputLen = 0;
    if(EVP_EncryptFinal(_ctx, out, &outputLen) != 1)
    {
        handleErrors("Error to EVP_EncryptFinal() : ");
        return 0;
    }
    return outputLen;
}









Symmetric::~Symmetric() 
{ 
    EVP_CIPHER_CTX_free(_ctx);
}
