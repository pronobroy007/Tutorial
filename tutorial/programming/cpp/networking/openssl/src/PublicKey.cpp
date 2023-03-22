#include "PublicKey.h"
#include "FileManager.h"


namespace CryptoLib 
{

    void displayRsaKey(EVP_PKEY *pkey, bool is_private) 
    {

        /*
         *   The functions EVP_PKEY_print_public(), EVP_PKEY_print_private() and
         *   EVP_PKEY_print_params() print out the public, private or parameter
         *   components of key pkey respectivel
         *
         *   int EVP_PKEY_print_public(BIO *out, const EVP_PKEY *pkey,
         *                     int indent, ASN1_PCTX *pctx);
         *   int EVP_PKEY_print_private(BIO *out, const EVP_PKEY *pkey,
         *                      int indent, ASN1_PCTX *pctx);
         *
         *   The parameter indent indicates how far the printout should be indented.
         *   The pctx parameter allows the print output to be finely tuned by using ASN1
         *   printing options. If pctx is set to NULL then default values will be used.
         */

        BIO *bio_out =  BIO_new_fp(stdout, BIO_NOCLOSE);
        if ( is_private )
            EVP_PKEY_print_private(bio_out, pkey, 0, NULL);
        else
            EVP_PKEY_print_public(bio_out, pkey, 0, NULL);
        BIO_free(bio_out);
    }

    void writeRsakey(EVP_PKEY *pkey, std::string key_file, bool is_private)
    {

        /*
         *   int PEM_write_bio_PrivateKey(BIO *bp, EVP_PKEY *x, const EVP_CIPHER *enc,
         *                        unsigned char *kstr, int klen,
         *                        pem_password_cb *cb, void *u);
         *   int PEM_write_bio_PUBKEY(BIO *bp, EVP_PKEY *x);
         *
         *   typedef int pem_password_cb (char *buf, int size, int rwflag, void *userdata);
         *                  pem_password_cb *callback, void *u);
         */

        BIO *bio_out = BIO_new_file(key_file.c_str(), "w");
        if ( is_private )
            PEM_write_bio_PrivateKey(bio_out, pkey, NULL, NULL, 0, 0, NULL);
        else
            PEM_write_bio_PUBKEY(bio_out, pkey);
        BIO_free(bio_out);
    }

    int genRsaKey(std::string pubkeyFileName, std::string priKeyFileName)
    {
        EVP_PKEY* pkey = NULL;
        OSSL_PARAM params[3];
        unsigned int primes = 3;
        unsigned int bits = 2048;

        /*The key algorithm context must be created using EVP_PKEY_CTX_new(3) or variants thereof*/
        EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new_from_name(NULL, "RSA", NULL);
        if(!pctx) std::cout << "Error EVP_PKEY_CTX_new_from_name() " << std::endl;



        /*initializes a public key algorithm context ctx for a key generation operation.*/
        if(EVP_PKEY_keygen_init(pctx) <= 0) std::cout << "Error EVP_PKEY_keygen_init() " << std::endl;
        //if(EVP_PKEY_keygen_init(pctx) <= 0) return handleErrors("Error EVP_PKEY_keygen_init()");



        /*
         * After initialization, generation parameters may be provided with EVP_PKEY_CTX_ctrl(3) 
         * or EVP_PKEY_CTX_set_params(3), or any other function described in those manuals.
         *
         * bits" (OSSL_PKEY_PARAM_RSA_BITS) <unsigned integer> 
         *      The value should be the cryptographic length for the RSA cryptosystem, in bits.
         *
         * "primes" (OSSL_PKEY_PARAM_RSA_PRIMES) <unsigned integer>
         *     The value should be the number of primes for the generated RSA key.
         *     The default is 2. It isn't permitted to specify a larger number of primes than 10.
         *     Additionally, the number of primes is limited by the length of the key being 
         *     generated so the maximum number could be less. Some providers may only support a value of 2.
        */
        params[0] = OSSL_PARAM_construct_uint("bits", &bits);
        params[1] = OSSL_PARAM_construct_uint("primes", &primes);
        params[2] = OSSL_PARAM_construct_end();
        if(!EVP_PKEY_CTX_set_params(pctx, params)) std::cout << "Error EVP_PKEY_CTX_set_params() " << std::endl;
        //EVP_PKEY_CTX_set_rsa_keygen_bits(pctx, bits);
        


        /*
         * The resulting key parameters or key are written to *ppkey. If *ppkey is NULL when this function is called,
         * it will be allocated, and should be freed by the caller when no longer useful, using EVP_PKEY_free(3).
        */
        if(EVP_PKEY_generate(pctx, &pkey) <= 0) std::cout << "Error EVP_PKEY_generate() " << std::endl;

        /*
         * The functions EVP_PKEY_print_public(), EVP_PKEY_print_private() and EVP_PKEY_print_params()
         * print out the public, private or parameter components of key pkey respectively.
         * The key is sent to BIO out in human readable form. The parameter indent indicates how 
         * far the printout should be indented.
         *
         * Example :
         * ---------
         *   FILE *pubKey, *priKey;
         *   pubKey = fopen("pubkey", "wb");
         *   priKey = fopen("prikey", "wb");
         *   if(!pubKey) std::cout << "failed to open pubkey file" <<  std::endl;
         *   if(!priKey) std::cout << "failed to open prikey file" <<  std::endl;
         *
         *   ASN1_PCTX *actx = ASN1_PCTX_new();
         *   EVP_PKEY_print_public_fp(pubKey, pkey, 0, actx);
         *   EVP_PKEY_print_private_fp(priKey, pkey, 0, actx);
         *   fclose(pubKey);
         *   fclose(priKey);
         *
         *
         * The functions EVP_PKEY_print_public_fp(), EVP_PKEY_print_private_fp() and 
         * EVP_PKEY_print_params_fp() do the same as the BIO based functions but use FILE fp instead.
        */
        //PublicKey::display_key(_pkey, false);
        writeRsakey(pkey, pubkeyFileName, false);
        writeRsakey(pkey, priKeyFileName, true);

        EVP_PKEY_CTX_free(pctx);
        EVP_PKEY_free(pkey);
        return 1;
    }


