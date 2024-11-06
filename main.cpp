// main.cpp
#include <iostream>
#include <chrono>
#include "LZ78Compressor.h"
#include "chacha20Encryptor.h"

int main() {
    LZ78Compressor compressor;
    Chacha20Encryptor encryptor;

    std::string input_file;
    std::string compressed_file = "compressed.lz78";
    std::string encrypted_file = "encrypted_file.enc";
    std::string decrypted_file = "decrypted.lz78";
    std::string decompressed_file;

    // Pedir al usuario el nombre del archivo de entrada
    std::cout << "Ingrese el nombre del archivo a procesar: ";
    std::cin >> input_file;

    // Determinar el nombre del archivo descomprimido
    decompressed_file = "decompressed_" + input_file;

    // Preguntar al usuario el orden de las operaciones
    int opcion;
    std::cout << "Seleccione el orden de operaciones:\n";
    std::cout << "1. Comprimir y luego encriptar\n";
    std::cout << "2. Encriptar y luego comprimir\n";
    std::cout << "Ingrese su opción (1 o 2): ";
    std::cin >> opcion;

    // Validar la opción ingresada
    if (opcion != 1 && opcion != 2) {
        std::cerr << "Opción inválida.\n";
        return 1;
    }

    auto start_process_first = std::chrono::high_resolution_clock::now();
    
    if (opcion == 1) {
        compressor.compress(input_file, compressed_file);
        encryptor.encrypt_file(compressed_file, encrypted_file);
        std::cout << "Archivo comprimido y luego encriptado con éxito.\n";

    } else {
        // Opción 2: Encriptar y luego comprimir
        encryptor.encrypt_file(input_file, encrypted_file);
        compressor.compress(encrypted_file, compressed_file);
        std::cout << "Archivo encriptado y luego comprimido con éxito.\n";
    }

    auto end_process_first = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> process_time = end_process_first - start_process_first;
    std::cout << "Tiempo total del proceso: " << process_time.count() << " segundos\n";

    auto start_process_second = std::chrono::high_resolution_clock::now();
    // Deshacer las operaciones en orden inverso
    if (opcion == 1) {
        // Desencriptar y luego descomprimir
        encryptor.decrypt_file(encrypted_file, decrypted_file);
        compressor.decompress(decrypted_file, decompressed_file);
    } else {
        // Descomprimir y luego desencriptar
        compressor.decompress(compressed_file, decrypted_file);
        encryptor.decrypt_file(decrypted_file, decompressed_file);
    }
    auto end_process_second = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> process_time_return = end_process_second - start_process_second;
    std::cout << "Tiempo total del proceso: " << process_time_return.count() << " segundos\n";

    std::cout << "Proceso de descompresión y desencriptación completado exitosamente.\n";
    return 0;
}
