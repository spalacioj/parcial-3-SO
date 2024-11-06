
# Compresor LZ78 en C++

Este proyecto implementa el algoritmo de compresión LZ78 en C++ para comprimir y descomprimir archivos tanto de texto plano como binarios. Utiliza una estructura de diccionario para almacenar y reutilizar subcadenas, lo que reduce la redundancia y el tamaño del archivo.

## Descripción del Algoritmo LZ78

El algoritmo LZ78 es un método de compresión sin pérdida que trabaja con un diccionario de subcadenas. Cada subcadena se asocia con un índice único en el diccionario. A medida que se lee el archivo, se crea un par `(índice, símbolo)` para cada nueva subcadena, donde:
- **Índice**: Representa la posición de la subcadena previa en el diccionario.
- **Símbolo**: El siguiente carácter que completa la subcadena.

Al final, el diccionario contiene todas las combinaciones posibles de subcadenas encontradas en el archivo. La compresión se logra al referenciar cada subcadena mediante su índice en lugar de almacenarla completamente.

## Estructura del Proyecto

- **LZ78Compressor.h**: Archivo de cabecera que define la clase `LZ78Compressor` con métodos de compresión y descompresión.
- **LZ78Compressor.cpp**: Implementación de los métodos de compresión y descompresión, junto con la función para mostrar la tabla de códigos.
- **main.cpp**: Programa principal que maneja los argumentos de la línea de comandos para comprimir o descomprimir archivos.
- **Makefile**: Archivo para compilar el proyecto en Linux.

## Uso del Programa

Para comprimir o descomprimir un archivo, el programa acepta los siguientes argumentos en la línea de comandos:

```bash
./lz78_program -c <archivo_entrada> <archivo_salida>  # Comprimir un archivo
./lz78_program -d <archivo_comprimido> <archivo_salida>  # Descomprimir un archivo
```

## Pseudocódigos de las Funciones

### Función de Compresión

La función `compress` toma un archivo de entrada y genera un archivo comprimido utilizando el algoritmo LZ78.

#### Pseudocódigo

```
function compress(inputFilePath, outputFilePath):
    abrir archivo de entrada en modo binario
    si archivo de entrada no está abierto:
        mostrar error y terminar

    abrir archivo de salida en modo binario
    si archivo de salida no está abierto:
        mostrar error y terminar

    inicializar dictionary como mapa vacío
    inicializar buffer como cadena vacía
    inicializar dictIndex en 1

    mientras leer símbolo del archivo de entrada:
        combined = buffer + símbolo

        si combined no está en dictionary:
            si buffer está vacío:
                index = 0
            si no:
                index = dictionary[buffer]
            
            escribir index en archivo de salida
            escribir símbolo en archivo de salida
            
            agregar combined a dictionary con dictIndex como índice
            incrementar dictIndex
            limpiar buffer
        si no:
            buffer = combined

    si buffer no está vacío:
        escribir dictionary[buffer] en archivo de salida
        escribir un 0 como indicador de fin de buffer

    cerrar archivo de entrada
    cerrar archivo de salida
```

### Función de Descompresión

La función `decompress` toma un archivo comprimido y lo descomprime utilizando el algoritmo LZ78.

#### Pseudocódigo

```
function decompress(inputFilePath, outputFilePath):
    abrir archivo de entrada en modo binario
    si archivo de entrada no está abierto:
        mostrar error y terminar

    abrir archivo de salida en modo binario
    si archivo de salida no está abierto:
        mostrar error y terminar

    inicializar dictionary con una entrada vacía para índice 0

    mientras leer (index, símbolo) del archivo de entrada:
        entrada = dictionary[index] + símbolo
        escribir entrada en archivo de salida
        agregar entrada a dictionary

    cerrar archivo de entrada
    cerrar archivo de salida
```

## Tabla de Códigos de Palabras (Word Code Table)

Durante el proceso de compresión, se genera una tabla de códigos de palabras, que muestra cada subcadena junto con su índice en el diccionario en formato de tupla `(índice, subcadena)`. Esta tabla ayuda a visualizar el proceso de compresión y el contenido del diccionario en cada paso.

### Ejemplo de Salida de la Tabla de Códigos

```
Tabla de Códigos de Palabras (Word Code Table) en formato de tupla:
(1, A)
(2, AB)
(3, BA)
(4, B)
(5, BC)
```

## Compilación y Ejecución

Para compilar el programa en Linux, usa el archivo `Makefile` proporcionado:

```bash
make  # Compila el proyecto
make clean  # Limpia los archivos compilados
```

Ejecuta el programa usando los comandos indicados en la sección "Uso del Programa".

## Notas Importantes

- El archivo comprimido generado incluye los índices y símbolos en binario, por lo que no es directamente legible sin descompresión.
- La implementación muestra la tabla de códigos de palabras al finalizar el proceso de compresión para que el usuario pueda observar el estado del diccionario.

## Referencias

- [Wikipedia - LZ78](https://en.wikipedia.org/wiki/LZ78): Explicación detallada del algoritmo LZ78 y su implementación.