    int rsaEncrypt(EVP_PKEY* pkey, std::string originalFileName, std::string encryptFileName) 
    {
        //Load EVP_PKEY from pubKey file
        //load_key("public", "pubKey");

       // display_key(pkey, false);
        
        if(pkey == nullptr) 
        {
            std::cout << "pkey has not been generated or loaded" << std::endl;
            return 0;
        }


        /*
        *  Step 1 : new ctx object
        *           EVP_PKEY_CTX *EVP_PKEY_CTX_new(EVP_PKEY *pkey, ENGINE *e);
        */
        EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new(pkey, NULL);
        if (!pctx) 
        {
            std::cout << "EVP_PKEY_CTX_new() Error" << std::endl;
            return 0;
        }
     

        /*
         *  Step 2 : Initializ public key algorithm
         *           int EVP_PKEY_encrypt_init(EVP_PKEY_CTX *ctx)
         */

        if(EVP_PKEY_encrypt_init(pctx) <= 0)
        {
            EVP_PKEY_CTX_free(pctx);
            EVP_PKEY_free(pkey);
            std::cout << "EVP_PKEY_encrypt_init() Error" << std::endl;
            return 0;
        }


        /*
         *  Step 3 : Perform public key encryption
         *           int EVP_PKEY_encrypt(EVP_PKEY_CTX *ctx, unsigned char *out, size_t *outlen,
         *                                const unsigned char *in, size_t inlen);
         *
         *  void *OPENSSL_malloc(size_t num)
         *  void  OPENSSL_free(void *addr)
         */

        int totalRead = 0;
        size_t outputLen = 0;
        const int readSize = 245; 
        unsigned char plaintext[readSize];
        FileManager readFile(originalFileName, OpMode::READ), writeFile(encryptFileName, OpMode::WRITE);

        while (true) 
        {
            if(!readFile.readFile(readSize, (char*)plaintext, totalRead)) break;
            //for(int i = 0; i < totalRead; i++) std::cout << ciphertext[i];

            /* Determine buffer length */
            EVP_PKEY_encrypt(pctx, NULL, &outputLen, plaintext, totalRead);
            unsigned char ciphertext[outputLen];

            if(EVP_PKEY_encrypt(pctx, ciphertext, &outputLen, plaintext, totalRead) <= 0)
            {
                std::cout << "Error to EVP_PKEY_encrypt() " << std::endl;
                EVP_PKEY_CTX_free(pctx);
                EVP_PKEY_free(pkey);
                return 0;
            }

            //for(int i = 0; i < outputLen; i++) std::cout << plaintext[i];
            //std::cout << "      " << outputLen << std::endl;
            if(outputLen) writeFile.writeFile((char*)ciphertext, outputLen);
        }

        EVP_PKEY_CTX_free(pctx);
        EVP_PKEY_free(pkey);
        return 1;

    }

