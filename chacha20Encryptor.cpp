// Chacha20Encryptor.cpp
#include "chacha20Encryptor.h"

Chacha20Encryptor::Chacha20Encryptor() {
    // Inicializar la biblioteca
    if (sodium_init() < 0) {
        std::cerr << "Error initializing sodium library." << std::endl;
        throw std::runtime_error("Failed to initialize sodium.");
    }
    // Generar clave y nonce aleatorios
    randombytes_buf(key, sizeof(key));
    randombytes_buf(nonce, sizeof(nonce));
}

void Chacha20Encryptor::chacha20_encrypt(const unsigned char* plaintext, unsigned char* ciphertext, size_t length) {
    crypto_stream_chacha20_xor(ciphertext, plaintext, length, nonce, key);
}

void Chacha20Encryptor::chacha20_decrypt(const unsigned char* ciphertext, unsigned char* decrypted, size_t length) {
    crypto_stream_chacha20_xor(decrypted, ciphertext, length, nonce, key);
}

void Chacha20Encryptor::encrypt_file(const std::string& input_file, const std::string& output_file) {
    std::ifstream infile(input_file, std::ios::binary);
    if (!infile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de entrada." << std::endl;
        return;
    }

    std::vector<unsigned char> plaintext((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    std::vector<unsigned char> ciphertext(plaintext.size());
    chacha20_encrypt(plaintext.data(), ciphertext.data(), plaintext.size());

    std::ofstream outfile(output_file, std::ios::binary);
    if (!outfile.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo de salida." << std::endl;
        return;
    }

    outfile.write(reinterpret_cast<const char*>(ciphertext.data()), ciphertext.size());
    outfile.close();
}

void Chacha20Encryptor::decrypt_file(const std::string& input_file, const std::string& output_file) {
    std::ifstream infile(input_file, std::ios::binary);
    if (!infile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de entrada." << std::endl;
        return;
    }

    std::vector<unsigned char> ciphertext((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    std::vector<unsigned char> decrypted(ciphertext.size());
    chacha20_decrypt(ciphertext.data(), decrypted.data(), ciphertext.size());

    std::ofstream outfile(output_file, std::ios::binary);
    if (!outfile.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo de salida." << std::endl;
        return;
    }

    outfile.write(reinterpret_cast<const char*>(decrypted.data()), decrypted.size());
    outfile.close();
}
