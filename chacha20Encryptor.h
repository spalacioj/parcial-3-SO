// Chacha20Encryptor.h
#ifndef CHACHA20ENCRYPTOR_H
#define CHACHA20ENCRYPTOR_H

#include <iostream>
#include <fstream>
#include <sodium.h>
#include <vector>

class Chacha20Encryptor {
public:
    Chacha20Encryptor();
    void encrypt_file(const std::string& input_file, const std::string& output_file);
    void decrypt_file(const std::string& input_file, const std::string& output_file);

private:
    unsigned char key[crypto_stream_chacha20_KEYBYTES];
    unsigned char nonce[crypto_stream_chacha20_NONCEBYTES];
    
    void chacha20_encrypt(const unsigned char* plaintext, unsigned char* ciphertext, size_t length);
    void chacha20_decrypt(const unsigned char* ciphertext, unsigned char* decrypted, size_t length);
};

#endif // CHACHA20ENCRYPTOR_H