    int rsaDecrypt(EVP_PKEY* pkey, std::string encryptFileName, std::string decryptFileName)
    {
        int err;
        
        if(pkey == nullptr) 
        {
            std::cout << "pkey has not been generated or loaded" << std::endl;
            return 0;
        }

         /*
         *  Step 1 : new ctx object
         *           EVP_PKEY_CTX *EVP_PKEY_CTX_new(EVP_PKEY *pkey, ENGINE *e);
         */

        EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new(pkey, NULL);
        if (!pctx) 
        {
            std::cout << "EVP_PKEY_CTX_new() Error" << std::endl;
            return 0;
        }
     
        /*
         *  Step 2 : Initializ public key algorithm
         *           int EVP_PKEY_encrypt_init(EVP_PKEY_CTX *ctx)
         */

        err = EVP_PKEY_decrypt_init(pctx);
        if(err <= 0)
        {
            EVP_PKEY_CTX_free(pctx);
            EVP_PKEY_free(pkey);
            std::cout << "EVP_PKEY_decrypt_init() Error" << std::endl;
            return 0;
        }

        /*
         *  Step 3 : Perform public key encryption
         *           int EVP_PKEY_encrypt(EVP_PKEY_CTX *ctx,
         *                                unsigned char *out, size_t *outlen,
         *                                const unsigned char *in, size_t inlen);
         *
         *  void *OPENSSL_malloc(size_t num)
         *  void  OPENSSL_free(void *addr)
         */

        int totalRead = 0;
        size_t outputLen = 0;
        const int readSize = EVP_PKEY_get_size(pkey); 
        unsigned char plaintext[readSize];
        FileManager readFile(encryptFileName, OpMode::READ), writeFile(decryptFileName, OpMode::WRITE);

        while (true) 
        {
            if(!readFile.readFile(readSize, (char*)plaintext, totalRead)) break;
            //for(int i = 0; i < totalRead; i++) std::cout << ciphertext[i];

            err = EVP_PKEY_decrypt(pctx, NULL, &outputLen, plaintext, totalRead);
            if(err <= 0)
            {
                std::cout << "Error to EVP_PKEY_decrypt(NULL) " << std::endl;
                EVP_PKEY_CTX_free(pctx);
                EVP_PKEY_free(pkey);
                return 0;
            }
            unsigned char ciphertext[outputLen];
            //std::cout << "Output : " << outputLen << std::endl;

            err = EVP_PKEY_decrypt(pctx, ciphertext, &outputLen, plaintext, totalRead);
            if(err <= 0)
            {
                std::cout << "Error to EVP_PKEY_decrypt() " << std::endl;
                EVP_PKEY_CTX_free(pctx);
                EVP_PKEY_free(pkey);
                return 0;
            }

            //for(int i = 0; i < outputLen; i++) std::cout << plaintext[i];
            if(outputLen) writeFile.writeFile((char*)ciphertext, outputLen);
        }

        EVP_PKEY_CTX_free(pctx);
        EVP_PKEY_free(pkey);
        return 1;
    }

    int rsaSign(EVP_PKEY* pkey, const unsigned char* mdBuff, size_t mdLen, std::string sigFileName)
    {
        int err;
        
        if(pkey == nullptr) 
        {
            std::cout << "pkey has not been generated or loaded" << std::endl;
            return 0;
        }

         /*
         *  Step 1 : new ctx object
         *           EVP_PKEY_CTX *EVP_PKEY_CTX_new(EVP_PKEY *pkey, ENGINE *e);
         */

        EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new(pkey, NULL);
        if (!pctx) 
        {
            std::cout << "EVP_PKEY_CTX_new() Error" << std::endl;
            return 0;
        }

        err = EVP_PKEY_sign_init(pctx);
        if (err <= 0) 
        {
            std::cout << "EVP_PKEY_sign_init() Error" << std::endl;
            return 0;
        }

        err = EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PADDING);
        if (err <= 0) 
        {
            std::cout << "EVP_PKEY_CTX_set_rsa_padding() Error" << std::endl;
            return 0;
        }

        //Sets the message digest type used in a signature. It can be used in the RSA, DSA and ECDSA algorithms.
        err = EVP_PKEY_CTX_set_signature_md(pctx, EVP_sha3_256());
        if (err <= 0) 
        {
            std::cout << "EVP_PKEY_CTX_set_signature_md() Error" << std::endl;
            return 0;
        }



        size_t outLen;
        FileManager writeFile(sigFileName, OpMode::WRITE);

        /* Determine buffer length */
        err = EVP_PKEY_sign(pctx, NULL, &outLen, mdBuff, mdLen);
        if(err <= 0)
        {
            std::cout << "Error to EVP_PKEY_sign(NULL) " << std::endl;
            EVP_PKEY_CTX_free(pctx);
            EVP_PKEY_free(pkey);
            return 0;
        }
        unsigned char outputBuff[outLen];

