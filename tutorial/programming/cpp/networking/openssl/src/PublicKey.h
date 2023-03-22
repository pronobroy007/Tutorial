#ifndef _DIFFHELLMANSIMULATION
#define _DIFFHELLMANSIMULATION
#include "OpensslHeader.h"

class PublicKey
{
    public:
        PublicKey();
            void load_key(std::string key_file_type, std::string key_file);
        ~PublicKey();

        /***************************************************************************************************** 
         * EVP_PKEY internal key may hold a private key, a public key, or both (a keypair), and along with those,
         * key parameters if the key type requires them. 
         *
         * The EVP_PKEY_new() function allocates an empty EVP_PKEY structure which is used by OpenSSL to store 
         * public and private keys. The reference count is set to 1.
         *
         * EVP_PKEY_up_ref() increments the reference count of key. 
         *
         * EVP_PKEY_dup() duplicates the key. The key must not be ENGINE based or a raw key,
         * otherwise the duplication will fail.
         *
         * EVP_PKEY_free() decrements the reference count of key and, if the reference count is zero,
         * frees it up. If key is NULL, nothing is done.
        *****************************************************************************************************/
        EVP_PKEY* _pkey;
    private:
};
#endif
