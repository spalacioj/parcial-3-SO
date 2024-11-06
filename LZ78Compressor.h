// LZ78Compressor.h
// Archivo de cabecera que define la clase LZ78Compressor, responsable de la compresión y descompresión de archivos
// usando el algoritmo LZ78

#ifndef LZ78COMPRESSOR_H
#define LZ78COMPRESSOR_H

#include <iostream>      // Para mensajes de error y la función de impresión en consola
#include <fstream>       // Para manejar la entrada y salida de archivos
#include <unordered_map> // Para el diccionario de compresión basado en subcadenas
#include <vector>        // Para almacenar el diccionario durante la descompresión
#include <string>        // Para el manejo de subcadenas y símbolos

class LZ78Compressor {
public:
    // Método para comprimir el archivo de entrada y guardar la salida en el archivo comprimido
    bool compress(const std::string& inputFilePath, const std::string& outputFilePath);

    // Método para descomprimir el archivo comprimido y guardar la salida en el archivo de salida
    bool decompress(const std::string& inputFilePath, const std::string& outputFilePath);

private:
    // Función para mostrar la tabla de códigos generada durante la compresión en formato de tupla (índice, subcadena)
    void displayWordCodeTable(const std::unordered_map<std::string, int>& dictionary) const;
};

#endif // LZ78COMPRESSOR_H