        err = EVP_PKEY_sign(pctx, outputBuff, &outLen, mdBuff, mdLen);
        if(err <= 0)
        {
            std::cout << "Error to EVP_PKEY_sign() " << std::endl;
            EVP_PKEY_CTX_free(pctx);
            EVP_PKEY_free(pkey);
            return 0;
        }
        std::cout << "Sign Output : " << outLen << std::endl;

        //for(int i = 0; i < outputLen; i++) std::cout << plaintext[i];
        if(outLen) writeFile.writeFile((char*)outputBuff, outLen);

        EVP_PKEY_CTX_free(pctx);
        EVP_PKEY_free(pkey);
        return 1;
    }

    int rsaVarify(EVP_PKEY* pkey, const unsigned char* mdBuff, size_t mdLen, std::string sigFileName)
    {
        int err;
        
        if(pkey == nullptr)
        {
            std::cout << "pkey has not been generated or loaded" << std::endl;
            return 0;
        }

         /*
         *  Step 1 : new ctx object
         *           EVP_PKEY_CTX *EVP_PKEY_CTX_new(EVP_PKEY *pkey, ENGINE *e);
         */

        EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new(pkey, NULL);
        if (!pctx) 
        {
            std::cout << "EVP_PKEY_CTX_new() Error" << std::endl;
            return 0;
        }

        err = EVP_PKEY_verify_init(pctx);
        if (err <= 0) 
        {
            std::cout << "EVP_PKEY_verify_init() Error" << std::endl;
            return 0;
        }

        err = EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PADDING);
        if (err <= 0) 
        {
            std::cout << "EVP_PKEY_CTX_set_rsa_padding() Error" << std::endl;
            return 0;
        }

        //Sets the message digest type used in a signature. It can be used in the RSA, DSA and ECDSA algorithms.
        err = EVP_PKEY_CTX_set_signature_md(pctx, EVP_sha3_256());
        if (err <= 0) 
        {
            std::cout << "EVP_PKEY_CTX_set_signature_md() Error" << std::endl;
            return 0;
        }


        size_t outLen;
        int totalRead = 0;
        FileManager readFile(sigFileName, OpMode::READ);
        unsigned char sigbuff[readFile.getFileSize()+1];
        readFile.readFile(readFile.getFileSize(), (char*)sigbuff, totalRead);

        err = EVP_PKEY_verify(pctx, sigbuff, totalRead, mdBuff, mdLen);
        if(err <= 0)
        {
            std::cout << "Error to EVP_PKEY_verify() " << std::endl;
            EVP_PKEY_CTX_free(pctx);
            EVP_PKEY_free(pkey);
            return 0;
        }
        

        EVP_PKEY_CTX_free(pctx);
        EVP_PKEY_free(pkey);
        return 1;
    }

}



PublicKey::PublicKey() : _pkey(NULL) { }

void PublicKey::load_key(std::string key_file_type, std::string key_file)
{
    /*
     *  key_file_type : private  private key
     *                  public   public key
     *
     *  EVP_PKEY *PEM_read_bio_PrivateKey(BIO *bp, EVP_PKEY **x,
     *                             pem_password_cb *cb, void *u);
     *  EVP_PKEY *PEM_read_bio_PUBKEY(BIO *bp, EVP_PKEY **x,
     *                         pem_password_cb *cb, void *u);
     *
     *  The PEM read functions all take an argument TYPE **x and return a TYPE * pointer.
     *  Where TYPE is whatever structure the function uses.
     *
     *  If x is NULL then the parameter is ignored. If x is not NULL but *x is NULL then
     *  the structure returned will be written to *x.
     *
     *  If neither x nor *x is NULL then an attempt is made to reuse the structure at *x
     *  (but see BUGS and EXAMPLES sections). Irrespective of the value of x a pointer to
     *  the structure is always returned (or NULL if an error occurred).
     */

    BIO *bio_key = NULL;
    bio_key = BIO_new_file(key_file.c_str(), "r");

    if (key_file_type == "public" ) {
        _pkey = PEM_read_bio_PUBKEY(bio_key, NULL, NULL, NULL);
    }

    if (key_file_type == "private" ) {
        _pkey = PEM_read_bio_PrivateKey(bio_key, NULL, NULL, NULL);
    }

    if (_pkey == nullptr) {
        std::cout << "Error : failed to load key from " << key_file << std::endl;
    }

    BIO_free(bio_key);
}

PublicKey::~PublicKey() { }
