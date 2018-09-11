#ifndef _AES_H_
#define _AES_H_

#include <stdint.h>
#include <string>
#include <cstdio>

class AES
{
public:
    AES(unsigned char* key = NULL);
    virtual ~AES();
    void SetKey(unsigned char *key);
    unsigned char* Cipher(unsigned char* input, unsigned char* output);
    unsigned char* InvCipher(unsigned char* input, unsigned char* output);
    void* Cipher(void* input, void *output, int length = 0);
    void* InvCipher(void* input, void *output, int length);
private:
    unsigned char Sbox[256];
    unsigned char InvSbox[256];
    unsigned char w[11][4][4];

    void KeyExpansion(unsigned char* key, unsigned char w[][4][4]);
    unsigned char FFmul(unsigned char a, unsigned char b);

    void SubBytes(unsigned char state[][4]);
    void ShiftRows(unsigned char state[][4]);
    void MixColumns(unsigned char state[][4]);
    void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);

    void InvSubBytes(unsigned char state[][4]);
    void InvShiftRows(unsigned char state[][4]);
    void InvMixColumns(unsigned char state[][4]);
};

enum AESMode_t { MODE_OFB = 1, MODE_CFB, MODE_CBC, MODE_ECB };


class AESModeOfOperation {
private:
    AES *m_aes;
    AESMode_t	  m_mode;
    unsigned char m_key[16];
    unsigned char m_iv[16];
    //	bool		  m_firstround;
public:
    AESModeOfOperation();
	AESModeOfOperation(AESMode_t mode, unsigned char *key, unsigned char *iv);
    ~AESModeOfOperation();
    void set_mode(AESMode_t _mode);
    void set_key(unsigned char *key);
    void set_iv(unsigned char *iv);


	std::string Encrypt(const std::string& input);

	std::string Decrypt(const std::string& input);

	std::string EncryptBase64(const std::string& input);

	std::string DecryptBase64(const std::string& input);

private:
	int  EncryptInternal(const unsigned char *input, size_t length, unsigned char *output);
	int  DecryptInternal(const unsigned char *input, size_t length, unsigned char *output);
};



#endif //_AES_H_
