#include "MAC.h"
#include "FileManager.h"

namespace CryptoLib
{
    int hmacEncryptBuff(std::string digestName, unsigned char* inp, size_t inLen, unsigned char* out, unsigned char* key, size_t keyLen)
    {
        unsigned int outputLen = 0;
        const EVP_MD* m = EVP_get_digestbyname(digestName.c_str());
        HMAC(m, key, keyLen, inp, inLen, out, &outputLen);
        return outputLen;
    }

    int hmacEncryptFile(std::string digestName, std::string fileName, unsigned char* out, unsigned char* key, size_t keyLen)
    {
        ERR_load_crypto_strings();
        int  totalRead = 0;
        std::size_t outputLen = 0;
        const int readSize = 1024;
        char plaintext[readSize];
        FileManager readFile(fileName.c_str(), OpMode::READ);
        

        /*******************************************************************
        * Here we difine which Message Authentication Code (MAC) we wish to use 
        * for ex hmac, cmag, gmac etc..
        *******************************************************************/
        EVP_MAC *mac = EVP_MAC_fetch(NULL, "hmac", NULL); 
        if(!mac) std::cout << "Error EVP_MAC_fetch() " << std::endl;

        /*********************************************************************************************************
        * If we set EVP_MAC to hmac then we need to define a OSSL_PARAM for mac(MD5, sha3 etc) and a key
        * If we set EVP_MAC to cmac then we need to define a OSSL_PARAM for cipher(aes_128_cbc) cbc mode and a key
        *********************************************************************************************************/
        const char *cipher = nullptr;
        const char *digest = digestName.c_str();
        
        OSSL_PARAM params[3];
        size_t params_n = 0;

        if (cipher != NULL) params[params_n++] = OSSL_PARAM_construct_utf8_string("cipher", (char*)cipher, 0);
        if (digest != NULL) params[params_n++] = OSSL_PARAM_construct_utf8_string("digest", (char*)digest, 0);
        params[params_n] = OSSL_PARAM_construct_end(); 
        /*********************************************************************************************************/

        /********************************************************************************************************* 
         * The cipher context is a data structure that keeps track of all relevant state for the purposes 
         * of encrypting or decrypting data over a period of time.
        *********************************************************************************************************/
        EVP_MAC_CTX* ctx = EVP_MAC_CTX_new(mac);
        if(!ctx) std::cout << "Error EVP_MAC_CTX_new() " << std::endl;

        if(!EVP_MAC_init(ctx, key, keyLen, params)) goto err;

        while (true) 
        {
            if(!readFile.readFile(readSize, plaintext, totalRead)) break;
            /*************************************************************************
             * All of the data can be passed to EVP_MAC_update at once, or it can be 
             * passed incrementally by calling the function as many times as necessary.
            *************************************************************************/
            if(!EVP_MAC_update(ctx, (unsigned char*)plaintext, totalRead)) goto err;
        }

        /*************************************************************
         * Calling HMAC_Final will compute the MAC and return the hash.
        **************************************************************/
        if(!EVP_MAC_final(ctx, (unsigned char*)plaintext, &outputLen, sizeof(plaintext))) goto err;

        //Copy output
        for (int i = 0; i < outputLen; i++) out[i] = plaintext[i];


        EVP_MAC_free(mac);
        EVP_MAC_CTX_free(ctx);
        return outputLen;

         err:
            EVP_MAC_CTX_free(ctx);
            EVP_MAC_free(mac);
            fprintf(stderr, "Something went wrong\n");
            //char *err = ERR_error_string(ERR_get_error(), NULL);
            char *err = ERR_error_string(ERR_get_error(), NULL);
            std::cout << err << std::endl;
            //ERR_print_errors_fp(stderr);
            return 0;
    }

    int macEncryptFile(std::string digestName, std::string fileName, unsigned char* out)
    {
        EVP_MD_CTX* ctx = EVP_MD_CTX_new();
        const EVP_MD* m = EVP_get_digestbyname(digestName.c_str());
        if(!m) 
        {
            EVP_MD_CTX_free(ctx);
            std::cout << "Error EVP_get_digestbyname() " << std::endl;
            return false;
        }

        EVP_DigestInit(ctx, m);

        int  totalRead = 0;
        unsigned int outputLen = 0;
        const int readSize = 1024;
        char plaintext[readSize];
        FileManager readFile(fileName.c_str(), OpMode::READ);

        while (true) 
        {
            if(!readFile.readFile(readSize, plaintext, totalRead)) break;
            EVP_DigestUpdate(ctx, plaintext, totalRead);
        }

        EVP_DigestFinal(ctx, out, &outputLen);

        EVP_MD_CTX_free(ctx);
        return outputLen;

    }

    int macEncryptBuff(std::string digestName, unsigned char* inp, size_t inLen, unsigned char* out)
    {
        EVP_MD_CTX* ctx = EVP_MD_CTX_new();
        OpenSSL_add_all_digests();
        const EVP_MD* m = EVP_get_digestbyname(digestName.c_str());
        if(!m) 
        {
            EVP_MD_CTX_free(ctx);
            std::cout << "Error EVP_get_digestbyname() " << std::endl;
            return false;
        }

        unsigned int outputLen;
        EVP_DigestInit(ctx, m);
        //std::cout << "lest byte write : " << EVP_MD_CTX_block_size(ctx) << std::endl;
        EVP_DigestUpdate(ctx, inp, inLen);
        EVP_DigestFinal(ctx, out, &outputLen);
        //std::cout << "Total byte read and write : " << inLen << ", "<< outputLen << std::endl;

        EVP_MD_CTX_free(ctx);
        return outputLen;
    }

}

