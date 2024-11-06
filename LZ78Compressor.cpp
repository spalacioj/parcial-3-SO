// LZ78Compressor.cpp
// Implementación de los métodos de compresión y descompresión para la clase LZ78Compressor

#include "LZ78Compressor.h"
#include <algorithm> // Incluye std::sort para ordenar la tabla de códigos de palabras al final de la compresión

// Método compress
// Este método toma un archivo de entrada, lo comprime usando el algoritmo LZ78 y guarda el resultado en el archivo de salida
// Recibe: inputFilePath (ruta del archivo de entrada), outputFilePath (ruta del archivo comprimido)
bool LZ78Compressor::compress(const std::string& inputFilePath, const std::string& outputFilePath) {
    // Abre el archivo de entrada en modo binario
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    if (!inputFile.is_open()) { // Verifica si el archivo de entrada se abrió correctamente
        std::cerr << "Error: No se pudo abrir el archivo de entrada.\n";
        return false;
    }

    // Abre el archivo de salida en modo binario para guardar los datos comprimidos
    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile.is_open()) { // Verifica si el archivo de salida se creó correctamente
        std::cerr << "Error: No se pudo crear el archivo de salida.\n";
        return false;
    }

    std::unordered_map<std::string, int> dictionary; // Diccionario para almacenar subcadenas y sus índices
    std::string buffer;                              // Buffer para almacenar la cadena parcial actual
    int dictIndex = 1;                               // Índice inicial para cada nueva subcadena en el diccionario

    char symbol; // Almacena el símbolo actual leído del archivo de entrada
    while (inputFile.get(symbol)) { // Lee cada símbolo del archivo
        std::string combined = buffer + symbol; // Combina el buffer con el símbolo actual

        // Si la subcadena combinada no está en el diccionario, se agrega y se comprime el contenido
        if (dictionary.count(combined) == 0) {
            int index = buffer.empty() ? 0 : dictionary[buffer]; // Índice de la subcadena previa en el diccionario
            outputFile.write(reinterpret_cast<const char*>(&index), sizeof(index)); // Escribe el índice en el archivo
            outputFile.put(symbol); // Escribe el símbolo actual en el archivo

            // Agrega la nueva subcadena al diccionario con el siguiente índice disponible
            dictionary[combined] = dictIndex++;
            buffer.clear(); // Limpia el buffer para comenzar una nueva subcadena
        } else {
            buffer = combined; // Actualiza el buffer para continuar formando una subcadena más larga
        }
    }

    // Manejo del último buffer, si aún contiene datos
    if (!buffer.empty()) {
        int index = dictionary[buffer];
        outputFile.write(reinterpret_cast<const char*>(&index), sizeof(index));
        outputFile.put(0); // Indicador de finalización
    }

    // Muestra la tabla de códigos de palabras generada durante la compresión en orden
    //displayWordCodeTable(dictionary);

    inputFile.close(); // Cierra el archivo de entrada
    outputFile.close(); // Cierra el archivo de salida
    return true; // Indica éxito en la compresión
}

// Método decompress
// Este método toma un archivo comprimido y lo descomprime usando el algoritmo LZ78
// Recibe: inputFilePath (ruta del archivo comprimido), outputFilePath (ruta del archivo descomprimido)
bool LZ78Compressor::decompress(const std::string& inputFilePath, const std::string& outputFilePath) {
    std::ifstream inputFile(inputFilePath, std::ios::binary); // Abre el archivo comprimido en modo binario
    if (!inputFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo comprimido.\n";
        return false;
    }

    std::ofstream outputFile(outputFilePath, std::ios::binary); // Abre el archivo de salida en modo binario
    if (!outputFile.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo de salida.\n";
        return false;
    }

    std::vector<std::string> dictionary = {""}; // Inicializa el diccionario con una entrada vacía para el índice 0
    int index; // Índice leído del archivo comprimido
    char symbol; // Símbolo leído del archivo comprimido

    // Descomprime cada par (índice, símbolo) del archivo comprimido
    while (inputFile.read(reinterpret_cast<char*>(&index), sizeof(index)) && inputFile.get(symbol)) {
        std::string entry = dictionary[index] + symbol; // Genera la subcadena original
        outputFile << entry; // Escribe la subcadena en el archivo de salida

        dictionary.push_back(entry); // Agrega la subcadena al diccionario para futuras referencias
    }

    inputFile.close(); // Cierra el archivo comprimido
    outputFile.close(); // Cierra el archivo de salida
    return true; // Indica éxito en la descompresión
}

// Método displayWordCodeTable
// Este método muestra la tabla de códigos de palabras generada durante la compresión en formato de tupla (índice, subcadena)
void LZ78Compressor::displayWordCodeTable(const std::unordered_map<std::string, int>& dictionary) const {
    // Almacena los pares (índice, subcadena) en un vector para ordenarlos
    std::vector<std::pair<int, std::string>> sortedEntries;
    for (const auto& entry : dictionary) {
        sortedEntries.emplace_back(entry.second, entry.first); // Crea pares (índice, subcadena)
    }

    // Ordena el vector por índice para que la tabla de códigos esté en orden
    std::sort(sortedEntries.begin(), sortedEntries.end());

    // Imprime la tabla de códigos de palabras en formato de tupla (índice, subcadena)
    std::cout << "Tabla de Códigos de Palabras (Word Code Table) en formato de tupla:\n";
    for (const auto& entry : sortedEntries) {
        std::cout << "(" << entry.first << ", [" << entry.second << "])\n"; // Muestra cada par (índice, subcadena)
    }
}
